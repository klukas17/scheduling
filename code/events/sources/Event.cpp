//
// Created by mihael on 29/04/23.
//

#include "Event.h"

Event::Event(double const time) {
    this->time = time;
    this->event_type = ABSTRACT;
    this->message = "";
}

Event::~Event() = default;

double Event::getTime() const {
    return time;
}

EventType Event::getEventType() const {
    return event_type;
}

std::string Event::getMessage() {
    return message;
}