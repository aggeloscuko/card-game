#include <iostream>
#include "Gameboard.hpp"

using std::advance;
using std::cout;
using std::endl;
using std::cin;

void playerEconomyPhase(Player& player)
{
    std::cout << player.getName() << "'s economy phase." << std::endl;
    player.printProvinces();
    player.printHoldings();
    cout << "\nPlayer's money: " << player.getMoney() << "\n\n" << endl;
    int i;
    do
    {
        cout << "Enter the number of the holding you want to tap (enter '0' to pass): ";
        cin >> i;
        if (i == 0)
        {
            break;
        }
        else if (i < 0 || i > player.getHoldings()->size())
        {
            cout << "\nWrong input.\n" << endl;
            continue;
        }
        
        list<BlackCard*>::iterator it;
        it = player.getHoldings()->begin();
        advance(it, i-1);
        if (!(*it)->get_isTapped() && i == 1)
        {
            (*it)->Tapped();
            player.addMoney(dynamic_cast<Stronghold*>(*it)->get_money());
            cout << "\nCard tapped successfully.\n" << endl;
        }
        else if (!(*it)->get_isTapped() && i != 1)
        {
            (*it)->Tapped();
            player.addMoney(dynamic_cast<Holding*>(*it)->get_harvestValue());
            cout << "\nCard tapped successfully.\n" << endl;
        }
        else
        {
            cout << "\nThe card is already tapped!\n" << endl;
        }
    } while (i != 0);

    do
    {
        cout << "Enter the number of the card you want to buy (enter '0' to pass): ";
        cin >> i;
        if (i == 0)
        {
            break;
        }
        else if (i < 0 || i > player.getProvinces()->size())
        {
            cout << "\nWrong input.\n" << endl;
            continue;
        }
        
        list<Province*>::iterator it2;
        it2 = player.getProvinces()->begin();
        advance(it2, i-1);

        if ((*it2)->getIsRevealed())
        {
            if (player.getMoney() >= (*it2)->getAvailable()->get_cost())
            {
                player.reduceMoney((*it2)->getAvailable()->get_cost());
                if ((*it2)->getAvailable()->getType() == HOLDING)
                {
                    player.getHoldings()->push_back((*it2)->getAvailable());
                    (*it2)->nextBlackCard(player.getDynastyDeck());
                    cout << "\nPurchase made successfully.\n" << endl;
                }
                else if ((*it2)->getAvailable()->getType() == PERSONALITY)
                {
                    player.getArmy()->push_back(dynamic_cast<Personality*>((*it2)->getAvailable()));
                    (*it2)->nextBlackCard(player.getDynastyDeck());
                    cout << "\nPurchase made successfully.\n" << endl;
                }
            }
            else
            {
                cout << "\nNot enough money!\n" << endl;
                continue;
            }
        }
        else
        {
            cout << "\nThe card is not revealed!\n" << endl;
            continue;
        }
        
        
    } while (i != 0);
    player.noMoney();
}






void Gameboard::economy_phase(void)
{
    std::cout << "\nEconomy Phase!\n" << std::endl;
    list<Player*>::iterator it;
    for (it = Players.begin(); it != Players.end(); it++)
    {
        playerEconomyPhase(**it);
    }
}