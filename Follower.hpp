#pragma once

#include "Card.hpp"


class Follower: public GreenCard{
public:
    Follower(const string& name, const int& cost, const bool& isTapped, const int& attackBonus, const int& defenseBonus, const int& effectCost, const int& effectBonus, const int& minimumHonour, const string& cardText);
    
    void printCard(void) const;
};

//GreenCard Follower types

class Footsoldier: public Follower{
public:

    //initialize Cost:0, attackBonus:2, defenseBonus:0, minimumHonour:1, effectBonus:1, effectCost:2
    Footsoldier(const string& name);

};

class Archer: public Follower{
public:

    //initialize Cost:0, attackBonus:0, defenseBonus:2, minimumHonour:1, effectBonus:1, effectCost:2
    Archer(const string& name);

};

class Sieger: public Follower{
public:

    //initialize Cost:0, attackBonus:0, defenseBonus:2, minimumHonour:1, effectBonus:1, effectCost:2
    Sieger(const string& name);

};

class Cavalry: public Follower{
public:

    //initialize Cost:5, attackBonus:3, defenseBonus:3, minimumHonour:2, effectBonus:2, effectCost:3
    Cavalry(const string& name);

};

class Naval: public Follower{
public:

    //initialize Cost:3, attackBonus:2, defenseBonus:4, minimumHonour:3, effectBonus:3, effectCost:4
    Naval(const string& name);

};

//Alternative name for Naval
typedef Naval Atakebune;

class Bushido: public Follower{
public:

    //initialize Cost:8, attackBonus:8, defenseBonus:8, minimumHonour:6, effectBonus:3, effectCost:8
    Bushido(const string& name);

};