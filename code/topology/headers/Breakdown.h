//
// Created by mihael on 9/18/23.
//

/**
 * @file Breakdown.h
 * @brief Defines the Breakdown class for representing a period of machine breakdown.
 */

#ifndef SCHEDULING_BREAKDOWN_H
#define SCHEDULING_BREAKDOWN_H

/**
 * @class Breakdown
 * @brief Represents a period of machine breakdown.
 *
 * The Breakdown class encapsulates information about a period during which a machine experiences a breakdown.
 * It includes attributes to store the start time and end time of the breakdown.
 */
class Breakdown {
private:
    long start_time; /**< The start time of the machine breakdown. */
    long end_time;   /**< The end time of the machine breakdown. */
public:
    /**
     * @brief Constructs a Breakdown object with the provided start and end times.
     * @param start_time The start time of the machine breakdown.
     * @param end_time The end time of the machine breakdown.
     */
    Breakdown(long start_time, long end_time);

    /**
     * @brief Retrieves the start time of the machine breakdown.
     * @return The start time of the breakdown.
     */
    [[nodiscard]] long getStartTime() const;

    /**
     * @brief Retrieves the end time of the machine breakdown.
     * @return The end time of the breakdown.
     */
    [[nodiscard]] long getEndTime() const;
};

#endif //SCHEDULING_BREAKDOWN_H
