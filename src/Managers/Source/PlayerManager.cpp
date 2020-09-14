#include "../Headers/PlayerManager.h"

PlayerManager::PlayerManager(string name, int health, int attack, int defence, int level)
    :Character(name, health, attack, defence, level) {
    // SIMULATION LIKE DB
    Item dagger = Item("Dagger", 0, 5, 0);
    AddItem(dagger);
}

void PlayerManager::AddItem(Item item) {
    inventory.push_back(item);
    // Increase stats since in our case all items are equip
    IncreaseStats(item.health, item.attack, item.defence);
}

void PlayerManager::IncreaseLevel(int newLevel) {
    level += newLevel;
}

void PlayerManager::IncreaseStats(int h, int a, int d) {
    currHp += h;
    maxHp += h;
    attack += a;
    defence += d;
}

void PlayerManager::lootRoom(Room *room) {
    vector<Item> roomItems = room->items;

    // Go through each item to add
    for (size_t i = 0; i < roomItems.size(); i++)
    {
        // Add items
        AddItem(roomItems[i]);
    }
}

void PlayerManager::TeleportRoom(Room *newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
}