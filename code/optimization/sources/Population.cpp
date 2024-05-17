//
// Created by mihael on 5/6/24.
//

#include "Population.h"

bool (*Population::comparator)(EvaluatedGenotype*, EvaluatedGenotype*) =
    [](EvaluatedGenotype* a, EvaluatedGenotype* b){
        return a->fitness_score < b->fitness_score;
};

Population::Population(int population_size) {
    this->population_size = population_size;
}

void Population::initialize(CreationOperator* creation_operator, EvaluationFunction* evaluation_function) {
    for (int i = 0; i < population_size; i++) {
        auto const new_unit_genotype = creation_operator->create();
        auto const fitness = evaluation_function->evaluate(new_unit_genotype);
        auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
        population.push_back(evaluated_unit);
    }

    std::sort(population.begin(), population.end(), comparator);
}

EvaluatedGenotype* Population::getGenotype(int index) {
    return population[index];
}

void Population::insertGenotype(EvaluatedGenotype* genotype) {
    auto it = std::lower_bound(population.begin(), population.end(), genotype, comparator);
    population.insert(it, genotype);

    auto genotype_to_destroy = population.back();
    population.pop_back();

    // delete genotype_to_destroy;
}

