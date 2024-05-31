//
// Created by mihael on 5/30/24.
//

#ifndef GEGENOTYPENODE_H
#define GEGENOTYPENODE_H


class GEGenotypeNode {
public:
    int node_id;
    int codon_value;
    GEGenotypeNode(int node_id, int codon_value);
    ~GEGenotypeNode();
    GEGenotypeNode* copy();
};



#endif //GEGENOTYPENODE_H
