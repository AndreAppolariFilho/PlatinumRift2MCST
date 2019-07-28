//
// Created by dev04 on 6/6/19.
//

#include "Tree.h"
#include <cstdio>
#include <cmath>

Tree::Tree(MCNode * node){
    this->node = node;
}

MCNode * Tree::best_action(int simulations_number){

    MCNode * v;
    int reward;

    for(int i = 0; i < simulations_number; i++)
    {
        //v = this->select();
        v = this->tree_policy();
        reward = v->rollout();
        v->backpropagate(reward);
        //printf("back %d\n",v->get_number_of_visits());
    }
    /*for(int i = 0; i < this->node->children.size(); i++)
    {
        printf("%d\n",this->node->children[i]->children.size());

        printf("\n");
    }*/
    return this->node->get_best_child(0.);
}

MCNode * Tree::select(){
    MCNode * current_node = this->node;
    while(current_node->is_fully_expanded() and current_node->contains_child())
        current_node = this->node->get_best_child(sqrt(2));
    return current_node;
}

MCNode * Tree::tree_policy(){
    MCNode * current_node = this->node;
    while(!current_node->is_terminal())
    {
        //current_node = current_node->expand();

        if(!current_node->is_fully_expanded())
            return current_node->expand();
        else
            current_node = current_node->get_best_child(sqrt(2));

    }
    return current_node;
}

