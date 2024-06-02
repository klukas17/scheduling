//
// Created by mihael on 6/2/24.
//

#include "SimpleImmunologicalAlgorithm.h"

#include <iostream>

SimpleImmunologicalAlgorithm::SimpleImmunologicalAlgorithm(
    EvaluationFunction* evaluation_function,
    CreationOperator* creation_operator,
    PerturbationOperator* perturbation_operator,
    int population_size,
    int number_of_evaluations,
    int number_of_clones
) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator)
{
    this->number_of_evaluations = number_of_evaluations;
    this->number_of_clones = number_of_clones;
    this->population_size = population_size;
}

void SimpleImmunologicalAlgorithm::optimize(Population* population) {
    population->initialize(creation_operator, evaluation_function);

    int evaluations = 0;

    int iter = 0;
    while (evaluations < number_of_evaluations) {

        std::vector<EvaluatedGenotype*> new_units;

        for (int i = 0; i < population_size; i++) {
            for (int j = 0; j < number_of_clones; j++) {
                auto new_unit_genotype = population->getGenotype(i)->genotype->copy();
                perturbation_operator->perturbate(new_unit_genotype);
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

        population->insertGenotypes(new_units);

        iter++;
        std::cout << "  ITER " << iter << ", err = " << population->getGenotype(0)->fitness_score << std::endl;
    }
}
