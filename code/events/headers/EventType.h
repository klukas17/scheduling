//
// Created by mihael on 29/04/23.
//

/**
 * @file EventType.h
 * @brief Defines the enumeration for representing types of events in the scheduling simulation.
 */

#ifndef SCHEDULING_EVENTTYPE_H
#define SCHEDULING_EVENTTYPE_H

/**
 * @enum EventType
 * @brief Enumerates the types of events in the scheduling simulation.
 *
 * The EventType enumeration lists different types of events that can occur during the scheduling simulation process.
 * Each type corresponds to a specific event category or behavior.
 */
enum EventType {
    ABSTRACT, /**< Abstract event type. */
    SYSTEM_ENTRY, /**< System entry event type. */
    SYSTEM_EXIT, /**< System exit event type. */
    MACHINE_BUFFER_ENTRY, /**< Machine buffer entry event type. */
    MACHINE_ENTRY, /**< Machine entry event type. */
    MACHINE_EXIT, /**< Machine exit event type. */
    WAKE_MACHINE /**< Wake machine event type. */
};

#endif //SCHEDULING_EVENTTYPE_H
