//
// Created by mihael on 5/27/24.
//

#ifndef LGPREGISTERSSTATE_H
#define LGPREGISTERSSTATE_H

#include <map>

class LGPRegistersState {
    std::map<int, double> registers;
    int number_of_registers;
public:
    explicit LGPRegistersState(int number_of_registers);
    int getNumberOfRegisters();
    double getValue(int register_id);
    void setValue(int register_id, double register_value);
};



#endif //LGPREGISTERSSTATE_H
