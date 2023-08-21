//
// Created by mihael on 30/04/23.
//

/**
 * @file WakeMachine.cpp
 * @brief Implements the member functions of the WakeMachine class.
 */

#include "WakeMachine.h"

WakeMachine::WakeMachine(long time, long machine_id) : Event(time), MachineEvent(time, machine_id) {
    this->event_type = WAKE_MACHINE;
}