//
// Created by dev04 on 6/7/19.
//

#ifndef MCST_MCNODE_H
#define MCST_MCNODE_H

#include "PlatinumRiftState.h"
#include "PlatinumRiftTurn.h"
#include "TicTacTurn.h"
#include "TicTacToeState.h"
#include <vector>

class MCNode {
private:
    std::vector<PlatinumRiftTurn> untried_actions;

    PlatinumRiftState state;
    int number_of_visits;
    double wins;
    int loses;

    double ucb(double c_param);
    PlatinumRiftTurn rollout_policy(std::vector<PlatinumRiftTurn> possible_actions);
public:
    MCNode * parent;
    std::vector<MCNode * > children;
    MCNode(PlatinumRiftState state);
    MCNode(PlatinumRiftState state, MCNode * parent);
    std::vector<PlatinumRiftTurn> get_untried_actions();
    double q();
    int get_number_of_visits();
    bool is_fully_expanded();
    bool contains_child();
    bool is_terminal();
    MCNode * get_best_child(double c_param);
    int rollout();
    void print_state();
    void set_state(PlatinumRiftState state);
    PlatinumRiftState get_state();
    void backpropagate(double win);
    MCNode * expand();

};


#endif //MCST_MCNODE_H
