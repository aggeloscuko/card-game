#include <iostream>
#include "Card.hpp"
using std::string;
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////     class Card    //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//Constructor
Card::Card(const string& name, const int& cost, const bool& isTapped)
: name(name), cost(cost), isTapped(isTapped){}

//Get the name
string Card::get_name(void) const{
    return this->name;
}

//Get cost
int Card::get_cost(void) const{
    return this->cost;
}

//Get isTapped
bool Card::get_isTapped(void) const{
    return this->isTapped;
}

//Make isTapped 1 (true)
void Card::Tapped(void){
    this->isTapped = 1;
    return;
}

//Make isTapped 0 (false)
void Card::Untap(void){
    this->isTapped = 0;
    return;
}

//Print the data members of the card
void Card::printCard(void) const
{
    std::cout << "Card name: " << name << '\n'
              << "Cost: " << cost << std::endl;
    if (isTapped == 0)
    {
        std::cout << "Status: available\n" << std::endl;
    }
    else
    {
        std::cout << "Status: unavailable\n" << std::endl;
    }
}





//////////////////////////////////////////////////////////////////////////////////
//////////////////////////     class GreenCard    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

GreenCard::GreenCard(const string& name, const int& cost, const bool& isTapped, const int& attackBonus, const int& defenseBonus, const int& effectCost, const int& effectBonus, const int& minimumHonour, const string& cardText, const GreenCardType& type)
:Card(name, cost, isTapped) , attackBonus(attackBonus), defenseBonus(defenseBonus), effectCost(effectCost), effectBonus(effectBonus), minimumHonour(minimumHonour), cardText(cardText), type(type){}

//Get attackBonus
int GreenCard::get_attackBonus(void) const{
    return this->attackBonus;
}

//Get defenseBonus
int GreenCard::get_defenseBonus(void) const{
    return this->defenseBonus;
}

//Get minimumHonour
int GreenCard::get_minimumHonour(void) const{
    return this->minimumHonour;
}

//Get cardText
string GreenCard::get_cardText(void) const{
    return this->cardText;
}

//Get type
GreenCardType GreenCard::getType(void) const{
    return this->type;
}

//Get effectCost
int GreenCard::get_effectCost(void) const{
    return this->effectCost;
}

//Get effectBonus
int GreenCard::get_effectBonus(void) const{
    return this->effectBonus;
}

//Activate the effect
void GreenCard::activate_effect(void){
    int bonus = this->get_effectBonus();
    this->attackBonus += bonus;
    this->defenseBonus += bonus;
}

void GreenCard::printCard(void) const
{
    Card::printCard();
    if (type == FOLLOWER)
    {
        std::cout << "Card type: Follower" << std::endl;
    }
    else
    {
        std::cout << "Card type: Item" << std::endl;
    }
    
    std::cout << "Attack bonus: " << attackBonus << '\n'
              << "Defence bonus: " << defenseBonus << '\n'
              << "Minimum honour required: " << minimumHonour << '\n'
              << "Effect bonus: " << effectBonus << '\n'
              << "Effect cost: " << effectCost << '\n'
              << "Text: " << cardText << std::endl;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////     class BlackCard    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//Constructor
BlackCard::BlackCard(const string& name, const int& cost, const bool& isTapped, const bool& isRevealed, const BlackCardType& type)
:Card(name,cost,isTapped), isRevealed(isRevealed), type(type){}

//Get isRevealed
bool BlackCard::get_isRevealed(void) const{
    return this->isRevealed;
}

//Make the bool value of isRevealed 1 (true)
void BlackCard::Revealed(void){
    this->isRevealed = 1;
    return;
}

//Make the bool value of isRevealed 0 (false)
void BlackCard::Hidden(void){
    this->isRevealed = 0;
    return;
}

//Get type
BlackCardType BlackCard::getType(void) const{
    return this->type;
}

void BlackCard::printCard(void) const
{
    Card::printCard();
    if (type == PERSONALITY)
    {
        std::cout << "Type: Personality" << std::endl;
    }
    else if (type == HOLDING)
    {
        std::cout << "Type: Holding" << std::endl;
    }
    else
    {
        std::cout << "Type: Stronghold" << std::endl;
    }

    if (isRevealed == 1)
    {
        std::cout << "Revealed" << std::endl;
    }
    else
    {
        std::cout << "Hidden" << std::endl;
    }
    
}

//virtual function
int BlackCard::get_money(void) const
{}

//virtual function
int BlackCard::get_harvestValue(void) const
{}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////     class Stronghold    ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//Initiliaze cost:0 , starting_honour:5, initialDefense:5, money:5 , name:"Stronghold"
Stronghold::Stronghold()
:BlackCard("Stronghold", 0, 0, 0, STRONGHOLD), starting_honour(5), initialDefense(5), money(5){}

int Stronghold::get_honour(void) const{
    return this->starting_honour;
}

int Stronghold::get_initialDefense(void) const{
    return this->initialDefense;
}

int Stronghold::get_money(void) const{
    return this->money;
}

void Stronghold::printCard(void) const
{
    BlackCard::printCard();
    std::cout << "Starting honour: " << starting_honour << '\n'
              << "Initial defence: " << initialDefense << '\n'
              << "Harvest value: " << money << std::endl;
}