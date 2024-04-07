//
// Created by mihael on 9/18/23.
//

#ifndef SCHEDULING_BREAKDOWN_H
#define SCHEDULING_BREAKDOWN_H

class Breakdown {
    double start_time;
    double end_time;
public:
    Breakdown(double start_time, double end_time);
    [[nodiscard]] double getStartTime() const;
    [[nodiscard]] double getEndTime() const;
};

#endif //SCHEDULING_BREAKDOWN_H
