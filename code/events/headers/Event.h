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
    explicit Event(long time);
    virtual ~Event() = 0;
    [[nodiscard]] long getTime() const;
    EventType getEventType();
    std::string getMessage();
};


#endif //SCHEDULING_EVENT_H
