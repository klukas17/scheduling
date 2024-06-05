//
// Created by mihael on 6/2/24.
//

#include "ClonalSelectionAlgorithm.h"

#include <iostream>

ClonalSelectionAlgorithm::ClonalSelectionAlgorithm(
    EvaluationFunction* evaluation_function,
    CreationOperator* creation_operator,
    PerturbationOperator* perturbation_operator,
    int population_size,
    int number_of_evaluations,
    double beta,
    double new_random_units_percentage,
    int perturbations_per_worst_unit
) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator)
{
    this->number_of_evaluations = number_of_evaluations;
    this->population_size = population_size;
    this->beta = beta;
    this->new_random_units_percentage = new_random_units_percentage;
    this->perturbations_per_worst_unit = perturbations_per_worst_unit;
}

ClonalSelectionAlgorithm::~ClonalSelectionAlgorithm() = default;

void ClonalSelectionAlgorithm::optimize(Population* population) {
    population->initialize(creation_operator, evaluation_function);

    int evaluations = 0;

    int iter = 0;
    while (evaluations < number_of_evaluations) {

        std::vector<EvaluatedGenotype*> new_units;

        for (int i = 0; i < population_size; i++) {
            auto number_of_clones = beta * population_size / (i + 1);
            for (int j = 0; j < number_of_clones; j++) {
                auto new_unit_genotype = population->getGenotype(i)->genotype->copy();
                auto number_of_perturbations = perturbations_per_worst_unit * (i + 1.0) / population_size;
                for (int p = 0; p < number_of_perturbations; p++) {
                    perturbation_operator->perturbate(new_unit_genotype);
                }
                auto const fitness = evaluation_function->evaluate(new_unit_genotype);
                auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
                new_units.push_back(evaluated_unit);

                evaluations++;
                if (evaluations >= number_of_evaluations) {
                    break;
                }
            }
            if (evaluations >= number_of_evaluations) {
                break;
            }
        }

        // elitism
        new_units.push_back(population->getGenotype(0)->copy());

        auto random_units = population_size * new_random_units_percentage;
        for (int i = 0; i < random_units && evaluations < number_of_evaluations; i++) {
            auto new_unit_genotype = creation_operator->create();
            auto const fitness = evaluation_function->evaluate(new_unit_genotype);
            auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
            new_units.push_back(evaluated_unit);
        }

        population->insertGenotypes(new_units);

        iter++;
        std::cout << "CLONALG ITER " << iter << ", err = " << population->getGenotype(0)->fitness_score << std::endl;
    }
}
