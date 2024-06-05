//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGEVALUATIONFUNCTIONTBGP_H
#define HYPERPARAMETERTUNINGEVALUATIONFUNCTIONTBGP_H
#include "HyperparameterTuningEvaluationFunction.h"


class HyperparameterTuningEvaluationFunctionTBGP final : public HyperparameterTuningEvaluationFunction {
public:
    HyperparameterTuningEvaluationFunctionTBGP(
        Topology* topology,
        std::map<long, Job*> jobs_train_set,
        std::map<long, Job*> jobs_test_set,
        int number_of_evaluations
    );
    GenotypeBlueprint* constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) override;
    CreationOperator* constructCreationOperator(HyperparameterTuningGenotype* htg) override;
    CombinationOperator* constructCombinationOperator(HyperparameterTuningGenotype* htg) override;
    PerturbationOperator* constructPerturbationOperator(HyperparameterTuningGenotype* htg) override;
    SerializationOperator* constructSerializationOperator(HyperparameterTuningGenotype* htg) override;
};



#endif //HYPERPARAMETERTUNINGEVALUATIONFUNCTIONTBGP_H
