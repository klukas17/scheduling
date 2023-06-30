//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineSpecificationsParser.h
 * @brief Defines the MachineSpecificationsParser class for parsing machine specifications from a file
 */

#ifndef SCHEDULING_MACHINESPECIFICATIONSPARSER_H
#define SCHEDULING_MACHINESPECIFICATIONSPARSER_H

#include <string>
#include <map>
#include "MachineType.h"
#include "MachineTypeMap.h"

/**
 * @class MachineSpecificationsParser
 * @brief Parses machine specifications from a file
 */
class MachineSpecificationsParser {
public:
    /**
     * @brief Constructs a MachineSpecificationsParser object
     */
    MachineSpecificationsParser();

    /**
     * @brief Parses the machine specifications from the specified file
     * @param path The path to the file containing machine specifications
     * @return A pointer to the MachineTypeMap object containing the parsed machine types
     */
    static MachineTypeMap* parse(const std::string& path);
};

#endif //SCHEDULING_MACHINESPECIFICATIONSPARSER_H
