#include <string>
#include <iostream>

#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character
{
private: 
    /* Your private data */
public:
    string name;
    int maxHp, currHp, attack, defence, level;

    Character(string="", int=0, int=0, int=0, int=0);

    int TakeDamage(int=0);

    bool isDead();
};

#endif
