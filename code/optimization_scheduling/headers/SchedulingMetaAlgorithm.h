//
// Created by mihael on 5/6/24.
//

#ifndef SCHEDULINGMETAALGORITHM_H
#define SCHEDULINGMETAALGORITHM_H

#include "OnlineSchedulingAlgorithmClusterCombinationOperator.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "OptimizationAlgorithmWithCombinationOperator.h"
#include "OptimizationAlgorithmWithCreationOperator.h"
#include "OptimizationAlgorithmWithPerturbationOperator.h"
#include "TopologyEnumerator.h"


class SchedulingMetaAlgorithm final :
    public OptimizationAlgorithmWithCreationOperator,
    public OptimizationAlgorithmWithPerturbationOperator,
    public OptimizationAlgorithmWithCombinationOperator
{
    TopologyEnumerator* topology_enumerator;
    OptimizationAlgorithm* inner_optimization_algorithm;
    Population* inner_optimization_algorithm_population;
    OnlineSchedulingAlgorithmClusterPerturbationOperator* cluster_perturbation_operator;
    OnlineSchedulingAlgorithmClusterCombinationOperator* cluster_combination_operator;
    int iterations_count;
public:
    SchedulingMetaAlgorithm(
        EvaluationFunction* evaluation_function,
        CreationOperator* creation_operator,
        PerturbationOperator* perturbation_operator,
        CombinationOperator* combination_operator,
        TopologyEnumerator* topology_enumerator,
        OptimizationAlgorithm* inner_optimization_algorithm,
        Population* inner_optimization_algorithm_population,
        int iterations_count
    );
    void optimize(Population* population) override;
};



#endif //SCHEDULINGMETAALGORITHM_H
