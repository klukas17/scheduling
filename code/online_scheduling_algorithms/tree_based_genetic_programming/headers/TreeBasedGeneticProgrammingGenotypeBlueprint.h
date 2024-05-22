//
// Created by mihael on 5/21/24.
//

#ifndef TREEBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#define TREEBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H

#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"
#include "TBGPNodeFactory.h"

class TreeBasedGeneticProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    TBGPNodeFactory* node_factory;
    int max_height;
    explicit TreeBasedGeneticProgrammingGenotypeBlueprint(TBGPNodeFactory* node_factory, int max_height);
    void setInputs(std::vector<std::string> inputs) override;
};



#endif //TREEBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
