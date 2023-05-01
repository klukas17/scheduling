//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_NODETYPE_H
#define SCHEDULING_NODETYPE_H

enum NodeType {
    ABSTRACT_NODE,
    MACHINE_NODE,
    SERIAL_GROUP_NODE,
    PARALLEL_GROUP_NODE,
    ROUTE_GROUP_NODE,
    OPEN_GROUP_NODE
};

enum GeneralNodeType {
    ABSTRACT_GENERAL_NODE,
    MACHINE_GENERAL_NODE,
    GROUP_GENERAL_NODE
};

#endif //SCHEDULING_NODETYPE_H
