//
// Created by mihael on 9/3/23.
//


#ifndef SCHEDULING_PATHTREENODEUTILS_H
#define SCHEDULING_PATHTREENODEUTILS_H

#include "Job.h"
#include "map"
#include "string"

class PathTreeNodeUtils {
public:
    static void logPathTreeNodes(std::map<long, Job*>& jobs, const std::string& logs_path);
    static void logPathTreeNode(PathTreeNode* path_tree_node, int indents, std::ofstream& log_stream);
};


#endif //SCHEDULING_PATHTREENODEUTILS_H
