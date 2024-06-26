//
// Created by mihael on 30/04/23.
//

#include "WakeMachine.h"

WakeMachine::WakeMachine(double const time, long const machine_id) : Event(time), MachineEvent(time, machine_id) {
    this->event_type = WAKE_MACHINE;
}