//
// Created by mihael on 29/06/23.
//

#ifndef SCHEDULING_SCHEDULINGERROR_H
#define SCHEDULING_SCHEDULINGERROR_H

#include <exception>
#include <string>

class SchedulingError final : public std::exception {
    std::string error_message;
public:
    explicit SchedulingError(const std::string& message);
    [[nodiscard]] const char* what() const noexcept override;
};

#endif //SCHEDULING_SCHEDULINGERROR_H
