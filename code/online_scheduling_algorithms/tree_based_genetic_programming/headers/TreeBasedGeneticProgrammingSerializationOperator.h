//
// Created by mihael on 5/21/24.
//

#ifndef TREEBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#define TREEBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "SerializationOperator.h"
#include "TBGPNode.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"


class TreeBasedGeneticProgrammingSerializationOperator final : public SerializationOperator {
    TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    std::vector<std::string> serializeNode(TBGPNode* node, int depth);
    TBGPNode* deserializeNode(std::vector<std::string>& representation, int& index);
public:
    TreeBasedGeneticProgrammingSerializationOperator(TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    ~TreeBasedGeneticProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //TREEBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
