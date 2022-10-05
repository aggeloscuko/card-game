#ifndef _PROVINCE_HPP_
#define _PROVINCE_HPP_

#include <list>
#include "Card.hpp"

using std::list;

class Province
{
    BlackCard* available;
    int defense;
    bool isRevealed;
public:
    Province(const Stronghold&);
    ~Province();

    void revealProvince(void);
    void printAvailable(void) const;
    int getDefense(void) const;
    bool getIsRevealed(void) const;
    BlackCard* getAvailable(void) const;
    void nextBlackCard(list<BlackCard*>* deck);
};

#endif