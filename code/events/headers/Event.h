//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_EVENT_H
#define SCHEDULING_EVENT_H

#include "EventType.h"
#include "string"

class Event {
protected:
    long time;
    EventType event_type;
    std::string message;
public:
    Event(long time);
    virtual ~Event() = 0;
    std::string getMessage();
    EventType getEventType();
    long getTime();
};


#endif //SCHEDULING_EVENT_H
