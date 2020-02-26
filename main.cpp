#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cfloat>

using namespace std;

class PlatinumRiftTurn {
private:
    int number_allies, number_enemies, number_platinum, number_comming_allies, send_to_id;
    bool enemy_base, allied_base, is_allie;
public:
    int id;
    PlatinumRiftTurn();
    PlatinumRiftTurn(
            int id,
            int number_allies,
            int number_enemies,
            bool is_allie,
            int number_platinum,
            bool is_enemy_base,
            bool is_allied_base
    );
    PlatinumRiftTurn(
            int id,
            int number_allies,
            int number_enemies,
            bool is_allie,
            int number_platinum,
            int number_comming_allies,
            bool is_enemy_base,
            bool is_allied_base
    );
    PlatinumRiftTurn(
            int id,
            int number_allies,
            int number_enemies,
            bool is_allie,
            int number_platinum,
            int number_comming_allies,
            bool is_enemy_base,
            bool is_allied_base,
            int send_to_id
    );
    int get_number_allies();
    int get_number_enemies();
    int get_number_platinum();
    int get_number_comming_allies();
    int get_send_id();
    bool is_enemy_base();
    bool is_allied_base();
    bool is_allied();
    void print_turn();

};

PlatinumRiftTurn::PlatinumRiftTurn(){

}

PlatinumRiftTurn::PlatinumRiftTurn(int id, int number_allies, int number_enemies, bool is_allie, int number_platinum, bool is_enemy_base, bool is_allied_base){
    this->number_allies = number_allies;
    this->number_enemies = number_enemies;
    this->is_allie = is_allie;
    this->number_platinum = number_platinum;
    this->allied_base = is_allied_base;
    this->enemy_base = is_enemy_base;
    this->id = id;
}

PlatinumRiftTurn::PlatinumRiftTurn(int id, int number_allies, int number_enemies, bool is_allie, int number_platinum, int number_comming_allies, bool is_enemy_base, bool is_allied_base){
    this->number_allies = number_allies;
    this->number_enemies = number_enemies;
    this->is_allie = is_allie;
    this->number_platinum = number_platinum;
    this->allied_base = is_allied_base;
    this->enemy_base = is_enemy_base;
    this->number_comming_allies = number_comming_allies;
    this->id = id;
}
PlatinumRiftTurn::PlatinumRiftTurn(
            int id,
            int number_allies,
            int number_enemies,
            bool is_allie,
            int number_platinum,
            int number_comming_allies,
            bool is_enemy_base,
            bool is_allied_base,
            int send_to_id
    ){
        this->number_allies = number_allies;
    this->number_enemies = number_enemies;
    this->is_allie = is_allie;
    this->number_platinum = number_platinum;
    this->allied_base = is_allied_base;
    this->enemy_base = is_enemy_base;
    this->number_comming_allies = number_comming_allies;
    this->id = id;
    this->send_to_id = send_to_id;
    }
int PlatinumRiftTurn::get_number_allies(){
    return this->number_allies;
}
int PlatinumRiftTurn::get_number_enemies(){
    return this->number_enemies;
}
int PlatinumRiftTurn::get_number_platinum(){
    return this->number_platinum;
}
int PlatinumRiftTurn::get_send_id(){
    return this->send_to_id;
}
bool PlatinumRiftTurn::is_enemy_base() {
    return this->enemy_base;
}
bool PlatinumRiftTurn::is_allied_base(){
    return this->allied_base;
}
bool PlatinumRiftTurn::is_allied() {
    return this->is_allie;
}
void PlatinumRiftTurn::print_turn(){
    cerr<<this->id<<"Number of allies "<<this->number_allies<<" Number of enemies "<<this->number_enemies<<" Number of platinum "<<this->number_platinum<<endl;
}
int PlatinumRiftTurn::get_number_comming_allies(){
    return this->number_comming_allies;
}

class PlatinumRiftState {
private:
    int **connections;
    
    int board_size;
    int depth;
    int turn_number;
public:
    int next_to_move;
    PlatinumRiftTurn *nodes;
    PlatinumRiftState(int board_size, int depth, int turn_number);
    PlatinumRiftState();
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
    int get_number_comming_allies(int pos);
    int get_send_id(int pos);
};

int MAX_DEPTH = 10;
int MAX_TURNS = 1000;
int MAX_NEIGHBORS = 6;
PlatinumRiftState::PlatinumRiftState(){

}
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
    this->nodes = new PlatinumRiftTurn[board_size];
    this->depth = depth;
    this->turn_number = turn_number;
}
void PlatinumRiftState::update_node(int pos, PlatinumRiftTurn node){
    this->nodes[pos] = node;
}
double PlatinumRiftState::game_result(PlatinumRiftState & previous_state){
    //defesa e ataque
    int pods = 0;
    /*
    for(int i = 0; i < this->board_size; i++) {
        pods += this->get_number_allies(i) - this->get_number_enemies(i);
    }
    */
    //exploração
    /*int zones = 0;
    for(int i = 0; i < this->board_size; i++) {
        if(this->is_allied(i) || !this->get_number_enemies(i) == 0)
            zones += 1;
        else
            zones-=1;
    }*/
    int previous_zones = 0;
    int previous_zones_enemies = 0;
    int neutral_zones = 0;
    
    for(int i = 0; i < this->board_size; i++)
    {
        if(this->is_allied(i) > 0)
        {
            previous_zones += 1;
            if(this->get_number_platinum(i) > 0)
            {
                previous_zones += 1;
            }
        }
        if(this->nodes[i].is_enemy_base())
        {
            previous_zones_enemies += 1;
            if(this->get_number_platinum(i) > 0)
            {
                previous_zones_enemies += 1;
            }
        }
        else if(this->nodes[i].get_number_enemies() > 0){
            previous_zones_enemies +=1;
            if(this->get_number_platinum(i) > 0)
            {
                previous_zones_enemies += 1;
            }
        }
        if(!this->is_allied(i) > 0 && !this->nodes[i].is_enemy_base() && this->nodes[i].get_number_enemies() == 0 && this->nodes[i].get_number_allies()==0)
        {
            neutral_zones += 1;
            if(this->get_number_platinum(i) > 0)
            {
                neutral_zones += 1;
            }
        }
    }
    
    //cerr<<"previous "<<previous_zones<<endl;
    //cerr<<"previous "<<previous_zones_enemies<<endl;
    //cerr<<"previous "<<neutral_zones<<endl;
    int future_zones = previous_zones;
    for(int i = 0; i < this->board_size; i++)
    {
        //cerr<<this->nodes[i].get_send_id()<<" "<<this->nodes[i].get_number_comming_allies()<<endl;
        if(!this->is_allied(this->nodes[i].get_send_id()) > 0 && \
        !this->nodes[this->nodes[i].get_send_id()].is_enemy_base() && \
        this->nodes[this->nodes[i].get_send_id()].get_number_enemies() == 0 && \
        this->nodes[this->nodes[i].get_send_id()].get_number_allies()==0){
            if(this->nodes[i].get_number_comming_allies() > 0)
            {
                future_zones += 1;
                if(this->get_number_platinum(this->nodes[i].get_send_id()) > 0)
                {
                    future_zones += 1;
                }
                
            }
        }
    }
    //cerr<<"future "<<future_zones<<endl;
    int zones = 0;
    for(int i = 0; i < this->board_size; i++) {
        if(this->get_number_allies(i)>0){
            zones+=1;
        }
        /*if(this->get_number_enemies(i)>0){
            zones-=1;
        }*/
        //zones += 1;
        if(this->get_number_allies(i) == 0 && this->get_number_enemies(i) == 0)
            zones -= 1;
        
    }
    int platinum = 0;
    
    //exploração
    
    /*for(int i = 0; i < this->board_size; i++) {
        platinum -= (this->get_number_platinum(i) + 1) - previous_state.get_number_platinum(i);
    }*/
    
    cerr<<"Score "<<(future_zones - previous_zones_enemies - neutral_zones)<<endl;
    /*for(int i = 0; i < this->board_size; i++) {
        if(this->nodes[i].get_number_comming_allies())
        {
            cerr<<this->nodes[i].get_send_id()<<" "<<this->nodes[i].get_number_comming_allies()<<endl;
        }
    }*/
    return (pods + (future_zones - previous_zones_enemies - neutral_zones) + platinum);
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
    //new_state.update_node(m.id, m);
    return new_state;
}
void PlatinumRiftState::print_state(){
    /*
    cerr<<"------Printing the state----------- "<<endl;
    for(int i = 0; i < this->board_size; i++)
    {
        this->nodes[i].print_turn();
    }
    cerr<<"---------------------------------"<<endl;
    */
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
int PlatinumRiftState::get_send_id(int pos){
    return this->nodes[pos].get_send_id();
}
int PlatinumRiftState::get_number_comming_allies(int pos){
    return this->nodes[pos].get_number_comming_allies();
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
    //cerr<<this->board_size<<endl;
    for(int i = 0; i < this->board_size; i++)
    {
        //if(this->nodes[i].get_number_allies() >=0 && this->nodes[i].get_number_enemies() >= 0)
        //{
            //cerr<<"if"<<endl;
            previous = this->nodes[i];
            //cerr<<"-> "<<previous.id<<" "<<previous.get_number_allies()<<endl;
            //cerr<<"Number Allies"<<previous.get_number_allies()<<endl;
            if(previous.get_number_allies() > 0){
                cerr<<"-> "<<previous.id<<" "<<previous.get_number_allies()<<endl;
                for(int j = 0; j < MAX_NEIGHBORS; j++)
                {
                    
                    bool is_allie = true;
                    
                    if (previous.get_number_allies() > 0 && connections[i][j]!=-1)
                    {
                        if (this->nodes[i].get_number_allies() >=
                            this->nodes[i].get_number_enemies()) {
                            is_allie = true;
                        } else {
                            is_allie = false;
                        }
                        
                        next = PlatinumRiftTurn(
                                i,
                                previous.get_number_allies(),
                                this->nodes[i].get_number_enemies(),
                                this->nodes[i].is_allied_base(),
                                this->nodes[i].get_number_platinum(),
                                previous.get_number_allies(),
                                this->nodes[i].is_enemy_base(),
                                this->nodes[i].is_allied_base(),
                                this->connections[i][j]
                        );
    
                        moves.push_back(next);
                    }
                    if(previous.get_number_allies() - 1 > 0 && connections[i][j]!=-1)
                    {
                        //cerr<<i<<" "<<this->connections[i][j]<<endl;
                        if(this->nodes[i].get_number_allies() >= this->nodes[i].get_number_enemies())
                        {
                            is_allie = true;
                        }
                        else
                        {
                            is_allie = false;
                        }
                        next = PlatinumRiftTurn(
                                i,
                                this->nodes[i].get_number_allies(),
                                this->nodes[i].get_number_enemies(),
                                this->nodes[i].is_allied_base(),
                                this->nodes[i].get_number_platinum(),
                                1,
                                this->nodes[i].is_enemy_base(),
                                this->nodes[i].is_allied_base(),
                                this->connections[i][j]
                        );
    
                        moves.push_back(next);
                    }
                }
            }
        //}
    }
    
    
    return moves;
}
class MCNode {
private:
    std::vector<PlatinumRiftTurn> untried_actions;

    PlatinumRiftState state;
    int number_of_visits;
    double wins;
    int loses;

    double ucb(double c_param);
    std::vector<PlatinumRiftTurn> rollout_policy(std::vector<PlatinumRiftTurn> possible_actions);
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
    //cerr<<"--------------------------------------"<<endl;
    for(int i = 0; i < this->children.size(); i++){
        if(this->children[i]->ucb(c_param) > max->ucb(c_param)){
            this->children[i]->state.print_state();
            max = this->children[i];
        }

    }
    //cerr<<"#########################################"<<endl;
    return max;
}
double MCNode::q(){
    return this->wins;

}
bool MCNode::contains_child(){
    return this->children.size() != 0;
}
std::vector<PlatinumRiftTurn> MCNode::rollout_policy(std::vector<PlatinumRiftTurn> possible_actions){
    srand(time(NULL));
    std::vector<PlatinumRiftTurn> possible_turns;
    bool ids_moveds[500] = { false };
    //int num_moves = rand() % (possible_actions.size() );
    int num_moves = 2;
    
    int count = 0;
    int size = possible_actions.size();
   for(count = 0; count < num_moves && count < size;){
        
        
        int index =  rand() % size;
        cerr<<possible_actions[index].id<<endl;
        if(!ids_moveds[possible_actions[index].id]){
            ids_moveds[possible_actions[index].id] = true;
            possible_turns.push_back(possible_actions[index]);
            for(int i = 0; i < possible_actions.size(); i++){
                if(possible_actions[i].id == possible_actions[index].id)
                {
                    count++;
                }
            }
            
            
        }
    }
    
    return possible_turns;

}
int MCNode::rollout(){
    PlatinumRiftState previous_state = this->state;
    PlatinumRiftState current_state = this->state;
    while (!current_state.finished()){

        std::vector<PlatinumRiftTurn> possible_moves = current_state.get_legal_actions();
        cerr<<"moves "<<possible_moves.size()<<endl;
        /*for(int i = 0; i < possible_moves.size();i++)
        {
            cerr<<possible_moves[i].id<<" "<<possible_moves[i].get_send_id()<<endl;
        }*/
        std::vector<PlatinumRiftTurn> action = this->rollout_policy(possible_moves);
        previous_state = current_state;
        //cerr<<"Teste"<<endl;
        for(int i = 0; i < action.size(); i++){
            current_state = current_state.move(action[i]);
        }
        //cerr<<"Teste 2"<<endl;

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
class Tree {
private:
    MCNode * node;
public:
    Tree(MCNode * node);
    MCNode * best_action(int simulations_number);
    MCNode * tree_policy();
    MCNode * select();
};
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
    }
    
    return this->node->get_best_child(0.);
}

MCNode * Tree::select(){
    MCNode * current_node = this->node;
    while(current_node->is_fully_expanded() && current_node->contains_child())
        current_node = this->node->get_best_child(sqrt(2));
    return current_node;
}

MCNode * Tree::tree_policy(){
    MCNode * current_node = this->node;
    int level = 0;
    while(!current_node->is_terminal())
    {
        if(!current_node->is_fully_expanded())
            return current_node->expand();
        else
            current_node = current_node->get_best_child(sqrt(2));

        level++;

    }
    return current_node;
}
int main()
{
    int playerCount; // the amount of players (always 2)
    int myId; // my player ID (0 or 1)
    int zoneCount; // the amount of zones on the map
    int linkCount; // the amount of links between all zones
    cin >> playerCount >> myId >> zoneCount >> linkCount; cin.ignore();
    //cerr << playerCount <<" "<<myId<<" "<<zoneCount<<" "<<linkCount<<endl;
    int **connections = new int*[zoneCount];
    for(int i = 0; i < zoneCount; i++)
    {
        connections[i] = new int[6];
        for(int j = 0; j < 6; j++ )
        {

            connections[i][j] = -1;

        }
    }

    int idZoneEnemy = 0;
    bool findEnemy = false;
    for (int i = 0; i < zoneCount; i++) {
        int zoneId; // this zone's ID (between 0 and zoneCount-1)
        int platinumSource; // Because of the fog, will always be 0
        cin >> zoneId >> platinumSource; cin.ignore();
        //cerr << zoneId<<" "<<platinumSource<<endl;
    }
    for (int i = 0; i < linkCount; i++) {
        int zone1;
        int zone2;
        cin >> zone1 >> zone2; cin.ignore();
        //cerr<<zone1<<" "<<zone2<<endl;
        bool set_zone1 = false;
        bool set_zone2 = false;
        for(int j = 0; j < 6; j++)
        {
            if(connections[zone1][j] == -1 && !set_zone1){

                connections[zone1][j] = zone2;
                set_zone1 = true;
            }
            if(connections[zone2][j] == -1 && !set_zone2){
                connections[zone2][j] = zone1;
                set_zone2 = true;
            }

        }

    }
    bool finded_enemy_base = false;
    bool finded_player_base = false;
    PlatinumRiftState state = PlatinumRiftState(connections, zoneCount, 0, 1);
    MCNode * root = new MCNode(state);
    MCNode * node_result;
    // game loop

    while (1) {

        int myPlatinum; // your available Platinum
        cin >> myPlatinum;
        cin.ignore();
        string result = "";
        for (int i = 0; i < zoneCount; i++) {
            int zId; // this zone's ID
            int ownerId; // the player who owns this zone (-1 otherwise)
            int podsP0; // player 0's PODs on this zone
            int podsP1; // player 1's PODs on this zone
            int visible; // 1 if one of your units can see this tile, else 0
            int platinum; // the amount of Platinum this zone can provide (0 if hidden by fog)
            cin >> zId >> ownerId >> podsP0 >> podsP1 >> visible >> platinum;
            //cin >> ownerId>>podsP0>>podsP1>>visible>>platinum>>zId;
            /*int platinum_aux = zId;
            zId = platinum;
            platinum = platinum_aux;*/
            //cerr<<zId<<" "<<ownerId<<" "<<podsP0<<" "<<podsP1<<" "<<visible<<" "<<platinum<<endl;
            int number_allies;
            int number_enemies;
            bool is_enemy = false;
            if(myId == 0 ){
                number_allies = podsP0;
                number_enemies = podsP1;
            }else{
                number_allies = podsP1;
                number_enemies = podsP0;
            }
            //cerr<<"Number enemies "<<number_enemies<<" "<<ownerId<<endl;
            bool is_allie = false;
            if(ownerId == myId)
            {
                is_allie = true;
            }
            else if(ownerId != -1)
            {
                is_enemy = true;    
            }
            
            
            PlatinumRiftTurn node;
            // cerr<<zId<<endl;
            if(!finded_enemy_base && number_enemies > 0)
            {
                finded_enemy_base = true;
                //cerr<<"Enemy "<<zId<<endl;
                node = PlatinumRiftTurn(zId, number_allies, number_enemies, is_allie, platinum, is_enemy, false);
            }
            else if(!finded_player_base && number_allies > 0)
            {
                finded_player_base = true;
                node = PlatinumRiftTurn(zId, number_allies, number_enemies, is_allie, platinum, is_enemy, true);
            }
            else
            {
                node = PlatinumRiftTurn(zId, number_allies, number_enemies, is_allie, platinum, is_enemy, false);
            }
            state.update_node(zId, node);
            cin.ignore();
        }
        int total_allie = 0;
        for(int i = 0; i < zoneCount; i++)
        {
            if(state.is_allied(i))
            {
                total_allie+=1;
            }
        }
        cerr<<"Total "<<total_allie<<endl;
        root = new MCNode(state);
        MCNode backup = *root;

        Tree tree = Tree(root);
        
        node_result = tree.best_action(5);
        
        for(int i = 0 ; i < zoneCount; i++)
        {
            if(node_result->get_state().get_number_comming_allies(i) > 0){
                //cerr<<i<<" "<<node_result->get_state().get_send_id(i)<<" "<<node_result->get_state().get_number_comming_allies(i)<<endl;
                result += to_string(node_result->get_state().get_number_comming_allies(i))+" "+to_string(i) + " " + to_string(node_result->get_state().get_send_id(i)) ;
                result += " ";
            }
            
       }
        
        cout<<result<<endl<<"WAIT"<<endl;

    }

    return 0;
}
