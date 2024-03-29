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
    SYSTEM_EXIT, /**< System exit event type. */
    SYSTEM_EXIT_FORCED, /**< Forced system exit event type. */
    SYSTEM_ENTRY, /**< System entry event type. */
    MACHINE_EXIT, /**< Machine exit event type. */
    MACHINE_EXIT_BATCH, /**< Machine exit in batch event type. */
    MACHINE_EXIT_FORCED, /**< Forced machine exit event type. */
    MACHINE_EXIT_FORCED_BATCH, /**< Forced machine exit in batch event type. */
    MACHINE_BUFFER_ENTRY, /**< Machine buffer entry event type. */
    PREREQUISITES_WAIT_START, /**< Start waiting for prerequisites event type. */
    PREREQUISITES_WAIT_END, /**< End waiting for prerequisites event type. */
    PREEMPT, /**< Preemption during processing event type. */
    PREEMPT_BATCH, /**< Preemption during processing in batch event type. */
    SETUP_START, /**< Start of a machine setup event type. */
    SETUP_END, /**< End of a machine setup event type. */
    SETUP_CANCEL, /**< Cancellation of a machine setup event type. */
    BREAKDOWN_START, /**< Start of a machine breakdown event type. */
    BREAKDOWN_END, /**< End of a machine breakdown event type. */
    MACHINE_ENTRY, /**< Machine entry event type. */
    MACHINE_ENTRY_BATCH, /**< Machine entry in batch event type. */
    MACHINE_BUFFER_ENTRY_REQUEST_ASYNCHRONOUS, /**< Asynchronous machine buffer entry request event type. */
    MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS, /**< Synchronous machine buffer entry request event type. */
    WAKE_MACHINE, /**< Wake machine event type. */
};

#endif //SCHEDULING_EVENTTYPE_H
