#include "MCNode.h"
#include "PlatinumRiftState.h"
#include "PlatinumRiftTurn.h"
#include "Tree.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
int main()
{
    int playerCount; // the amount of players (always 2)
    int myId; // my player ID (0 or 1)
    int zoneCount; // the amount of zones on the map
    int linkCount; // the amount of links between all zones

    int **connections = new int*[zoneCount];
    for(int i = 0; i < zoneCount; i++)
    {
        connections[i] = new int[6];
        for(int j = 0; j < 6; j++ )
        {
            connections[i][j] = -1;
        }
    }

    cin >> playerCount >> myId >> zoneCount >> linkCount; cin.ignore();

    int idZoneEnemy = 0;
    bool findEnemy = false;
    for (int i = 0; i < zoneCount; i++) {
        int zoneId; // this zone's ID (between 0 and zoneCount-1)
        int platinumSource; // Because of the fog, will always be 0
        cin >> zoneId >> platinumSource; cin.ignore();
    }
    for (int i = 0; i < linkCount; i++) {
        int zone1;
        int zone2;
        cin >> zone1 >> zone2; cin.ignore();
        for(int j = 0; j < 6; j++)
        {
            if(connections[zone1][j] == -1)
                connections[zone1][j] = zone2;
            if(connections[zone2][j] == -1)
                connections[zone2][j] = zone1;
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
            int number_allies;
            int number_enemies;

            if(myId == 0 ){
                number_allies = podsP0;
                number_enemies = podsP1;
            }else{
                number_allies = podsP1;
                number_enemies = podsP0;
            }
            bool is_allie = true;
            if(number_allies > number_enemies)
            {
                is_allie = true;
            }
            else
            {
                is_allie = false;
            }
            PlatinumRiftTurn node;
            if(!finded_enemy_base && number_enemies > 0)
            {
                finded_enemy_base = true;
                node = PlatinumRiftTurn(zId, number_allies, number_enemies, is_allie, platinum, true, false);
            }
            else if(!finded_player_base && number_allies > 0)
            {
                finded_player_base = true;
                node = PlatinumRiftTurn(zId, number_allies, number_enemies, is_allie, platinum, false, true);
            }
            else
            {
                node = PlatinumRiftTurn(zId, number_allies, number_enemies, is_allie, platinum, false, false);
            }
            state.update_node(zId, node);
            cin.ignore();
        }
        root = new MCNode(state);

        Tree tree = Tree(root);
        node_result = tree.best_action(1000);
        for(int i = 0 ; i < zoneCount; i++)
        {
            for(int j = 0; j < 6; j++)
            {
                if(node_result->get_state().get_number_allies(connections[i][j]) - root->get_state().get_number_allies(i) > 0)
                {
                    result += to_string(node_result->get_state().get_number_allies(connections[i][j]) - root->get_state().get_number_allies(i)) + " " + to_string(i) +" "+to_string(connections[i][j]);
                    result += " ";
                }
            }
        }
        cout<<result<<"WAIT"<<endl;


    }


    return 0;
}