#pragma once

#include "Card.hpp"



enum HoldingType { PLAIN, FARMLAND, MINE, GOLDMINE, CRYSTALMINE, GIFTSANDFAVOUR};

class Holding: public BlackCard{
private:
    HoldingType holding_type; //Stores which card this Holding is
    int harvestValue;
    Holding* upperHolding;
    Holding* subHolding;

protected:
    //Accessor to harvestValue
    int get_original_harvestValue(void) const;

public:

    //Constructor, upperHolding, subHolding initialized to nullptr
    Holding(const string& name, const int& cost, const bool& isTapped, const bool& isRevealed, const int& harvestValue, const HoldingType& holding_type);

    //Get final harvestValue including chain benefits (if any)
    //Depending on what Holding card it is, the chain reactions change so the definition of the function must be defined on each Holding card seperately
    virtual int get_harvestValue(void) const = 0;

    //Get upperHolding
    Holding* get_upperHolding(void) const;

    //get subHolding
    Holding* get_subHolding(void) const;

    //set the value of upperHolding
    void set_upperHolding(Holding*);

    //Set the value of subHolding
    void set_subHolding(Holding*);

    //Get type
    HoldingType get_holding_type(void) const;

    void printCard(void) const;
};

// connects two holdings, holding1 -> (upperholding) holding2,  holding2-> (subholding) holding1
void connect_holdings(Holding& holding1, Holding& holding2);


class Plain: public Holding{
public:
    //initialize Cost:2 , harvestValue:2, isTapped:0, isRevealed:0
    Plain(const string& name);
    int get_harvestValue(void) const;

};

class Farmland: public Holding{
public:
    //initialize Cost:3 , harvestValue:4, isTapped:0, isRevealed:0
    Farmland(const string& name);
    int get_harvestValue(void) const;

};

class Mine: public Holding{
public:
    //initialize Cost:5 , harvestValue:3, isTapped:0, isRevealed:0
    Mine(const string& name);
    int get_harvestValue(void) const;

};

class GoldMine: public Holding{
public:
    //initialize Cost:7 , harvestValue:5, isTapped:0, isRevealed:0
    GoldMine(const string& name);
    int get_harvestValue(void) const;

};

class CrystalMine: public Holding{
public:
    //initialize Cost:12 , harvestValue:6, isTapped:0, isRevealed:0
    CrystalMine(const string& name);
    int get_harvestValue(void) const;

};

class GiftsandFavour: public Holding{
public:
    //initialize Cost:2 , harvestValue:2, isTapped:0, isRevealed:0
    GiftsandFavour(const string& name);
    int get_harvestValue(void) const;

};

