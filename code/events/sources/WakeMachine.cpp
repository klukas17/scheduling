//
// Created by mihael on 30/04/23.
//

#include "WakeMachine.h"

WakeMachine::WakeMachine(long time, long machine_id) : Event(time) {
    this->machine_id = machine_id;
    this->event_type = WAKE_MACHINE;
}