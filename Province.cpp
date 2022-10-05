#include <iostream>
#include "Province.hpp"

Province::Province(const Stronghold& stronghold)
:defense(stronghold.get_initialDefense()), available(nullptr), isRevealed(0)
{}

Province::~Province()
{
    if (available != nullptr)
        delete available;
}

void Province::revealProvince(void)
{
    isRevealed = 1;
}

void Province::printAvailable(void) const
{
    if (available != nullptr)
        available->printCard();
    else
        std::cout << "There is no available card to buy in this province.\n" << std::endl;
}

int Province::getDefense(void) const
{
    return defense;
}

bool Province::getIsRevealed(void) const
{
    return isRevealed;
}

BlackCard* Province::getAvailable(void) const
{
    return available;
}

void Province::nextBlackCard(list<BlackCard*>* deck)
{
    available = deck->front();
    deck->pop_front();
}