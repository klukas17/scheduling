#include <iostream>
#include <fstream>
#include "string"
#include "yaml-cpp/yaml.h"

void print_node(const YAML::Node& node, int indent = 0, bool is_sub_node = false) {

    if (node.IsScalar()) {
        std::cout << std::string(indent, ' ');
        if (is_sub_node)
            std::cout << "- ";
        std::cout << node.as<std::string>() << std::endl;
    }

    if (node.IsMap()) {
        for (const auto& pair : node) {
            std::cout << std::string(indent, ' ');
            if (is_sub_node)
                std::cout << "- ";
            std::cout << pair.first.as<std::string>() << ":" << std::endl;
            if (!is_sub_node)
                print_node(pair.second, indent + 2);
            else
                print_node(pair.second, indent + 4);
        }
    }

    if (node.IsSequence()) {
        for (const auto& sub_node : node) {
            print_node(sub_node, indent, true);
        }
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    YAML::Node doc = YAML::LoadFile("../../examples/genotype_config/example_01/machine_topology.yaml");

    print_node(doc);

    return 0;
}