#include "../../Managers/Headers/PlayerManager.h"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon {
public:
    PlayerManager player;
    Room rooms[4];

    Dungeon(PlayerManager);

    int StartDungeon();
    void TeleportToRoom(Room *);

    void EmptyRoot(Room *);
    void ChestRoom(Room *);
    void EnemyRoom(Room *);

    void LootActions(Room *);
    void FightActions(EnemyManager *);
    void MovementActions(Room *);
    void PrintActions(int, string[]);

    int EndDungeon();
};

#endif