//
// Created by dev04 on 7/25/19.
//

#include "PlatinumRiftTurn.h"

PlatinumRiftTurn::PlatinumRiftTurn(int id, int number_allies, int number_enemies, bool is_allie, int number_platinum, bool is_enemy_base, bool is_allied_base){
    this->number_allies = number_allies;
    this->number_enemies = number_enemies;
    this->is_allie = is_allie;
    this->number_platinum = number_platinum;
    this->allied_base = is_allied_base;
    this->enemy_base = is_enemy_base;
    this->id = id;
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
bool PlatinumRiftTurn::is_enemy_base() {
    return this->enemy_base;
}
bool PlatinumRiftTurn::is_allied_base(){
    return this->allied_base;
}
bool PlatinumRiftTurn::is_allied() {
    return this->is_allie;
}