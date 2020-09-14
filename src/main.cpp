#include <iostream>
#include "World/Source/Dungeon.cpp"
#include "GameObjects/Source/Character.cpp"
#include "GameObjects/Source/Item.cpp"
#include "Managers/Source/PlayerManager.cpp"
#include "Managers/Source/EnemyManager.cpp"
#include "World/Source/Room.cpp"

int main(int argc, char const *argv[])
{
    cout << "Welcome to Atlantis! Please write your nickname: \n";

    // Set our player
    string playerName;
    cin >> playerName;

    PlayerManager player = PlayerManager(playerName, 100, 20, 10, 1);

    // Set our rooms

    // 2.

    // Items loot
    Item sword = Item("Sword", 0, 10, 0);
    Item vestment = Item("Vestment", 5, 0, 10);
    vector<Item> secondRoomLoot = {
        sword, vestment
    };

    // 3.

    // Enemies
    EnemyManager liltch = EnemyManager("Mini Liltch", 50, 20, 10);
    EnemyManager crazyFairy1 = EnemyManager("Mini Crazy Fairy", 15, 12, 3);
    EnemyManager crazyFairy2 = EnemyManager("Mini Crazy Fairy", 15, 12, 3);

    // 4.
    EnemyManager akuma = EnemyManager("Mini Akuma", 100, 20, 10);
    EnemyManager boardaxe1 = EnemyManager("Mini Boardaxe Sword", 25, 10, 5);
    EnemyManager boardaxe2 = EnemyManager("Mini Boardaxe Sword", 25, 10, 5);


    Dungeon atlantisDungeon = Dungeon(player);
    atlantisDungeon.rooms[0] = Room(0, false, vector<Item>(), vector<EnemyManager>());
    atlantisDungeon.rooms[1] = Room(1, false, secondRoomLoot, vector<EnemyManager>());
    atlantisDungeon.rooms[2] = Room(2, false, vector<Item>(), {
        liltch, crazyFairy1, crazyFairy2
    });
    atlantisDungeon.rooms[3] = Room(3, true, vector<Item>(), {
        akuma, boardaxe2, boardaxe1
    });

    // Think of this as update() in Unity
    while (true)
    {
        int result = atlantisDungeon.StartDungeon();

        if (result == 0) {
            break;
        }
    }
    
    cout << "Exiting from Dungeon";

    /* code */
    return 0;
}
