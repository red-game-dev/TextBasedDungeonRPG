#include "../Headers/Room.h"

Room::Room(int p, bool ie, vector<Item> it, vector<EnemyManager> gcs){
    pos = p;
    isExit = ie;
    items = it;
    enemies = gcs;
};

void Room::clearLoot() {
    items.clear();
}

void Room::clearEnemies()
{
    enemies.clear();
}