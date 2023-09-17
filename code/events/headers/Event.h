//
// Created by mihael on 29/04/23.
//

/**
 * @file Event.h
 * @brief Defines the Event class for representing an event in the scheduling simulation.
 */

#ifndef SCHEDULING_EVENT_H
#define SCHEDULING_EVENT_H

#include "EventType.h"
#include "string"

/**
 * @class Event
 * @brief Represents an event in the scheduling simulation.
 *
 * The Event class encapsulates information about an event that occurs in the scheduling simulation process.
 * It includes attributes to store the event time, event type, and an optional message associated with the event.
 */
class Event {
protected:
    long time; /**< Time at which the event occurs. */
    EventType event_type; /**< Type of the event. */
    std::string message; /**< Message associated with the event. */
public:
    /**
     * @brief Constructs an Event object with the provided time.
     * @param time The time at which the event occurs.
     */
    explicit Event(long time);

    /**
     * @brief Virtual destructor for the Event class.
     */
    virtual ~Event() = 0;

    /**
     * @brief Retrieves the time at which the event occurs.
     * @return The time of the event.
     */
    [[nodiscard]] long getTime() const;

    /**
     * @brief Retrieves the type of the event.
     * @return The type of the event.
     */
    [[nodiscard]] EventType getEventType() const;

    /**
     * @brief Retrieves the message associated with the event.
     * @return The message associated with the event.
     */
    std::string getMessage();
};

#endif //SCHEDULING_EVENT_H
