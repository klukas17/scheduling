//
// Created by mihael on 5/22/24.
//

#ifndef TBGPNODEREPLACER_H
#define TBGPNODEREPLACER_H
#include "TBGPNode.h"


class TBGPNodeReplacer {
public:
    static void replaceChildren(TBGPNode* parent, TBGPNode* former_child, TBGPNode* new_child);
};



#endif //TBGPNODEREPLACER_H
