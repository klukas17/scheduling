//
// Created by mihael on 8/19/23.
//

#ifndef SCHEDULING_TOPOLOGYUTILS_H
#define SCHEDULING_TOPOLOGYUTILS_H

#include "Topology.h"
#include "string"

class TopologyUtils {
public:
    static void logTopology(const Topology* topology, const std::string& logs_path);
    static void logTopologyElement(TopologyElement* topology_element, int indents, std::ofstream& log_stream);
};

#endif //SCHEDULING_TOPOLOGYUTILS_H

