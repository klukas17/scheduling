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
    explicit GraphBasedGeneticProgrammingSerializationOperator(GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    ~GraphBasedGeneticProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //GRAPHBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
