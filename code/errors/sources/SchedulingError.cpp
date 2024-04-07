//
// Created by mihael on 29/06/23.
//

#include "SchedulingError.h"

SchedulingError::SchedulingError(const std::string& message) {
    this->error_message = "Scheduling error: " + message;
}

const char* SchedulingError::what() const noexcept {
    return error_message.c_str();
}
