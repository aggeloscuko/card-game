#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <string>
#include <list>
#include "DeckBuilder.hpp"
#include "Card.hpp"
#include "Holding.hpp"
#include "Personality.hpp"
#include "Province.hpp"

using std::list;

class Player
{
    const int maxHand = 6;              //maximum number of fate cards in player's hand
    const int numberOfProvinces = 4;
    string name;
    DeckBuilder deckbuilder;
    Stronghold stronghold;
    int honour;
    int money;
    list<Province*>* provinces;
    list<GreenCard*>* fateDeck;
    list<BlackCard*>* dynastyDeck;
    list<GreenCard*>* hand;
    list<BlackCard*>* holdings;
    list<Personality*>* army;
public:
    Player(string);
    ~Player();

    string getName(void) const;
    int getMoney(void) const;
    int getHonour(void) const;
    int getMaxHand(void) const;
    list<BlackCard*>* getHoldings(void) const;
    list<Province*>* getProvinces(void) const;
    Province getFirstProvince(void) const;
    list<Personality*>* getArmy(void) const;
    list<GreenCard*>* getHand(void) const;
    list<BlackCard*>* getDynastyDeck(void) const;
    void addMoney(int);
    void reduceMoney(int);
    void noMoney(void);                             //set money equal to 0
    void untapEverything(void);
    void drawFateCard(void);
    void removeFirstProvince(void);
    void removeDeadArmy(void);                      //removes all dead personalities from player's army
    void revealProvinces(void);
    void printHand(void) const;
    void printProvinces(void) const;
    void printHoldings(void) const;
    void printArmy(void) const;
    void printAvailableArmy(void) const;            //prints all personalities in the army that are not tapped
    bool armyIsAvailable(void) const;               //returns 1 if there is an untapped personality in the army, else 0
    void discardSurplusFateCards(void);
};

#endif