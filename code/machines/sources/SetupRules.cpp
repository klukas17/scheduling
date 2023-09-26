//
// Created by mihael on 9/23/23.
//

/**
 * @file SetupRules.cpp
 * @brief Implements the member functions of the SetupRules class.
 */

#include "SetupRules.h"

SetupRules::SetupRules() {}

void SetupRules::addSetup(Setup *setup) {
    this->setups.push_back(setup);
}

Setup *SetupRules::findSetup(long from, long to) {
    for (auto setup : setups) {
        auto setup_from = setup->getJobTypeFrom();
        auto setup_to = setup->getJobTypeTo();
        bool from_check = setup_from == nullptr || setup_from->getId() == from;
        bool to_check = setup_to == nullptr || setup_to->getId() == to;
        if (from_check && to_check) {
            return setup;
        }
    }
    return nullptr;
}