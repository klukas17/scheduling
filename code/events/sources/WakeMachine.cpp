//
// Created by mihael on 30/04/23.
//

#include "WakeMachine.h"

WakeMachine::WakeMachine(long time, long machine_id, long step_id) : Event(time), MachineEvent(time, machine_id, step_id) {
    this->event_type = WAKE_MACHINE;
}