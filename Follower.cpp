#include "Follower.hpp"

Follower::Follower(const string& name, const int& cost, const bool& isTapped, const int& attackBonus, const int& defenseBonus, const int& effectCost, const int& effectBonus, const int& minimumHonour, const string& cardText)
:GreenCard(name, cost, isTapped, attackBonus, defenseBonus, effectCost, effectBonus, minimumHonour, cardText, FOLLOWER){}

//
void Follower::printCard(void) const
{
    GreenCard::printCard();
}


//GreenCard Follower types

//initialize Cost:0, attackBonus:2, defenseBonus:0, minimumHonour:1, effectBonus:1, effectCost:2
Footsoldier::Footsoldier(const string& name)
:Follower(name, 0, 0, 2, 0, 2, 1, 1, "Archer text"){}

//initialize Cost:0, attackBonus:0, defenseBonus:2, minimumHonour:1, effectBonus:1, effectCost:2
Archer::Archer(const string& name)
:Follower(name, 0, 0, 0, 2, 2, 1, 1, "Archer text"){}


//initialize Cost:3, attackBonus:4, defenseBonus:2, minimumHonour:3, effectBonus:3, effectCost:4
Cavalry::Cavalry(const string& name)
:Follower(name, 3, 0, 4, 2, 4, 3, 3, "Cavalry text"){}

//initialize Cost:5, attackBonus:3, defenseBonus:3, minimumHonour:2, effectBonus:2, effectCost:3
Sieger::Sieger(const string& name)
:Follower(name, 5, 0, 3, 3, 3, 2, 2, "Sieger text"){}

//initialize Cost:3, attackBonus:2, defenseBonus:4, minimumHonour:3, effectBonus:3, effectCost:4
Naval::Naval(const string& name)
:Follower(name, 3, 0, 2, 4, 4, 3, 3, "Naval text"){}

//initialize Cost:8, attackBonus:8, defenseBonus:8, minimumHonour:6, effectBonus:3, effectCost:8
Bushido::Bushido(const string& name)
:Follower(name, 8, 0, 8, 8, 8, 3, 6, "Bushido text"){}