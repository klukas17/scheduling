//
// Created by mihael on 5/29/24.
//

#ifndef GENEEXPRESSIONPROGRAMMINGSERIALIZATIONOPERATOR_H
#define GENEEXPRESSIONPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "GeneExpressionProgrammingGenotypeBlueprint.h"
#include "GEPPhenotypeNode.h"
#include "GEPProgram.h"
#include "SerializationOperatorWithDistinctPhenotype.h"


class GeneExpressionProgrammingSerializationOperator final : public SerializationOperatorWithDistinctPhenotype {
    GeneExpressionProgrammingGenotypeBlueprint* blueprint;
    std::vector<std::string> serializePhenotypeNode(GEPPhenotypeNode* node, GEPProgram* program, int depth);
public:
    explicit GeneExpressionProgrammingSerializationOperator(GeneExpressionProgrammingGenotypeBlueprint* blueprint);
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
    std::vector<std::string> serializePhenotype(Genotype* genotype) override;
};



#endif //GENEEXPRESSIONPROGRAMMINGSERIALIZATIONOPERATOR_H
