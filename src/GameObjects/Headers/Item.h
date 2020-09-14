#include <string>
#include <iostream>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item
{
private:
    /* Your private data */
public: // Don't ever use public for everything, this for example to quick overview
    string name;
    int health, attack, defence;

    Item(string="", int=0, int=0, int=0);
};

#endif
