//
// Created by mihael on 9/23/23.
//

/**
 * @file SetupRules.h
 * @brief Defines the SetupRules class for managing setup operations between job types.
 */

#ifndef SCHEDULING_SETUPRULES_H
#define SCHEDULING_SETUPRULES_H

#include "Setup.h"
#include <vector>

/**
 * @class SetupRules
 * @brief Manages setup operations between job types.
 *
 * The SetupRules class is responsible for managing setup operations between different job types on a machine.
 * It includes methods to add setup operations and find a setup operation between specific job types.
 */
class SetupRules {
private:
    std::vector<Setup*> setups; /**< Vector containing setup operations between job types. */

public:
    /**
     * @brief Constructs a SetupRules object.
     */
    SetupRules();

    /**
     * @brief Adds a setup operation to the collection of setup rules.
     * @param setup A pointer to the Setup object representing the setup operation.
     */
    void addSetup(Setup* setup);

    /**
     * @brief Finds a setup operation between two job types.
     * @param from The ID of the source job type.
     * @param to The ID of the destination job type.
     * @return A pointer to the Setup object representing the setup operation, or nullptr if not found.
     */
    Setup* findSetup(long from, long to);
};

#endif //SCHEDULING_SETUPRULES_H

