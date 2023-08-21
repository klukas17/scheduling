//
// Created by mihael on 25/06/23.
//

/**
 * @file Prerequisite.h
 * @brief Defines the Prerequisite class for representing a job prerequisite.
 */

#ifndef SCHEDULING_PREREQUISITE_H
#define SCHEDULING_PREREQUISITE_H

/**
 * @class Prerequisite
 * @brief Represents a job prerequisite.
 *
 * The Prerequisite class encapsulates information about a job prerequisite, including the job ID, machine ID,
 * and the number of repetitions required before the associated job can be scheduled.
 */
class Prerequisite {
private:
    long job_id; /**< The ID of the associated job that has a prerequisite. */
    long machine_id; /**< The ID of the machine associated with the prerequisite. */
    long repetitions; /**< The number of repetitions required for the prerequisite to be satisfied. */
public:
    /**
     * @brief Constructs a Prerequisite object with the given parameters.
     * @param job_id The ID of the job that has the prerequisite.
     * @param machine_id The ID of the machine associated with the prerequisite.
     * @param repetitions The number of repetitions required to satisfy the prerequisite.
     */
    Prerequisite(long job_id, long machine_id, long repetitions);

    /**
     * @brief Retrieves the job ID of the prerequisite.
     * @return The ID of the job associated with the prerequisite.
     */
    [[nodiscard]] long getJobId() const;

    /**
     * @brief Retrieves the machine ID associated with the prerequisite.
     * @return The ID of the machine associated with the prerequisite.
     */
    [[nodiscard]] long getMachineId() const;

    /**
     * @brief Retrieves the number of repetitions required for the prerequisite to be satisfied.
     * @return The number of repetitions required to satisfy the prerequisite.
     */
    [[nodiscard]] long getRepetitions() const;
};

#endif //SCHEDULING_PREREQUISITE_H

