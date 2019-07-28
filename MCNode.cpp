//
// Created by dev04 on 6/7/19.
//

#include "MCNode.h"
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cfloat>

MCNode::MCNode(PlatinumRiftState state):state(state), parent(NULL),number_of_visits(0){
    this->wins = 0;
    if(this->untried_actions.size() == 0)
        this->untried_actions = state.get_legal_actions();

}
MCNode::MCNode(PlatinumRiftState state, MCNode * parent):state(state),parent(parent),number_of_visits(0){
    this->wins = 0;
    if(this->untried_actions.size() == 0)
        this->untried_actions = state.get_legal_actions();
}

std::vector<PlatinumRiftTurn> MCNode::get_untried_actions(){
    return this->untried_actions;
}
void MCNode::set_state(PlatinumRiftState state){
    this->state = state;
}
PlatinumRiftState MCNode::get_state(){
    return this->state;
}
int MCNode::get_number_of_visits(){
    return this->number_of_visits;
}
bool MCNode::is_fully_expanded(){
    return this->untried_actions.size() == 0;
}

double MCNode::ucb(double c_param){
    int father_visits = 1;
    if(this->parent){
        father_visits = this->parent->get_number_of_visits();
    }
    double exploration = (this->q()/(this->get_number_of_visits()*1.0));
    double exploitation = sqrt((2.0*log(  father_visits * 1.0 ) / (this->get_number_of_visits())));
    return  exploration + c_param * exploitation;
}

MCNode * MCNode::get_best_child(double c_param){

    MCNode * max = this->children[0];
    for(int i = 0; i < this->children.size(); i++){
        if(this->children[i]->ucb(c_param) > max->ucb(c_param)){
            max = this->children[i];
        }

    }
    return max;
}
double MCNode::q(){
    return this->wins;

}
bool MCNode::contains_child(){
    return this->children.size() != 0;
}
PlatinumRiftTurn MCNode::rollout_policy(std::vector<PlatinumRiftTurn> possible_actions){
    srand(time(NULL));
    int size = possible_actions.size();
    int index =  rand() % size;
    return possible_actions[index];

}
int MCNode::rollout(){
    PlatinumRiftState previous_state = this->state;
    PlatinumRiftState current_state = this->state;
    while (!current_state.finished()){

        std::vector<PlatinumRiftTurn> possible_moves = current_state.get_legal_actions();
        PlatinumRiftTurn action = this->rollout_policy(possible_moves);
        previous_state = current_state;
        current_state = current_state.move(action);

    }
    return current_state.game_result(previous_state);
}

MCNode * MCNode::expand(){

    srand(time(NULL));
    int size = this->untried_actions.size();
    int index =  rand() % size;

    PlatinumRiftTurn action = this->untried_actions[index];
    this->untried_actions.erase(this->untried_actions.begin()+index,this->untried_actions.begin()+index+1);
    PlatinumRiftState next_state = this->state.move(action);
    MCNode * child = new MCNode(next_state, this);
    this->children.push_back(child);
    return child;

}

void MCNode::print_state(){
    state.print_state();
}
bool MCNode::is_terminal(){
    return this->state.finished();
}
void MCNode::backpropagate(double win){
    this->wins+=win;
    this->number_of_visits+=1;
    if(this->parent){
        this->parent->backpropagate(win);
    }

}