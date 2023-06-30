//
// Created by mihael on 29/06/23.
//

/**
 * @file SchedulingError.cpp
 * @brief Implements the member functions of the SchedulingError class.
 */

#include "SchedulingError.h"

/**
 * @brief Constructs a SchedulingError object with the specified error message.
 * @param message The error message to associate with the exception.
 */
SchedulingError::SchedulingError(const std::string& message) {
    this->error_message = "Scheduling error: " + message;
}

/**
 * @brief Retrieves the error message associated with the exception.
 * @return The error message as a C-style string.
 */
const char* SchedulingError::what() const noexcept {
    return error_message.c_str();
}
