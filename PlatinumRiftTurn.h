//
// Created by dev04 on 7/25/19.
//

#ifndef MCST_PLATINUMRIFTTURN_H
#define MCST_PLATINUMRIFTTURN_H


class PlatinumRiftTurn {
private:
    int number_allies, number_enemies, number_platinum;
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
    int get_number_allies();
    int get_number_enemies();
    int get_number_platinum();
    bool is_enemy_base();
    bool is_allied_base();
    bool is_allied();

};


#endif //MCST_PLATINUMRIFTTURN_H
