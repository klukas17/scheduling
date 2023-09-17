//
// Created by mihael on 29/04/23.
//

/**
 * @file Event.cpp
 * @brief Implements the member functions of the Event class.
 */

#include "Event.h"

Event::Event(long time) {
    this->time = time;
    this->event_type = ABSTRACT;
    this->message = "";
}

Event::~Event() = default;

long Event::getTime() const {
    return time;
}

EventType Event::getEventType() const {
    return event_type;
}

std::string Event::getMessage() {
    return message;
}