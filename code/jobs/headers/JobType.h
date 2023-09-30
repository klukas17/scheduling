//
// Created by mihael on 29/04/23.
//

/**
 * @file JobType.h
 * @brief Defines the JobType class for representing a job type.
 */

#ifndef SCHEDULING_JOBTYPE_H
#define SCHEDULING_JOBTYPE_H

#include <map>
#include <set>

/**
 * @class JobType
 * @brief Class for representing a job type.
 *
 * This class stores information about a job type, including its ID,
 * processing times for different machine types, related job families,
 * and forbidden machine types.
 */
class JobType {
protected:
    long id; /**< The ID of the job type */
    std::map<long, long> processing_times; /**< Processing times associated with different machine types */
    std::set<long> forbidden_machine_types; /**< Set of forbidden machine type IDs */
    bool preempt; /**< Indicates whether preemption is allowed for this job type */

public:
    /**
     * @brief Constructs a JobType object with the given ID.
     * @param id The ID of the job type.
     */
    JobType(long id, bool preempt);

    /**
     * @brief Gets the ID of the job type.
     * @return The ID of the job type.
     */
    [[nodiscard]] long getId() const;

    /**
     * @brief Gets the processing time associated with a specific machine type.
     * @param machine_type_id The ID of the machine type.
     * @return The processing time for the specified machine type.
     */
    long getProcessingTime(long machine_type_id);

    /**
     * @brief Sets the processing time for a specific machine type.
     * @param machine_type_id The ID of the machine type.
     * @param processing_time The processing time to set.
     */
    void setProcessingTime(long machine_type_id, long processing_time);

    /**
     * @brief Gets the set of forbidden machine type IDs.
     * @return The set of forbidden machine type IDs.
     */
    std::set<long> getForbiddenMachineTypes();

    /**
     * @brief Adds a machine type to the set of forbidden machine types.
     * @param machine_type_id The ID of the machine type to add.
     */
    void addForbiddenMachineType(long machine_type_id);

    /**
     * @brief Checks if preemption is allowed for this job type.
     * @return true if preemption is allowed, false otherwise.
     */
    [[nodiscard]] bool getPreempt() const;
};


#endif //SCHEDULING_JOBTYPE_H
