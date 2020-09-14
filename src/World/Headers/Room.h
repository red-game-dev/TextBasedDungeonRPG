#include <vector>

#include "../../Managers/Headers/EnemyManager.h"
#include "../../GameObjects/Headers/Item.h"

#ifndef ROOM_H
#define ROOM_H

class Room 
{
public: 
    int pos;
    bool isExit;

    vector<Item> items;
    vector<EnemyManager> enemies;

    Room(int=0, bool=false, vector<Item> = vector<Item>(), vector<EnemyManager> = vector<EnemyManager>());

    void clearLoot();
    void clearEnemies();
};

#endif