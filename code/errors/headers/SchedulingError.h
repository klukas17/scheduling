//
// Created by mihael on 29/06/23.
//

/**
 * @file SchedulingError.h
 * @brief Defines the SchedulingError class for handling scheduling errors.
 */

#ifndef SCHEDULING_SCHEDULINGERROR_H
#define SCHEDULING_SCHEDULINGERROR_H

#include <exception>
#include <string>

/**
 * @class SchedulingError
 * @brief Exception class for handling scheduling errors.
 *
 * This class inherits from std::exception and provides an error message for scheduling-related exceptions.
 */
class SchedulingError : public std::exception {
private:
    std::string error_message; /**< The error message associated with the exception. */
public:
    /**
     * @brief Constructs a SchedulingError object with the specified error message.
     * @param message The error message to associate with the exception.
     */
    explicit SchedulingError(const std::string& message);

    /**
     * @brief Retrieves the error message associated with the exception.
     * @return The error message as a C-style string.
     */
    [[nodiscard]] const char* what() const noexcept override;
};

#endif //SCHEDULING_SCHEDULINGERROR_H
