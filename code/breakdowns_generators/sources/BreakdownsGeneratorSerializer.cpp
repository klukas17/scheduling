//
// Created by mihael on 5/18/24.
//

#include "BreakdownsGeneratorSerializer.h"
#include "fstream"
#include "Machine.h"
#include "OpenGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "SerialGroup.h"

void BreakdownsGeneratorSerializer::serializeTopology(const std::string& path, Topology* topology) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "topology";
    serializeTopologyElement(out, topology->getRootElement());
    out << YAML::EndMap;
    std::ofstream file(path);
    file << out.c_str();
    file.close();
}

void BreakdownsGeneratorSerializer::serializeTopologyElement(YAML::Emitter& out, TopologyElement* topology_element) {

    switch(topology_element->getTopologyElementType())
    {

    case ABSTRACT_TOPOLOGY_ELEMENT:
        {
            break;
        }

    case MACHINE_TOPOLOGY_ELEMENT:
        {
            auto machine = dynamic_cast<Machine*>(topology_element);
            out << YAML::BeginMap;
            out << YAML::Key << "machine";
            out << YAML::BeginMap;
            out << YAML::Key << "id";
            out << YAML::Value << machine->getId();
            out << YAML::Key << "machine_type_id";
            out << YAML::Value << machine->getMachineType()->getId();
            auto breakdowns = machine->getBreakdowns();
            if (!breakdowns.empty()) {
                out << YAML::Key << "breakdowns";
                out << YAML::Value << YAML::BeginSeq;
                for (auto breakdown : breakdowns) {
                    out << YAML::BeginMap;
                    out << YAML::Key << "start_time";
                    out << YAML::Value << breakdown->getStartTime();
                    out << YAML::Key << "end_time";
                    out << YAML::Value << breakdown->getEndTime();
                    out << YAML::EndMap;
                }
                out << YAML::EndSeq;
            }
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

    case SERIAL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto serial_group = dynamic_cast<SerialGroup*>(topology_element);
            out << YAML::BeginMap;
            out << YAML::Key << "serial";
            out << YAML::BeginMap;
            out << YAML::Key << "id";
            out << YAML::Value << serial_group->getId();
            auto breakdowns = serial_group->getBreakdowns();
            if (!breakdowns.empty()) {
                out << YAML::Key << "breakdowns";
                out << YAML::Value << YAML::BeginSeq;
                for (auto breakdown : breakdowns) {
                    out << YAML::BeginMap;
                    out << YAML::Key << "start_time";
                    out << YAML::Value << breakdown->getStartTime();
                    out << YAML::Key << "end_time";
                    out << YAML::Value << breakdown->getEndTime();
                    out << YAML::EndMap;
                }
                out << YAML::EndSeq;
            }
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto child : serial_group->getChildren()) {
                serializeTopologyElement(out, child);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

    case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto parallel_group = dynamic_cast<ParallelGroup*>(topology_element);
            out << YAML::BeginMap;
            out << YAML::Key << "parallel";
            out << YAML::BeginMap;
            out << YAML::Key << "id";
            out << YAML::Value << parallel_group->getId();
            auto breakdowns = parallel_group->getBreakdowns();
            if (!breakdowns.empty()) {
                out << YAML::Key << "breakdowns";
                out << YAML::Value << YAML::BeginSeq;
                for (auto breakdown : breakdowns) {
                    out << YAML::BeginMap;
                    out << YAML::Key << "start_time";
                    out << YAML::Value << breakdown->getStartTime();
                    out << YAML::Key << "end_time";
                    out << YAML::Value << breakdown->getEndTime();
                    out << YAML::EndMap;
                }
                out << YAML::EndSeq;
            }
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto child : parallel_group->getChildren()) {
                serializeTopologyElement(out, child);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

    case ROUTE_GROUP_TOPOLOGY_ELEMENT:
        {
            auto route_group = dynamic_cast<RouteGroup*>(topology_element);
            out << YAML::BeginMap;
            out << YAML::Key << "route";
            out << YAML::BeginMap;
            out << YAML::Key << "id";
            out << YAML::Value << route_group->getId();
            auto breakdowns = route_group->getBreakdowns();
            if (!breakdowns.empty()) {
                out << YAML::Key << "breakdowns";
                out << YAML::Value << YAML::BeginSeq;
                for (auto breakdown : breakdowns) {
                    out << YAML::BeginMap;
                    out << YAML::Key << "start_time";
                    out << YAML::Value << breakdown->getStartTime();
                    out << YAML::Key << "end_time";
                    out << YAML::Value << breakdown->getEndTime();
                    out << YAML::EndMap;
                }
                out << YAML::EndSeq;
            }
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto child : route_group->getChildren()) {
                serializeTopologyElement(out, child);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

    case OPEN_GROUP_TOPOLOGY_ELEMENT:
        {
            auto open_group = dynamic_cast<OpenGroup*>(topology_element);
            out << YAML::BeginMap;
            out << YAML::Key << "open";
            out << YAML::BeginMap;
            out << YAML::Key << "id";
            out << YAML::Value << open_group->getId();
            auto breakdowns = open_group->getBreakdowns();
            if (!breakdowns.empty()) {
                out << YAML::Key << "breakdowns";
                out << YAML::Value << YAML::BeginSeq;
                for (auto breakdown : breakdowns) {
                    out << YAML::BeginMap;
                    out << YAML::Key << "start_time";
                    out << YAML::Value << breakdown->getStartTime();
                    out << YAML::Key << "end_time";
                    out << YAML::Value << breakdown->getEndTime();
                    out << YAML::EndMap;
                }
                out << YAML::EndSeq;
            }
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto child : open_group->getChildren()) {
                serializeTopologyElement(out, child);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }
    }
}
