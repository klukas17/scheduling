//
// Created by mihael on 30/04/23.
//

/**
 * @file MachineEvent.h
 * @brief Defines the MachineEvent class for representing a machine-related event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEEVENT_H
#define SCHEDULING_MACHINEEVENT_H

#include "Event.h"

/**
 * @class MachineEvent
 * @brief Represents a machine-related event in the scheduling simulation.
 *
 * The MachineEvent class is derived from the Event class and represents an event that is related to a specific machine
 * in the scheduling simulation process. It includes attributes to store the associated machine's identifier.
 */
class MachineEvent : public virtual Event {
protected:
    long machine_id; /**< Identifier of the machine associated with the event. */
public:
    /**
     * @brief Constructs a MachineEvent object with the provided time and machine identifier.
     * @param time The time at which the machine-related event occurs.
     * @param machine_id The identifier of the machine associated with the event.
     */
    MachineEvent(long time, long machine_id);

    /**
     * @brief Virtual destructor for the MachineEvent class.
     */
    ~MachineEvent() override = 0;

    /**
     * @brief Retrieves the identifier of the machine associated with the event.
     * @return The identifier of the associated machine.
     */
    [[nodiscard]] long getMachineId() const;
};

#endif //SCHEDULING_MACHINEEVENT_H
