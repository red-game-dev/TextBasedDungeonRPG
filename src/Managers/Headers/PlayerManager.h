#include "../../GameObjects/Headers/Character.h"
#include "../../World/Headers/Room.h"

#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

class PlayerManager : public Character
{
private:
    /* data */
public:
    Room *currentRoom;
    Room *previousRoom;

    vector<Item> inventory;

    PlayerManager(string="", int=0, int=0, int=0, int=0);

    void AddItem(Item);
    void IncreaseStats(int=0, int=0, int=0);
    void lootRoom(Room *);
    void TeleportRoom(Room *);
    void IncreaseLevel(int);
};

#endif