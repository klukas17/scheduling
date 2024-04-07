//
// Created by mihael on 9/18/23.
//

#include "Breakdown.h"

Breakdown::Breakdown(double const start_time, double const end_time) {
    this->start_time = start_time;
    this->end_time = end_time;
}

double Breakdown::getStartTime() const {
    return start_time;
}

double Breakdown::getEndTime() const {
    return end_time;
}