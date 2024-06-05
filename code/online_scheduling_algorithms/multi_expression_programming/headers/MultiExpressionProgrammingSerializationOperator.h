//
// Created by mihael on 5/30/24.
//

#ifndef MULTIEXPRESSIONPROGRAMMINGSERIALIZATIONOPERATOR_H
#define MULTIEXPRESSIONPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "MultiExpressionProgrammingGenotypeBlueprint.h"
#include "SerializationOperator.h"


class MultiExpressionProgrammingSerializationOperator final : public SerializationOperator {
    MultiExpressionProgrammingGenotypeBlueprint* blueprint;
public:
    explicit MultiExpressionProgrammingSerializationOperator(MultiExpressionProgrammingGenotypeBlueprint* blueprint);
    ~MultiExpressionProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //MULTIEXPRESSIONPROGRAMMINGSERIALIZATIONOPERATOR_H
