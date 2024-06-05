//
// Created by mihael on 5/29/24.
//

#ifndef STACKBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#define STACKBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "SerializationOperator.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"


class StackBasedGeneticProgrammingSerializationOperator final : public SerializationOperator {
    StackBasedGeneticProgrammingGenotypeBlueprint* blueprint;
public:
    explicit StackBasedGeneticProgrammingSerializationOperator(StackBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    ~StackBasedGeneticProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //STACKBASEDGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
