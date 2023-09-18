//
// Created by mihael on 9/18/23.
//

/**
 * @file BreakdownEnd.h
 * @brief Defines the BreakdownEnd class for representing an end of a machine breakdown in the scheduling simulation.
 */

#ifndef SCHEDULING_BREAKDOWNEND_H
#define SCHEDULING_BREAKDOWNEND_H

#include "MachineEvent.h"

/**
 * @class BreakdownEnd
 * @brief Represents an end of a machine breakdown in the scheduling simulation.
 *
 * The BreakdownEnd class is derived from the MachineEvent class and represents an event that signifies the end of a breakdown.
 * It includes attributes to store the time of the event and the associated machine's identifier.
 */
class BreakdownEnd : public MachineEvent {
public:
    /**
     * @brief Constructs a BreakdownEnd object with the provided time and machine identifier.
     * @param time The time at which the breakdown end machine event occurs.
     * @param machine_id The identifier of the machine associated with the event.
     */
    BreakdownEnd(long time, long machine_id);
};


#endif //SCHEDULING_BREAKDOWNEND_H
