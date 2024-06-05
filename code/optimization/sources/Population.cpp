//
// Created by mihael on 5/6/24.
//

#include "Population.h"

#include <iostream>

bool (*Population::comparator)(EvaluatedGenotype*, EvaluatedGenotype*) =
    [](EvaluatedGenotype* a, EvaluatedGenotype* b){
        return a->fitness_score < b->fitness_score;
};

Population::Population(int population_size) {
    this->population_size = population_size;
}

Population::~Population() {
    for (auto unit : population) {
        delete unit;
    }
}

void Population::initialize(CreationOperator* creation_operator, EvaluationFunction* evaluation_function) {
    while (population.size() < population_size) {
        std::cout << "Initializing population: " << population.size() + 1 << "/" << population_size << std::endl;
        auto const new_unit_genotype = creation_operator->create();
        auto const fitness = evaluation_function->evaluate(new_unit_genotype);
        auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
        population.push_back(evaluated_unit);
    }

    std::sort(population.begin(), population.end(), comparator);
}

void Population::replacePopulation(const std::vector<EvaluatedGenotype*>& new_population) {
    for (auto unit : population) {
        delete unit;
    }
    population.clear();
    for (auto unit : new_population) {
        population.push_back(unit);
    }

    std::sort(population.begin(), population.end(), comparator);
}

EvaluatedGenotype* Population::getGenotype(int index) {
    return population[index];
}

void Population::insertGenotype(EvaluatedGenotype* genotype) {
    auto it = std::lower_bound(population.begin(), population.end(), genotype, comparator);
    population.insert(it, genotype);

    adjustPopulationSize();
}

void Population::insertGenotypes(std::vector<EvaluatedGenotype*> genotypes) {
    for (auto genotype : genotypes) {
        auto it = std::lower_bound(population.begin(), population.end(), genotype, comparator);
        population.insert(it, genotype);
    }

    adjustPopulationSize();
}

void Population::adjustPopulationSize() {
    while (population.size() > population_size) {
        auto genotype_to_destroy = population.back();
        population.pop_back();

        delete genotype_to_destroy;
    }
}
