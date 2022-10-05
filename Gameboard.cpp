 #include "Gameboard.hpp"
 #include <string>

 using std::to_string;

bool sorting_with_honour(Player* player1, Player* player2){
    return player1->getHonour() > player2->getHonour();
}

 //Number of players in the Game
Gameboard::Gameboard(const int& num_of_players){

    int counter = 0;

    while (counter < num_of_players){
        counter++;
        Players.push_back(new Player("Player" + to_string(counter)));
    }
    //
    Players.sort(sorting_with_honour);

}

Gameboard::~Gameboard(){
    list<Player*>::iterator it;
    for (it = Players.begin() ; it != Players.end() ; it++){
        if ((*it) != nullptr) delete (*it);
    }
}

string Gameboard::get_winner_name(void) const{
    //If there is a winner, then the list pf Players will contain only the player who has won (A player who has lost is removed from the list)
    return this->Players.front()->getName();
}


bool Gameboard::checkWinningCondition(void) const
{
    if (Players.size() == 1)
    {
        std::cout << get_winner_name() << " is the winner!" << std::endl;
        return 1;
    }
    else
    {
        return 0;
    }
}