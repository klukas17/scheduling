//
// Created by mihael on 9/18/23.
//

#include "BreakdownStart.h"

BreakdownStart::BreakdownStart(double const time, long const machine_id) : Event(time), MachineEvent(time, machine_id) {
    this->event_type = BREAKDOWN_START;
    this->message = "Machine " + std::to_string(machine_id) + ": Started breakdown";
}