#include "Player.hpp"

//The Gameboard. It contains all the players in the game in a list and contains all the phases of each round




//Encodes what decisions the player has done during his battle phase
enum PlayerBattleState { INITIAL_STATE, END_TURN};
//INITIAL_STATE: the player has not chosen to attack
//END_TURN: Player's turn has ended



class Gameboard{
private:
    list<Player*> Players;

public:
    //Number of players in the Game
    Gameboard(const int& num_of_players);

    void starting_phase(void);

    void equip_phase(void);

    void battle_phase(void);

    void economy_phase(void);

    bool final_phase(void);

    //Handles the input of the user
    //input is the command the player typed.
    //state is the current state of the player (explanation of each state in the enum definition above)
    //Player is the player who gave the input
    PlayerBattleState handling_input(string input, PlayerBattleState state, Player* player);

    //Checks if there is a winner and prints the necessary messages
    bool checkWinningCondition(void) const;

    //Check if a person has won the game
    string get_winner_name(void) const;

    ~Gameboard();
};
