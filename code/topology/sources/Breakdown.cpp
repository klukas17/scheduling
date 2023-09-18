//
// Created by mihael on 9/18/23.
//

/**
 * @file Breakdown.cpp
 * @brief Implements the member functions of the Breakdown class.
 */

#include "Breakdown.h"

Breakdown::Breakdown(long start_time, long end_time) {
    this->start_time = start_time;
    this->end_time = end_time;
}

long Breakdown::getStartTime() const {
    return start_time;
}

long Breakdown::getEndTime() const {
    return end_time;
}