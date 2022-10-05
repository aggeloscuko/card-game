#include <iostream>
#include "Holding.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////     class Holding    ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//Constructor, upperHolding, subHolding initialized to nullptr
Holding::Holding(const string& name, const int& cost, const bool& isTapped, const bool& isRevealed, const int& harvestValue, const HoldingType& holding_type)
:BlackCard(name, cost, isTapped, isRevealed, HOLDING), harvestValue(harvestValue), upperHolding(nullptr), subHolding(nullptr), holding_type(holding_type){}

int Holding::get_original_harvestValue(void) const{
    return this->harvestValue;
}

//pure virtual function
//Get harvestValue including chain reaction benefits
//Depending on what Holding card it is, the chain reactions change so the definition of the function must be defined on each Holding card seperately
int Holding::get_harvestValue(void) const
{}

//Get upperHolding
Holding* Holding::get_upperHolding(void) const{
    return this->upperHolding;
}

//get subHolding
Holding* Holding::get_subHolding(void) const{
    return this->subHolding;
}

//set the value of upperHolding
void Holding::set_upperHolding(Holding* pHolding){
    this->upperHolding = pHolding;
}

//Set the value of subHolding
void Holding::set_subHolding(Holding* pHolding){
    this->subHolding = pHolding;
}

//Get type
HoldingType Holding::get_holding_type(void) const{
    return this->holding_type;
}


void Holding::printCard(void) const
{
    BlackCard::printCard();
    std::cout << "Harvest value: " << harvestValue << std::endl;
    if (upperHolding != nullptr)
    {
        std::cout << "Upper Holding: " << upperHolding->get_name() << std::endl;
    }
    else
    {
        std::cout << "No Upper Holding" << std::endl;
    }
    if (subHolding != nullptr)
    {
        std::cout << "Sub Holding: " << subHolding->get_name() << std::endl;
    }
    else
    {
        std::cout << "No Sub Holding." << std::endl;
    }
}

// connects two holdings, holding1 -> (upperholding) holding2,  holding2-> (subholding) holding1
void connect_holdings(Holding& holding1, Holding& holding2){
    holding1.set_upperHolding(&holding2);
    holding2.set_subHolding(&holding1);

}


//Constructors for Holding Card types


//initialize Cost:2 , harvestValue:2, isTapped:0, isRevealed:0
Plain::Plain(const string& name)
:Holding(name,5,0,0,2, PLAIN){}

//No chains for Plain
int Plain::get_harvestValue(void) const{
    return this->get_original_harvestValue();
}



//initialize Cost:3 , harvestValue:4, isTapped:0, isRevealed:0
Farmland::Farmland(const string& name)
:Holding(name,3,0,0,4, FARMLAND){}

//No chains for Farmland
int Farmland::get_harvestValue(void) const{
    return this->get_original_harvestValue();
}

//initialize Cost:5 , harvestValue:3, isTapped:0, isRevealed:0
Mine::Mine(const string& name)
:Holding(name,5,0,0,3, MINE){}

//Check all chain possibilities for bonus points
int Mine::get_harvestValue(void) const{
    if (this->get_subHolding() != nullptr){
        //Error
    }
    //The only possible upperHolding for a mine is a GoldMine
    if (this->get_subHolding() != nullptr){
        return this->get_original_harvestValue() + 2;
    }
    //No chain combo bonuses
    return this->get_original_harvestValue();
}

//initialize Cost:7 , harvestValue:5, isTapped:0, isRevealed:0
GoldMine::GoldMine(const string& name)
:Holding(name,7,0,0,5, GOLDMINE){}

//Check all chain possibilities for bonus points
int GoldMine::get_harvestValue(void) const{
    //Only possible subHolding is the Mine
    if (this->get_subHolding() != nullptr){

        //If it is also connected to the CrystalMine (the only possible upperHolding)
        if (this->get_upperHolding() != nullptr){
            return 2 * this->get_original_harvestValue();
        }
        //Otherwise it is connected only to the Mine
        else{
            return this->get_original_harvestValue() + 4;
        }
    }
    //It is not connected to a Mine
    //If it is connected to a CrystalMine
    if (this->get_upperHolding() != nullptr){
        return this->get_original_harvestValue() + 5;
    }
    //It is not connected to a Mine and CrystalMine
    else{
        return this->get_original_harvestValue();
    }
}

//initialize Cost:12 , harvestValue:6, isTapped:0, isRevealed:0
CrystalMine::CrystalMine(const string& name)
:Holding(name,12,0,0,6, CRYSTALMINE){}

//Check all chain possibilities for bonus points
int CrystalMine::get_harvestValue(void) const{
    //Only possible subHolding is the GoldMine
    if (this->get_subHolding() != nullptr){

        //If the GoldMine is also connected to the MineMine (completing the chain)
        if ((this->get_subHolding())->get_subHolding() != nullptr){
            return 3 * this->get_original_harvestValue();
        }
        //Otherwise it is connected only to the GoldMine
        else{
            return 2 * this->get_original_harvestValue();
        }
    }
    //It is not connected to a GoldMine
    //If it is connected to a CrystalMine
    return this->get_original_harvestValue();
}

//initialize Cost:2 , harvestValue:2, isTapped:0, isRevealed:0
GiftsandFavour::GiftsandFavour(const string& name)
:Holding(name,2,0,0,2, GIFTSANDFAVOUR){}

int GiftsandFavour::get_harvestValue(void) const{
    return this->get_original_harvestValue();
}