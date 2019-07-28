//
// Created by dev04 on 7/25/19.
//

#ifndef MCST_PLATINUMRIFTSTATE_H
#define MCST_PLATINUMRIFTSTATE_H

#include "PlatinumRiftTurn.h"
#include <vector>
class PlatinumRiftState {
private:
    int **connections;
    PlatinumRiftTurn *nodes;
    int board_size;
    int depth;
    int turn_number;
public:
    int next_to_move;
    PlatinumRiftState(int board_size, int depth, int turn_number);
    PlatinumRiftState(int **connections, int board_size, int depth, int turn_number);
    PlatinumRiftState move(PlatinumRiftTurn m);
    void update_node(int pos, PlatinumRiftTurn node);
    double game_result(PlatinumRiftState & previous_state);
    void print_state();
    bool finished();
    std::vector<PlatinumRiftTurn> get_legal_actions();
    bool is_allied(int pos);
    int get_number_allies(int pos);
    int get_number_enemies(int pos);
    int get_number_platinum(int pos);
};


#endif //MCST_PLATINUMRIFTSTATE_H
