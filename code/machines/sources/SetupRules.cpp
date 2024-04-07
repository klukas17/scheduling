//
// Created by mihael on 9/23/23.
//

#include "SetupRules.h"

SetupRules::SetupRules() = default;

void SetupRules::addSetup(Setup *setup) {
    this->setups.push_back(setup);
}

Setup *SetupRules::findSetup(long const from, long const to) {
    for (auto const setup : setups) {
        if (auto const setup_from = setup->getJobTypeFrom(), setup_to = setup->getJobTypeTo();
            (setup_from == nullptr || setup_from->getId() == from) &&
            (setup_to == nullptr || setup_to->getId() == to)
        ) {
            return setup;
        }
    }
    return nullptr;
}