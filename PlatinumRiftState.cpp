//
// Created by dev04 on 7/25/19.
//

#include "PlatinumRiftState.h"

int MAX_DEPTH = 10;
int MAX_TURNS = 1000;
int MAX_NEIGHBORS = 6;

PlatinumRiftState::PlatinumRiftState(int board_size, int depth, int turn_number){
    this->connections = new int*[board_size];
    this->nodes = new PlatinumRiftTurn[board_size];
    for(int i = 0; i < board_size; i++){
        this->connections[i] = new int[MAX_NEIGHBORS];
    }
    this->depth = depth;
    this->board_size = board_size;
    this->turn_number = turn_number;
}
PlatinumRiftState::PlatinumRiftState(int **connections, int board_size, int depth, int turn_number){
    this->connections = connections;
    this->board_size = board_size;
    this->depth = depth;
    this->turn_number = turn_number;
}
void PlatinumRiftState::update_node(int pos, PlatinumRiftTurn node){
    this->nodes[pos] = node;
}
double PlatinumRiftState::game_result(PlatinumRiftState & previous_state){
    //defesa e ataque
    int pods = 0;
    for(int i = 0; i < this->board_size; i++) {
        pods += this->get_number_allies(i) - this->get_number_enemies(i);
    }
    //exploração
    int zones = 0;
    for(int i = 0; i < this->board_size; i++) {
        if(this->is_allied(i))
            zones += 1;
        else
            zones-=1;
    }
    //exploração
    int platinum = 0;
    for(int i = 0; i < this->board_size; i++) {
        platinum += this->get_number_platinum(i) - previous_state.get_number_platinum(i);
    }
    return (pods + zones + platinum);
}
PlatinumRiftState PlatinumRiftState::move(PlatinumRiftTurn m){
    PlatinumRiftState new_state = PlatinumRiftState(this->connections,this->board_size,this->depth+1, this->turn_number+1);

    for(int i = 0; i < this->board_size; i++)
    {
        new_state.update_node(i, this->nodes[i]);
        if(m.id == i)
        {
            new_state.update_node(i, m);
        }
    }
    return new_state;
}
void PlatinumRiftState::print_state(){
    printf("print nao implementado\n");
}
bool PlatinumRiftState::finished(){
    if(this->depth >= MAX_DEPTH)
        return true;
    if(this->turn_number == MAX_TURNS)
        return true;
    for(int i = 0; i < this->board_size; i++)
    {
        if(this->nodes[i].is_enemy_base() && this->nodes[i].get_number_enemies() <= 0 && this->nodes[i].get_number_allies() > 0)
            return true;
    }
    return false;
}

int PlatinumRiftState::get_number_allies(int pos){
    return this->nodes[pos].get_number_allies();
}
int PlatinumRiftState::get_number_enemies(int pos){
    return this->nodes[pos].get_number_enemies();
}
int PlatinumRiftState::get_number_platinum(int pos){
    return this->nodes[pos].get_number_platinum();
}
bool PlatinumRiftState::is_allied(int pos){
    return this->nodes[pos].is_allied();
}
std::vector<PlatinumRiftTurn> PlatinumRiftState::get_legal_actions(){
    std::vector<PlatinumRiftTurn> moves;
    PlatinumRiftTurn next;
    PlatinumRiftTurn previous;
    for(int i = 0; i < this->board_size; i++)
    {
        if(this->nodes[i].get_number_allies() > 0 && this->nodes[i].get_number_enemies() > 0)
        {
            for(int j = 0; j < MAX_NEIGHBORS; j++)
            {
                //Adicionar probabilidades

                //expandir todos
                previous = this->nodes[i];
                bool is_allie = true;
                if (previous.get_number_allies() > 0 && previous.get_number_enemies() == 0)
                {
                    if (this->nodes[this->connections[i][j]].get_number_allies() + previous.get_number_allies() >=
                        this->nodes[this->connections[i][j]].get_number_enemies()) {
                        is_allie = true;
                    } else {
                        is_allie = false;
                    }
                    next = PlatinumRiftTurn(
                            j,
                            this->nodes[this->connections[i][j]].get_number_allies() + previous.get_number_allies(),
                            this->nodes[this->connections[i][j]].get_number_enemies(),
                            is_allie,
                            this->nodes[this->connections[i][j]].get_number_platinum(),
                            this->nodes[this->connections[i][j]].is_enemy_base(),
                            this->nodes[this->connections[i][j]].is_allied_base()
                    );

                    moves.push_back(next);
                }
                if(previous.get_number_allies() - 1 > 0 && previous.get_number_enemies() == 0)
                {
                    if(this->nodes[this->connections[i][j]].get_number_allies() + previous.get_number_allies() >= this->nodes[this->connections[i][j]].get_number_enemies())
                    {
                        is_allie = true;
                    }
                    else
                    {
                        is_allie = false;
                    }
                    next = PlatinumRiftTurn(
                            j,
                            this->nodes[this->connections[i][j]].get_number_allies() + 1,
                            this->nodes[this->connections[i][j]].get_number_enemies(),
                            is_allie,
                            this->nodes[this->connections[i][j]].get_number_platinum(),
                            this->nodes[this->connections[i][j]].is_enemy_base(),
                            this->nodes[this->connections[i][j]].is_allied_base()
                    );

                    moves.push_back(next);
                }
            }
        }
    }
    return moves;
}