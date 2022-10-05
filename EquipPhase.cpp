#include <iostream>
#include "Card.hpp"
#include "Personality.hpp"
#include "Item.hpp"
#include "Follower.hpp"
#include "Gameboard.hpp"
#include "TypeConverter.hpp"

using std::advance;
using std::cout;
using std::cin;
using std::endl;

void playerEquipPhase(Player& player)
{
    cout << player.getName() << "'s equip phase." << endl;
    player.printArmy();
    cout << '\n' << endl;
    player.printHoldings();
    cout << "\nPlayer's money: " << player.getMoney() << "\n\n" << endl;
    int p, f, i;
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
        cout << "Enter the number of the Personality you want to equip a Fate Card to and the number of that Fate Card (enter '0 0' to pass): ";
        cin >> p >> f;
        if (p == 0 && f == 0)
        {
            break;
        }
        else if(p > 0 && p <= player.getArmy()->size() && f > 0 && f <= player.getHand()->size())
        {
            list<Personality*>::iterator it;
            list<GreenCard*>::iterator it2;
            it = player.getArmy()->begin();
            it2 = player.getHand()->begin();
            advance(it, p-1);
            advance(it2, f-1);
            if (player.getMoney() >= (*it2)->get_cost())
            {
                if ((*it)->get_honour() >= (*it2)->get_minimumHonour())
                {
                    GreenCard* card = *it2;
                    Follower* follow;
                    Item* item;
                    TypeConverter typeconv;
                    typeconv.getCorrectType(card, &follow, &item);
                    if (follow == nullptr)
                    {
                        if ((*it)->get_Item_equips()->size() < (*it)->get_max_items())
                        {
                            player.reduceMoney(item->get_cost());
                            (*it)->Equip(*item);
                            cout << "Item equipped successfully! Would you like to upgrade the Item at the cost of "
                                << item->get_effectCost() << "? (enter '1' for 'yes', '0' for 'no')" << endl;
                            int bonus;
                            cin >> bonus;
                            if (bonus == 1 && player.getMoney() >= item->get_effectCost())
                            {
                                item->activate_effect();
                                player.reduceMoney(item->get_effectCost());
                                cout << "Item upgraded successfully!\n" << endl;
                            }
                            else if(bonus == 1 && player.getMoney() < item->get_effectCost())
                            {
                                cout << "You don't have enough money to upgrade the Item.\n" << endl;
                            }
                        }
                        else
                        {
                            cout << "Your Personality has reached the maximum number of equipped Items! The Item cannot be equipped!\n" << endl;
                        }
                    }
                    else
                    {
                        if ((*it)->get_Follower_equips()->size() < (*it)->get_max_followers())
                        {
                            player.reduceMoney(follow->get_cost());
                            (*it)->Equip(*follow);
                            cout << "Follower equipped successfully! Would you like to upgrade the Follower at the cost of "
                                << follow->get_effectCost() << "? (enter '1' for 'yes', '0' for 'no')" << endl;
                            int bonus;
                            cin >> bonus;
                            if (bonus == 1 && player.getMoney() >= follow->get_effectCost())
                            {
                                follow->activate_effect();
                                player.reduceMoney(follow->get_effectCost());
                                cout << "Follower upgraded successfully!\n" << endl;
                            }
                            else if(bonus == 1 && player.getMoney() < follow->get_effectCost())
                            {
                                cout << "You don't have enough money to upgrade the Follower.\n" << endl;
                            }
                        }
                        else
                        {
                            cout << "Your Personality has reached the maximum number of equipped Followers! The Follower cannot be equipped!\n" << endl;
                        }
                    }
                }
                else
                {
                    cout << "The Personality's honour is too low.\n" << endl;
                }
            }
            else
            {
                cout << "You don't have enough money.\n" << endl;
            }
        }
        else
        {
            cout << "Wrong input!\n" << endl;
        }
    } while (p!= 0 && f != 0);
    player.noMoney();
}








void Gameboard::equip_phase(void)
{
    std::cout << "\nEquip Phase!\n" << std::endl;
    list<Player*>::iterator it;
    for (it = Players.begin(); it != Players.end(); it++)
    {
        playerEquipPhase(**it);
    }
}