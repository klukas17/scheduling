//
// Created by mihael on 5/6/24.
//

#include "SchedulingMetaAlgorithm.h"

#include <iostream>

SchedulingMetaAlgorithm::SchedulingMetaAlgorithm(
    EvaluationFunction* evaluation_function,
    CreationOperator* creation_operator,
    PerturbationOperator* perturbation_operator,
    CombinationOperator* combination_operator,
    TopologyEnumerator* topology_enumerator,
    OptimizationAlgorithm* inner_optimization_algorithm,
    Population* inner_optimization_algorithm_population,
    int iterations_count
) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator),
    OptimizationAlgorithmWithCombinationOperator(evaluation_function, combination_operator)
{
    this->topology_enumerator = topology_enumerator;
    this->inner_optimization_algorithm = inner_optimization_algorithm;
    this->inner_optimization_algorithm_population = inner_optimization_algorithm_population;
    this->cluster_perturbation_operator = dynamic_cast<OnlineSchedulingAlgorithmClusterPerturbationOperator*>(perturbation_operator);
    this->cluster_combination_operator = dynamic_cast<OnlineSchedulingAlgorithmClusterCombinationOperator*>(combination_operator);
    this->iterations_count = iterations_count;
}

void SchedulingMetaAlgorithm::optimize(Population* population) {
    population->initialize(creation_operator, evaluation_function);

    for (int i = 0; i < iterations_count; i++) {
        auto machines_partition = topology_enumerator->getPartition();
        cluster_perturbation_operator->setModifiableMachines(machines_partition);
        cluster_combination_operator->setModifiableMachines(machines_partition);
        inner_optimization_algorithm->optimize(inner_optimization_algorithm_population);
        auto best_genotype = inner_optimization_algorithm_population->getGenotype(0)->genotype->copy();
        auto genotype_evaluation = evaluation_function->evaluate(best_genotype);
        auto evaluated_genotype = new EvaluatedGenotype(best_genotype, genotype_evaluation);
        population->insertGenotype(evaluated_genotype);
        std::cout << "SMA ITER " << i + 1 << ", err = " << population->getGenotype(0)->fitness_score << std::endl;
    }
}
