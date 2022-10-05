#include <iostream>
#include "Personality.hpp"
#include <iterator>

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////     class Personality    //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//Constructor
Personality::Personality(const string& name, const int& cost, const bool& isTapped, const bool& isRevealed, const int& attack, const int& defense, const int& honour, const bool& isDead, const int& max_items, const int& max_followers)
:BlackCard(name, cost, isTapped, isRevealed, PERSONALITY), attack(attack), defense(defense), honour(honour), isDead(isDead),max_items(max_items), max_followers(max_followers){
    Items = new vector<Item>();
    Followers = new vector<Follower>();
}

//Get attack
int Personality::get_original_attack(void) const{
    return this->attack;
}

//Get defence
int Personality::get_original_defense(void) const{
    return this->defense;
}

//get honour
int Personality::get_honour(void) const{
    return this->honour;
}

//Get isDead
bool Personality::get_isDead(void) const{
    return this->isDead;
}

//Personality dies (in battle of performs Seppuku)
void Personality::Dead(void){
    this->isDead = 1;
    return;
}

//Equip an item to the personality
void Personality::Equip(const Item& item){
    this->Items->push_back(item);
}

//Equip a follower to a personality
void Personality::Equip(const Follower& follower){
    this->Followers->push_back(follower);
}

//Unequip last follower (the last in the vector<Follower>)
void Personality::unequip_last_follower(void){
    this->Followers->pop_back();
}

//Get last follower (the last in vector<Follower>)
Follower Personality::get_last_follower(void) const{
    return this->Followers->back();
}

//Check if there are followers equipped to the personality
bool Personality::is_equipped_to_followers(void) const{
    return !this->Followers->empty();
}

//get attack including attack bonuses gained from followers and items (used in battle) (reduces durability of the items and removes them if necessary)
int Personality::get_attack(void) const{
    int attack = this->get_original_attack();  //Initialise the attack power

    //Add the bonus attack points given by the Items and Followers

    for (vector<Item>::iterator it = Items->begin() ; it != this->Items->end() ;){
        attack += (*it).get_attackBonus();

        //get_attack() function is used only when a personality attacks in the battle phase so reduce the durabity of items here and remove them if needed
        (*it).reduce_durability();
        if ((*it).get_durability() == 0) it = Items->erase(it);   //If the durability of the item drops to zero then the item breaks (Unequip)
        else it++;
    }

    for (vector<Follower>::iterator it = Followers->begin() ; it != Followers->end() ; it++){
        attack += (*it).get_attackBonus();
    }

    return attack;
}

//get defense including defense bonuses gained from followers and items (used in battle) (reduces durability of the items and removes them if necessary)
int Personality::get_defense(void) const{
    int defense = this->get_original_attack();  //Initialise the defense value

    //Add the bonus defense points given by the Items and Followers

    for (vector<Item>::iterator it = Items->begin() ; it != this->Items->end() ;){
        defense += (*it).get_defenseBonus();

        //get_defense() function is used only when a personality defends in the battle phase so reduce the durabity of items here and remove them if needed
        (*it).reduce_durability();
        if ((*it).get_durability() == 0) it = Items->erase(it);   //If the durability of the item drops to zero then the item breaks (Unequip)
        else it++;
    }

    for (vector<Follower>::iterator it = Followers->begin() ; it != Followers->end() ; it++){
        defense += (*it).get_defenseBonus();
    }

    return defense;
}

//Get Item equips (a pointer to a vector containing all Items that are equiped to a personality)
vector<Item>* Personality::get_Item_equips(void) const{
    return this->Items;
}

//Get Follower equips (a pointer to a vector containing all Foloowers that are equiped to a personality)
vector<Follower>* Personality::get_Follower_equips(void) const{
    return this->Followers;
}

//If a personality loses a battle, it loses 1 honour
void Personality::reduce_honour(void){
    this->honour -= 1;

    //If he becomes dishonored
    if (this->honour == 0){
        this->Dead();       //Performs Seppuku
    }
}

//Get capacity of item equips
int Personality::get_max_items(void) const{
    return this->max_items;
}

//Get capacity of follower equips
int Personality::get_max_followers(void) const{
    return this->max_followers;
}


Personality::~Personality(){
    if (Followers != nullptr) delete Followers;
    if (Items != nullptr) delete Items;
}

void Personality::printCard(void) const
{
    BlackCard::printCard();
    std::cout << "Attack: " << attack << '\n'
              << "Defence: " << defense << '\n'
              << "Honour: " << honour << '\n'
              << "Condition: " << isDead << std::endl;
    if (Followers->empty())
    {
        std::cout << "No Followers" << std::endl;
    }
    else
    {
        std::cout << "      -Followers:" << std::endl;
        vector<Follower>::iterator it;
        for (it = Followers->begin(); it != Followers->end(); it++)
        {
            it->printCard();
        }
    }
    if (Items->empty())
    {
        std::cout << "No Items" << std::endl;
    }
    else
    {
        std::cout << "      -Items:" << std::endl;
        vector<Item>::iterator it2;
        for (it2 = Items->begin(); it2 != Items->end(); it2++)
        {
            it2->printCard();
        }
    }
}
//Constructors of Personality Card types

//initialize Cost:5 , Attack:3, Defence:2, Honour:2 , isTapped:0, isRevealed:0
Attacker::Attacker(const string& name)
:Personality(name,5,0,0,3,2,2,0){}

//initialize Cost:5 , Attack:2, Defence:3, Honour:2 , isTapped:0, isRevealed:0
Defender::Defender(const string& name)
:Personality(name,5,0,0,2,3,2,0){}

//initialize Cost:30 , Attack:20, Defence:20, Honour:12 , isTapped:0, isRevealed:0
Champion::Champion(const string& name)
:Personality(name,30,0,0,20,20,12,0){}

//initialize Cost:15 , Attack:5, Defence:10, Honour:8 , isTapped:0, isRevealed:0
Chancellor::Chancellor(const string& name)
:Personality(name,15,0,0,5,10,8,0){}

//initialize Cost:15 , Attack:10, Defence:5, Honour:8 , isTapped:0, isRevealed:0
Shogun::Shogun(const string& name)
:Personality(name,15,0,0,10,5,8,0){}