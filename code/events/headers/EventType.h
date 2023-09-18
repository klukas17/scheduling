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
    SYSTEM_EXIT_FORCED, /**< Forced system exit event type. */
    MACHINE_EXIT, /**< Machine exit event type. */
    MACHINE_EXIT_FORCED, /**< Forced machine exit event type. */
    MACHINE_BUFFER_ENTRY, /**< Machine buffer entry event type. */
    PREREQUISITES_WAIT_START, /**< Start waiting for prerequisites event type. */
    PREREQUISITES_WAIT_END, /**< End waiting for prerequisites event type. */
    PREEMPT, /**< Preemption during processing event type. */
    BREAKDOWN_START, /**< Start of a machine breakdown event type. */
    BREAKDOWN_END, /**< End of a machine breakdown event type. */
    MACHINE_ENTRY, /**< Machine entry event type. */
    WAKE_MACHINE, /**< Wake machine event type. */
};

#endif //SCHEDULING_EVENTTYPE_H
