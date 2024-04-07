//
// Created by mihael on 9/23/23.
//

#ifndef SCHEDULING_SETUPRULES_H
#define SCHEDULING_SETUPRULES_H

#include "Setup.h"
#include <vector>

class SetupRules {
    std::vector<Setup*> setups;
public:
    SetupRules();
    void addSetup(Setup* setup);
    Setup* findSetup(long from, long to);
};

#endif //SCHEDULING_SETUPRULES_H

