//
// Created by mihael on 5/23/24.
//

#ifndef CARTESIANGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#define CARTESIANGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "SerializationOperator.h"


class CartesianGeneticProgrammingSerializationOperator final : public SerializationOperator {
    CartesianGeneticProgrammingGenotypeBlueprint* blueprint;
public:
    explicit CartesianGeneticProgrammingSerializationOperator(CartesianGeneticProgrammingGenotypeBlueprint* blueprint);
    ~CartesianGeneticProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //CARTESIANGENETICPROGRAMMINGSERIALIZATIONOPERATOR_H
