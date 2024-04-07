//
// Created by mihael on 8/19/23.
//

#include "TopologyUtils.h"
#include "SchedulingError.h"
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"
#include "fstream"

void TopologyUtils::logTopology(const Topology *topology, const std::string &logs_path) {
    std::ofstream log_stream(logs_path);
    logTopologyElement(topology->getRootElement(), 0, log_stream);
    log_stream.close();
}

void TopologyUtils::logTopologyElement(TopologyElement *topology_element, int const indents, std::ofstream & log_stream) {

    for (int i = 0; i < indents; i++) {
        log_stream << "\t";
    }

    switch(topology_element->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in TopologyUtils::logTopologyElement function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            log_stream << "Machine: " << "id = " << topology_element->getId()
                << ", machine_type_id = " << dynamic_cast<Machine*>(topology_element)->getMachineType()->getId() << std::endl;
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Serial group: " << "id = " << topology_element->getId() << std::endl;
            for (auto const child : dynamic_cast<SerialGroup*>(topology_element)->getChildren()) {
                logTopologyElement(child, indents + 1, log_stream);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Parallel group: " << "id = " << topology_element->getId() << std::endl;
            for (auto const child : dynamic_cast<ParallelGroup*>(topology_element)->getChildren()) {
                logTopologyElement(child, indents + 1, log_stream);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Route group: " << "id = " << topology_element->getId() << std::endl;
            for (auto const child : dynamic_cast<RouteGroup*>(topology_element)->getChildren()) {
                logTopologyElement(child, indents + 1, log_stream);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Open group: " << "id = " << topology_element->getId() << std::endl;
            for (auto const child : dynamic_cast<OpenGroup*>(topology_element)->getChildren()) {
                logTopologyElement(child, indents + 1, log_stream);
            }
            break;
    }
}