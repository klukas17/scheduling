//
// Created by mihael on 4/7/24.
//

#ifndef JOBGENERATORPARAMETERS_H
#define JOBGENERATORPARAMETERS_H

#include "DoubleGenerator.h"


class JobGeneratorParameters {
    long job_type;
    long number_of_jobs;
    DoubleGenerator* release_time_generator;
    double expected_duration;
    DoubleGenerator* weight_generator;
public:
    JobGeneratorParameters(
        long job_type,
        long number_of_jobs,
        DoubleGenerator* release_time_generator,
        double expected_duration,
        DoubleGenerator* weight_generator
    );
    [[nodiscard]] long getJobType() const;
    [[nodiscard]] long getNumberOfJobs() const;
    [[nodiscard]] double generateReleaseTime() const;
    [[nodiscard]] double getExpectedDuration() const;
    [[nodiscard]] double generateWeight() const;
};



#endif //JOBGENERATORPARAMETERS_H
