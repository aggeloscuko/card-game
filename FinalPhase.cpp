#include <iostream>
#include "Gameboard.hpp"

void playerFinalPhase(Player& player)
{
    std::cout << player.getName() << "'s final phase." << std::endl;
    if (player.getHand()->size() > player.getMaxHand())
    {
        player.discardSurplusFateCards();
    }
    player.printHand();
    player.printProvinces();
    player.printArmy();                 //printArena()
    player.printHoldings();
}



bool Gameboard::final_phase(void)
{
    std::cout << "\nFinal Phase!\n" << std::endl;
    list<Player*>::iterator it;
    for (it = Players.begin(); it != Players.end(); it++)
    {
        playerFinalPhase(**it);
    }
    return checkWinningCondition();
}