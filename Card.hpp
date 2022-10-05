#pragma once

#include <string>
using std::string;

class Card{
private:
    string name;
    int cost;
    bool isTapped;

public:

    //Constructor
    Card(const string& name, const int& cost, const bool& isTapped);

    //Get the name
    string get_name(void) const;

    //Get cost
    int get_cost(void) const;

    //Get isTapped
    bool get_isTapped(void) const;

    //Make isTapped 1 (true)
    void Tapped(void);

    //Make isTapped 0 (false)
    void Untap(void);

    void printCard(void) const;

};

enum GreenCardType { FOLLOWER, ITEM};

class GreenCard: public Card{
private:
    GreenCardType type;
    int attackBonus;
    int defenseBonus;
    int minimumHonour;
    int effectCost;
    int effectBonus;
    string cardText;

public:

    GreenCard(const string& name, const int& cost, const bool& isTapped, const int& attackBonus, const int& defenseBonus, const int& effectCost, const int& effectBonus, const int& minimumHonour, const string& cardText, const GreenCardType& type);

    //Get attackBonus
    int get_attackBonus(void) const;

    //Get defenseBonus
    int get_defenseBonus(void) const;

    //Get minimumHonour
    int get_minimumHonour(void) const;

    //Get cardText
    string get_cardText(void) const;

    //Get type
    GreenCardType getType(void) const;

    //Get effectCost
    int get_effectCost(void) const;

    //Get effectBonus
    int get_effectBonus(void) const;

    //Activate the effect
    void activate_effect(void);

    void printCard(void) const;

};


enum BlackCardType { PERSONALITY, HOLDING, STRONGHOLD};

class BlackCard: public Card{
private:
    bool isRevealed;
    BlackCardType type;

public:

    //Constructor
    BlackCard(const string& name, const int& cost, const bool& isTapped, const bool& isRevealed, const BlackCardType& type);

    //Get isRevealed
    bool get_isRevealed(void) const;

    //Make the bool value of isRevealed 1 (true)
    void Revealed(void);

    //Get type
    BlackCardType getType(void) const;

    //Make the bool value of isRevealed 0 (false)
    void Hidden(void);

    void printCard(void) const;

    virtual int get_money(void) const;
    virtual int get_harvestValue(void) const;
};

//TODO: Decide whether to add more features to Stronghold
class Stronghold: public BlackCard{
private:
    int starting_honour;
    int initialDefense;
    int money;

public:
    //Initiliaze cost:0 , starting_honour:5, initialDefense:5, money:5 , name:"Stronghold"
    Stronghold();

    int get_honour(void) const;

    int get_initialDefense(void) const;

    int get_money(void) const;

    void printCard(void) const;
};