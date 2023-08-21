//
// Created by mihael on 30/04/23.
//

/**
 * @file WakeMachine.h
 * @brief Defines the WakeMachine class for representing a wake machine event in the scheduling simulation.
 */

#ifndef SCHEDULING_WAKEMACHINE_H
#define SCHEDULING_WAKEMACHINE_H

#include "MachineEvent.h"

/**
 * @class WakeMachine
 * @brief Represents a wake machine event in the scheduling simulation.
 *
 * The WakeMachine class is derived from the MachineEvent class and represents an event that signifies the awakening of a machine.
 * It includes attributes to store the time of the event and the associated machine's identifier.
 */
class WakeMachine : public MachineEvent {
public:
    /**
     * @brief Constructs a WakeMachine object with the provided time and machine identifier.
     * @param time The time at which the wake machine event occurs.
     * @param machine_id The identifier of the machine associated with the event.
     */
    WakeMachine(long time, long machine_id);
};

#endif //SCHEDULING_WAKEMACHINE_H
