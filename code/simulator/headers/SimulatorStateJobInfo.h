//
// Created by mihael on 5/16/24.
//

#ifndef SIMULATORSTATEJOBINFO_H
#define SIMULATORSTATEJOBINFO_H

class SimulatorStateJobInfo {
    long machine_id;
    double remaining_time_on_machine;
    bool currently_processing_on_machine;
    double start_of_processing_time;
public:
    SimulatorStateJobInfo();
    long getMachineId();
    void setMachineId(long machine_id);
    double getRemainingTimeOnMachine();
    void setRemainingTimeOnMachine(double remaining_time_on_machine);
    bool getCurrentlyProcessingOnMachine();
    void setCurrentlyProcessingOnMachine(bool currently_processing_on_machine);
    double getStartOfProcessingTime();
    void setStartOfProcessingTime(double start_of_processing_time);
    double calculateRemainingTime(double time);
};


#endif //SIMULATORSTATEJOBINFO_H
