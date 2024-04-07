//
// Created by mihael on 9/18/23.
//

#include "BreakdownEnd.h"

BreakdownEnd::BreakdownEnd(double const time, long const machine_id) : Event(time), MachineEvent(time, machine_id) {
    this->event_type = BREAKDOWN_END;
    this->message = "Machine " + std::to_string(machine_id) + ": Finished breakdown";
}