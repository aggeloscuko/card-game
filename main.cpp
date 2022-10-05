#include <iostream>
#include "Gameboard.hpp"

using namespace std;

int main(void){
    int num_of_players;
    cout << "Enter number of players:";
    cin >> num_of_players;
    cout << endl;
    Gameboard gameboard(num_of_players);
    cout << "Starting game!" << endl << endl;

    do{
        gameboard.starting_phase();
        gameboard.equip_phase();
        gameboard.battle_phase();
        gameboard.economy_phase();

    }while (gameboard.final_phase() == false);

}