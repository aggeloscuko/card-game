#include <iostream>
#include "Item.hpp"


Item::Item(const string& name, const int& cost, const bool& isTapped, const int& attackBonus, const int& defenseBonus, const int& effectCost, const int& effectBonus, const int& minimumHonour, const string& cardText, const int& durability)
:GreenCard(name, cost, isTapped, attackBonus, defenseBonus, effectCost, effectBonus, minimumHonour, cardText, ITEM), durability(durability){}

//Get durability
int Item::get_durability(void) const{
    return this->durability;
}

//Reduce durability by 1
void Item::reduce_durability(void){
    durability -= 1;
    return;
}

void Item::printCard(void) const
{
    GreenCard::printCard();
    std::cout << "Durability: " << durability << '\n' << std::endl;
}

//Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
Katana::Katana(const string& name)
:Item(name, 2, 0, 2, 0, 2, 1, 1, "Katana text", 3){}


//Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
Spear::Spear(const string& name)
:Item(name, 2, 0, 2, 0, 2, 1, 1, "Spear text", 3){}



//Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
Bow::Bow(const string& name)
:Item(name, 2, 0, 2, 0, 2, 1, 1, "Bow text", 3){}

//Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
Ninjato::Ninjato(const string& name)
:Item(name, 2, 0, 2, 0, 2, 1, 1, "Ninjato text", 3){}

//Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
Wakizashi::Wakizashi(const string& name)
:Item(name, 2, 0, 2, 0, 2, 1, 1, "Wakizashi text", 3){}