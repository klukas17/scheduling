//
// Created by mihael on 29/04/23.
//

#include "Event.h"

Event::Event(long time) {
    this->time = time;
    this->event_type = ABSTRACT;
    this->message = "";
}

Event::~Event() {}

std::string Event::getMessage() {
    return message;
}

EventType Event::getEventType() {
    return event_type;
}

long Event::getTime() {
    return time;
}