#include "Gameboard.hpp"

void playerStartingPhase(Player& player)
{
    std::cout << player.getName() << "'s starting phase." << std::endl;
    player.untapEverything();
    player.drawFateCard();
    player.revealProvinces();
    player.printHand();
    player.printProvinces();
}



void Gameboard::starting_phase(void)
{
    std::cout << "\nStarting Phase!\n" << std::endl;
    list<Player*>::iterator it;
    for (it = Players.begin(); it != Players.end(); it++)
    {
        playerStartingPhase(**it);
    }
}