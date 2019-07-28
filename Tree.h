//
// Created by dev04 on 6/6/19.
//

#ifndef MCST_TREE_H
#define MCST_TREE_H
#include "MCNode.h"

class Tree {
private:
    MCNode * node;
public:
    Tree(MCNode * node);
    MCNode * best_action(int simulations_number);
    MCNode * tree_policy();
    MCNode * select();
};


#endif //MCST_TREE_H
