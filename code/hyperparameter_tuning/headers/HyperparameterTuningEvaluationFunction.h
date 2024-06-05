//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGEVALUATIONFUNCTION_H
#define HYPERPARAMETERTUNINGEVALUATIONFUNCTION_H

#include "CombinationOperator.h"
#include "CreationOperator.h"
#include "EvaluationFunction.h"
#include "GenotypeBlueprint.h"
#include "HyperparameterTuningGenotype.h"
#include "Job.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperator.h"
#include "OptimizationAlgorithm.h"
#include "PerturbationOperator.h"
#include "SerializationOperator.h"
#include "Topology.h"
#include "TopologyEnumerator.h"


class HyperparameterTuningEvaluationFunction : public EvaluationFunction {
protected:
    Topology* topology;
    std::map<long, Job*> jobs_train_set;
    std::map<long, Job*> jobs_test_set;
    int number_of_evaluations;
    GenotypeBlueprint* blueprint;
public:
    HyperparameterTuningEvaluationFunction(
        Topology* topology,
        std::map<long, Job*> jobs_train_set,
        std::map<long, Job*> jobs_test_set,
        int number_of_evaluations
    );
    double _evaluate(Genotype* genotype) override;

    int extractIterationCount(HyperparameterTuningGenotype* htg);
    int extractSubPopulationSize(HyperparameterTuningGenotype* htg);
    OnlineSchedulingAlgorithmClusterCombinationOperator* extractClusterCombinationOperator(
        HyperparameterTuningGenotype* htg,
        CombinationOperator* sub_combination_operator
    );
    TopologyEnumerator* extractTopologyEnumerator(
        HyperparameterTuningGenotype* htg,
        Topology* topology
    );
    OptimizationAlgorithm* extractSubAlgorithm(
        HyperparameterTuningGenotype* htg,
        EvaluationFunction* evaluation_function,
        CreationOperator* creation_operator,
        PerturbationOperator* perturbation_operator,
        CombinationOperator* combination_operator
    );

    virtual GenotypeBlueprint* constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) = 0;
    virtual CreationOperator* constructCreationOperator(HyperparameterTuningGenotype* htg) = 0;
    virtual CombinationOperator* constructCombinationOperator(HyperparameterTuningGenotype* htg) = 0;
    virtual PerturbationOperator* constructPerturbationOperator(HyperparameterTuningGenotype* htg) = 0;
    virtual SerializationOperator* constructSerializationOperator(HyperparameterTuningGenotype* htg) = 0;
};



#endif //HYPERPARAMETERTUNINGEVALUATIONFUNCTION_H
