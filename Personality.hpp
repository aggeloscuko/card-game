#pragma once

#include "Card.hpp"
#include "Item.hpp"
#include "Follower.hpp"
#include <vector>

using std::vector;


class Personality: public BlackCard{
private:
//TODO: Add (equips?) followers or items
    int attack;
    int defense;
    int honour;
    bool isDead;
    int max_items;      //capacity of item equips
    int max_followers;  //capacity of follower equips
    //Equips of a personality
    vector<Follower>* Followers;  //The equipped followers
    vector<Item>* Items;          //The equipped items

    //Get attack
    int get_original_attack(void) const;

    //Get defence
    int get_original_defense(void) const;

public:
    //Constructor
    Personality(const string& name, const int& cost, const bool& isTapped, const bool& isRevealed, const int& attack, const int& defense, const int& honour, const bool& isDead, const int& max_items = 4, const int& max_followers = 6);

    //get honour
    int get_honour(void) const;

    //Get isDead
    bool get_isDead(void) const;

    //Personality dies (in battle of performs Seppuku)
    void Dead(void);


    //Equip an item to the personality
    void Equip(const Item& item);

    //Equip a follower to a personality
    void Equip(const Follower& follower);

    //Unequip last follower (the last in the vector<Follower>)
    void unequip_last_follower(void);

    //Get last follower (the last in vector<Follower>)
    Follower get_last_follower(void) const;

    //Check if there are followers equipped to the personalit
    bool is_equipped_to_followers(void) const;

    //get attack including attack bonuses gained from followers and items
    int get_attack(void) const;

    //get defense including defense bonuses gained from followers and items
    int get_defense(void) const;

    //Get Item equips (a pointer to a vector containing all Items that are equiped to a personality)
    vector<Item>* get_Item_equips(void) const;

    //Get Follower equips (a pointer to a vector containing all Followers that are equiped to a personality)
    vector<Follower>* get_Follower_equips(void) const;

    //If a personality loses a battle, it loses 1 honour. If the honour becomes 0, the personality will be considered dead (seppuku)
    void reduce_honour(void);

    //Get capacity of item equips
    int get_max_items(void) const;

    //Get capacity of follower equips
    int get_max_followers(void) const;

    void printCard(void) const;

    ~Personality();

};

class Attacker: public Personality{
public:

    //initialize Cost:5 , Attack:3, Defence:2, Honour:2 , isTapped:0, isRevealed:0
    Attacker(const string& name);
};

class Defender: public Personality{
public:

    //initialize Cost:5 , Attack:2, Defence:3, Honour:2 , isTapped:0, isRevealed:0
    Defender(const string& name);
};

class Champion: public Personality{
public:

    //initialize Cost:30 , Attack:20, Defence:20, Honour:12 , isTapped:0, isRevealed:0
    Champion(const string& name);
};

class Chancellor: public Personality{
public:

    //initialize Cost:15 , Attack:5, Defence:10, Honour:8 , isTapped:0, isRevealed:0
    Chancellor(const string& name);
};

class Shogun: public Personality{
public:

    //initialize Cost:15 , Attack:10, Defence:5, Honour:8 , isTapped:0, isRevealed:0
    Shogun(const string& name);
};