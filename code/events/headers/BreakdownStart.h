//
// Created by mihael on 9/18/23.
//

/**
 * @file BreakdownStart.h
 * @brief Defines the BreakdownStart class for representing a start of a machine breakdown in the scheduling simulation.
 */

#ifndef SCHEDULING_BREAKDOWNSTART_H
#define SCHEDULING_BREAKDOWNSTART_H

#include "MachineEvent.h"

/**
 * @class BreakdownStart
 * @brief Represents a start of a machine breakdown in the scheduling simulation.
 *
 * The BreakdownStart class is derived from the MachineEvent class and represents an event that signifies the start of a breakdown.
 * It includes attributes to store the time of the event and the associated machine's identifier.
 */
class BreakdownStart : public MachineEvent {
public:
    /**
     * @brief Constructs a BreakdownStart object with the provided time and machine identifier.
     * @param time The time at which the breakdown start machine event occurs.
     * @param machine_id The identifier of the machine associated with the event.
     */
    BreakdownStart(long time, long machine_id);
};


#endif //SCHEDULING_BREAKDOWNSTART_H
