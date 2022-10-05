#include <iostream>
#include "Player.hpp"

using std::cout;
using std::endl;

Player::Player(string playerName)
: name(playerName), honour(stronghold.get_honour()), money(stronghold.get_money())
{
    deckbuilder.createFateDeck();
    deckbuilder.createDynastyDeck();
    deckbuilder.deckShuffler(deckbuilder.getGreen());
    deckbuilder.deckShuffler(deckbuilder.getBlack());
    fateDeck = deckbuilder.getGreen();
    dynastyDeck = deckbuilder.getBlack();

    hand = new list<GreenCard*>();
    holdings = new list<BlackCard*>();
    army = new list<Personality*>();
    provinces = new list<Province*>();
    holdings->push_back(new Stronghold(stronghold));
    for (int i = 0; i < maxHand - 1; i++)
    {
        drawFateCard();
    }
    
    for(int i = 0; i < numberOfProvinces; i++)
    {
        provinces->push_back(new Province(stronghold));
    }
    list<Province*>::iterator it;
    for (it = provinces->begin(); it != provinces->end(); it++)
    {
        (*it)->nextBlackCard(dynastyDeck);
    }
    
}

Player::~Player()
{
    if (!provinces->empty())
    {
        list<Province*>::iterator it;
        for(it = provinces->begin(); it != provinces->end(); it++)
        {
            delete (*it);
        }
    }
    delete provinces;

    if (!hand->empty())
    {
        list<GreenCard*>::iterator ithand;
        for (ithand = hand->begin(); ithand != hand->end(); ithand++)
        {
            delete (*ithand);
        }
    }
    delete hand;

    if (!holdings->empty())
    {
        list<BlackCard*>::iterator ithold;
        for (ithold = holdings->begin(); ithold != holdings->end(); ithold++)
        {
            delete (*ithold);
        }
    }
    delete holdings;

    if (!army->empty())
    {
        list<Personality*>::iterator itp;
        for (itp = army->begin(); itp != army->end(); itp++)
        {
            delete (*itp);
        }
    }
    delete army;
}

string Player::getName(void) const
{
    return name;
}

int Player::getMoney(void) const
{
    return money;
}

int Player::getHonour(void) const
{
    return honour;
}

int Player::getMaxHand(void) const
{
    return maxHand;
}

list<BlackCard*>* Player::getHoldings(void) const
{
    return holdings;
}

list<Province*>* Player::getProvinces(void) const
{
    return provinces;
}

Province Player::getFirstProvince(void) const
{
    return **(provinces->begin());
}

list<Personality*>* Player::getArmy(void) const
{
    return army;
}

list<GreenCard*>* Player::getHand(void) const
{
    return hand;
}

list<BlackCard*>* Player::getDynastyDeck(void) const
{
    return dynastyDeck;
}

void Player::addMoney(int x)
{
    money += x;
}

void Player::reduceMoney(int x)
{
    money -= x;
}

void Player::noMoney(void)
{
    money = 0;
}

void Player::untapEverything(void)
{
    if (!hand->empty())
    {
        list<GreenCard*>::iterator it;
        for(it = hand->begin(); it != hand->end(); it++)
        {
            (*it)->Untap();
        }
    }
    if (!holdings->empty())
    {
        list<BlackCard*>::iterator it;
        for(it = holdings->begin(); it != holdings->end(); it++)
        {
            (*it)->Untap();
        }
    }
    if (!army->empty())
    {
        list<Personality*>::iterator it;
        for(it = army->begin(); it != army->end(); it++)
        {
            (*it)->Untap();
        }
    }
    stronghold.Untap();
}

void Player::drawFateCard(void)
{
    list<GreenCard*>::iterator it;
    if (!fateDeck->empty())
    {
        it = fateDeck->begin();
        hand->splice(hand->end(), *fateDeck, it);
    }
}

void Player::removeFirstProvince(void)
{
    if (!provinces->empty())
    {
        list<Province*>::iterator it;
        it = provinces->begin();
        provinces->erase(it);
    }
}

void Player::removeDeadArmy(void)
{
    if (!army->empty())
    {
        list<Personality*>::iterator it;
        it = army->begin();
        if (army->size() == 1)
        {
            if ((*it)->get_isDead())
            {
                army->erase(it);
            }
        }
        else
        {
            list<Personality*>::iterator it2;
            it2 = next(it);
            while (it2 != army->end())
            {
                if ((*it)->get_isDead())
                {
                    army->erase(it);
                    it = it2;
                    it2++;
                }
                else
                {
                    it++;
                    it2++;
                }
            }
        }
    }
}

void Player::revealProvinces(void)
{
    if (!provinces->empty())
    {
        list<Province*>::iterator it;
        for (it = provinces->begin(); it != provinces->end(); it++)
        {
                (*it)->revealProvince();
        }
    }
}

void Player::printHand(void) const
{
    cout << '\n' << endl;
    if (hand->empty())
    {
        cout << "There are no Fate Cards in " << this->getName() << "'s hand.\n" << endl;
    }
    else
    {
        list<GreenCard*>::iterator it;
        int i = 1;
        cout << this->getName() << "'s hand:" << endl;
        for (it = hand->begin(); it != hand->end(); it++)
        {
            cout << '\n' << i << '.' << endl;
            (*it)->printCard();
            i++;
        }
    }
}

void Player::printProvinces(void) const
{
    if (!provinces->empty())
    {
        list<Province*>::iterator it;
        int i = 1;
        for (it = provinces->begin(); it != provinces->end(); it++, i++)
        {
            cout << '\n' << "Province number " << i << " has defense: " << (*it)->getDefense() << endl;
            cout << "Its available Dynasty Card is:" << endl;
            cout << "   --";
            (*it)->printAvailable();
        }
    }
}

void Player::printHoldings(void) const
{
    list<BlackCard*>::iterator it;
    int i = 1;
    cout << this->getName() << "'s holdings:" << endl;
    for (it = holdings->begin(); it != holdings->end(); it++)
    {
        cout << '\n' << i << '.' << endl;
        (*it)->printCard();
        i++;
    }
}

void Player::printArmy(void) const
{
    if (army->empty())
    {
        cout << "There are no Personalities in " << this->getName() << "'s army.\n" << endl;
    }
    else
    {
        list<Personality*>::iterator it;
        int i = 1;
        cout << this->getName() << "'s army:" << endl;
        for (it = army->begin(); it != army->end(); it++)
        {
            cout << '\n' << i << '.' << endl;
            (*it)->printCard();
            i++;
        }
    }
}

void Player::printAvailableArmy(void) const
{
    if (army->empty())
    {
        cout << "\nThere are no Personalities in " << this->getName() << "'s army.\n" << endl;
    }
    else
    {
        list<Personality*>::iterator it;
        int i = 0;
        cout << this->getName() << "'s army:" << endl;
        for (it = army->begin(); it != army->end(); it++)
        {
            if (!(*it)->get_isTapped())
            {
                i++;
                cout << '\n' << i << '.' << endl;
                (*it)->printCard();
            }
        }
        if (i == 0)
        {
            cout << "\nThere are no available Personalities.\n" << endl;
        }
    }
}

bool Player::armyIsAvailable(void) const
{
    list<Personality*>::iterator it;
    for (it = army->begin(); it != army->end(); it++)
    {
        if (!(*it)->get_isTapped())
        {
            return 1;
        }
    }
    return 0;
}

void Player::discardSurplusFateCards(void)
{
    int num;
    list<GreenCard*>::iterator it;
    while (hand->size() >= maxHand)
    {
        printHand();
        cout << "\nThere are too many cards in " << name << "'s hand, only " << maxHand << " are allowed. Enter the number of a card you would like to discard: ";
        std::cin >> num;
        if (num < 0 || num > hand->size())
        {
            cout << "\nWrong input!" << endl;
            continue;
        }
        else
        {
            it = hand->begin();
            std::advance(it, num-1);
            hand->erase(it);
        }
    }
}