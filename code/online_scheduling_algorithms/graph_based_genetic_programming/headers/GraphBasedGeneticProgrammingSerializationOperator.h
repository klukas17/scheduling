//
// Created by mihael on 6/1/24.
//

#ifndef GRAPHBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#define GRAPHBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"
#include "SerializationOperator.h"


class GraphBasedGeneticProgrammingSerializationOperator final : public SerializationOperator {
    GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint;
public:
    GraphBasedGeneticProgrammingSerializationOperator(GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //GRAPHBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
