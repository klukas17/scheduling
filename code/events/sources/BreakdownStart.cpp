//
// Created by mihael on 9/18/23.
//

/**
 * @file BreakdownStart.cpp
 * @brief Implements the member functions of the BreakdownStart class.
 */

#include "BreakdownStart.h"

BreakdownStart::BreakdownStart(long time, long machine_id) : Event(time), MachineEvent(time, machine_id) {
    this->event_type = BREAKDOWN_START;
    this->message = "Machine " + std::to_string(machine_id) + ": Started breakdown";
}