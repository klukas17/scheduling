//
// Created by mihael on 5/27/24.
//

#ifndef LINEARGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#define LINEARGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "LinearGeneticProgrammingGenotypeBlueprint.h"
#include "SerializationOperator.h"


class LinearGeneticProgrammingSerializationOperator final : public SerializationOperator {
    LinearGeneticProgrammingGenotypeBlueprint* blueprint;
public:
    explicit LinearGeneticProgrammingSerializationOperator(LinearGeneticProgrammingGenotypeBlueprint* blueprint);
    ~LinearGeneticProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //LINEARGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
