//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_EVENT_H
#define SCHEDULING_EVENT_H

#include "EventType.h"
#include "string"

class Event {
protected:
    double time;
    EventType event_type;
    std::string message;
public:
    explicit Event(double time);
    virtual ~Event() = 0;
    [[nodiscard]] double getTime() const;
    [[nodiscard]] EventType getEventType() const;
    std::string getMessage();
};

#endif //SCHEDULING_EVENT_H
