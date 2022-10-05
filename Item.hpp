#pragma once

#include "Card.hpp"

class Item: public GreenCard{
private:
    int durability;
public:

    Item(const string& name, const int& cost, const bool& isTapped, const int& attackBonus, const int& defenseBonus, const int& effectCost, const int& effectBonus, const int& minimumHonour, const string& cardText, const int& durability);

    //Get durability
    int get_durability(void) const;

    //Reduce durability by 1
    void reduce_durability(void);

    void printCard(void) const;
};

class Katana: public Item{
public:
    //Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
    Katana(const string& name);
};

class Spear: public Item{
public:
    //Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
    Spear(const string& name);
};

class Bow: public Item{
public:
    //Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
    Bow(const string& name);
};

class Ninjato: public Item{
public:
    //Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
    Ninjato(const string& name);
};

class Wakizashi: public Item{
public:
    //Initialise Cost:2, attackBonus:2, defenseBonus:0, effectCost:2, effectBonus:1 minimumHonour:1, durability:3
    Wakizashi(const string& name);
};