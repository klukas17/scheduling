//
// Created by mihael on 5/5/24.
//

#ifndef SCHEDULINGEVALUATIONFUNCTION_H
#define SCHEDULINGEVALUATIONFUNCTION_H

#include <string>
#include "EvaluationFunction.h"
#include "Job.h"
#include "ObjectiveFunction.h"
#include "Topology.h"


class SchedulingEvaluationFunction final : public EvaluationFunction {
    ObjectiveFunction* objective_function;
    Topology* topology;
    std::map<long, Job*> jobs;
    bool logs_enabled;
    std::string output_dir;
    int log_index;
public:
    SchedulingEvaluationFunction(
        ObjectiveFunction* objective_function,
        Topology* topology,
        std::map<long, Job*>& jobs,
        bool logs_enabled = false,
        std::string output_dir = ""
    );
    double _evaluate(Genotype* genotype) override;
};



#endif //SCHEDULINGEVALUATIONFUNCTION_H
