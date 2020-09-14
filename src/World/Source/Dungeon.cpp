#include "../Headers/Dungeon.h"	
#include <algorithm>   // transform()
#include <cctype>      // toupper(), tolower()
#include <functional>  // ptr_fun()

Dungeon::Dungeon(PlayerManager p) {
    player = p;
}

void Dungeon::TeleportToRoom(Room *room) {
    // Room that has enemies
    if (room->enemies.size() > 0) {
        EnemyRoom(room);
    }
    // else room with rewards 
    else if (room->items.size() > 0) {
        ChestRoom(room);
    } // else must be an empty room
    else {
        EmptyRoot(room);
    }
}



void Dungeon::MovementActions(Room *room) {
    while (true)
    {
        if (room->pos == 0) {
            string strInput;
            string actions[] = {
                "a. Move right",
                "b. Move down"
            };

            PrintActions(2, actions);

            cin >> strInput;

            // Transform the result to lower case
            // You cannot store it in str, it's not like JS
            // Has to be an output iterator equal to @p result+(last-first).
            transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

            if (strInput == "a") {
                player.TeleportRoom(&rooms[1]);

                return;
            } else if(strInput == "b") {
                player.TeleportRoom(&rooms[2]);

                return;
            } else {
                cout << "Nope, you cannot select other then a key!\n";
            }
        } else if (room->pos == 1) {
            string strInput;
            string actions[] = {
                "a. Move left"
            };

            PrintActions(1, actions);

            cin >> strInput;

            // Transform the result to lower case
            // You cannot store it in str, it's not like JS
            // Has to be an output iterator equal to @p result+(last-first).
            transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

            if (strInput == "a") {
                player.TeleportRoom(&rooms[0]);

                return;
            } else {
                cout << "Nope, you cannot select other then a key!\n";
            }
        } else if (room->pos == 2) {
            string strInput;
            string actions[] = {
                "a. Move up",
                "b. Move right"
            };

            PrintActions(2, actions);

            cin >> strInput;

            // Transform the result to lower case
            // You cannot store it in str, it's not like JS
            // Has to be an output iterator equal to @p result+(last-first).
            transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

            if (strInput == "a") {
                player.TeleportRoom(&rooms[0]);

                return;
            } else if(strInput == "b") {
                player.TeleportRoom(&rooms[3]);

                return;
            } else {
                cout << "Nope, you cannot select other then a key!\n";
            }
        } else {
            string strInput;
            string actions[] = {
                "a. Move left"
            };

            PrintActions(1, actions);

            cin >> strInput;

            // Transform the result to lower case
            // You cannot store it in str, it's not like JS
            // Has to be an output iterator equal to @p result+(last-first).
            transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

            if (strInput == "a") {
                player.TeleportRoom(&rooms[2]);

                return;
            } else {
                cout << "Nope, you cannot select other then a key!\n";
            }
        }
    }
}

void Dungeon::PrintActions(int numActions, string actions[]) {
    cout << "\nChoose an action: \n";

    for (size_t i = 0; i < numActions; i++)
    {
        cout << actions[i] << "\n";
    }
}

void Dungeon::LootActions(Room *room) {
    cout << "You open the chests and got\n";
    int previousHp = player.maxHp;
    int previousAttck = player.attack;
    int previousDefence = player.defence;
    vector<Item> loot = room->items;

    player.lootRoom(room);
    room->clearLoot();

    for (size_t i = 0; i < loot.size(); i++)
    {
        cout << "1x " << loot[i].name << "\n\n";
        cout << "Your stats has been increased by:\n";
        cout << "Health: " << (player.maxHp - previousHp) << "\n";
        cout << "Attack: " << (player.attack - previousAttck) << "\n";
        cout << "Defence: " << (player.defence - previousDefence) << "\n\n";
    }
       
    cout << "Congratz!\n";
}

void Dungeon::FightActions(EnemyManager *enemy) {
    string actions[] = {
        "a. Attack",
        "b. Retreat"
    };

    while (true)
    {
        PrintActions(2, actions);

        string strInput;
        cin >> strInput;

        // Transform the result to lower case
        // You cannot store it in str, it's not like JS
        // Has to be an output iterator equal to @p result+(last-first).
        transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );
        // Player actions 
        if (strInput == "a") {
            // Attack
            int damage = enemy->TakeDamage(player.attack);
            cout << enemy->name << " been damaged a total of " << damage << "\n";
    
        } else if(strInput == "b") {
            // Swap teleported rooms
            player.TeleportRoom(player.previousRoom);
            // Move to previous room
            TeleportToRoom(player.currentRoom);
            return;
        } else {
            cout << "Nope, you cannot select other then a key!\n";
        }

        // Enemy actions
        if (enemy->isDead()) {
            int previousLevel = player.level;
            int previousHp = player.maxHp;
            int previousAttck = player.attack;
            int previousDefence = player.defence;

            cout << enemy->name << " Say: How did you manage! I'll return and defeat you!\n\n";
            cout << "You made it, you defeated " << enemy->name << "\n";
            // Set player stats
            player.IncreaseLevel(1);
            player.IncreaseStats(10, 5, 5);
       
            cout << "Congratz your level has been increased and your stats too!\n";

            cout << "Level from " << previousLevel << " to " << (player.level) << "\n";
            cout << "Health: " << (player.maxHp - previousHp) << "\n";
            cout << "Attack: " << (player.attack - previousAttck) << "\n";
            cout << "Defence: " << (player.defence - previousDefence) << "\n\n";

            return;
        }
        
        // Damage the player
        int damage = player.TakeDamage(enemy->attack);

        cout << enemy->name << " has attacked you and gave a total of " << damage << " damage\n";
        cout << "You got left " << player.currHp << "/" << player.maxHp << " Health\n";
        cout << enemy->name << " got left " << enemy->currHp << "/" << enemy->maxHp << " Health\n";

        if (player.isDead()) {
            return;
        }
    }
}




void Dungeon::EnemyRoom(Room *room) {

    if (room->enemies.size() == 0) {
        cout << "I did see some enemies around, but they are gone!\n";
    }

    cout << "Seems few enemies is around!\n";
    
    int currentEnemyIndex = 0;

    string actions[] = {
        "a. Go against the enemy ",
        "b. Retreat to previous room"
    };

    while (true)
    {
        PrintActions(2, actions);

        string strInput;
        cin >> strInput;

        // Transform the result to lower case
        // You cannot store it in str, it's not like JS
        // Has to be an output iterator equal to @p result+(last-first).
        transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

        if (strInput == "a") {
            while (room->enemies.size() > 0)
            {
                if (currentEnemyIndex > (room->enemies.size() - 1)) {
                    cout << "Seems you have defeated all the " << room->enemies.size() << " enemies in this room";
                    
                    room->clearEnemies();

                    return;
                }

                EnemyManager enemy = room->enemies[currentEnemyIndex];

                string actions[] = {
                    "a. Fight " + enemy.name + " (" + to_string(currentEnemyIndex + 1) + ")",
                    "b. Retreat to previous room"
                };

                PrintActions(2, actions);

                string strPveInput;
                cin >> strPveInput;

                // Transform the result to lower case
                // You cannot store it in str, it's not like JS
                // Has to be an output iterator equal to @p result+(last-first).
                transform(strPveInput.begin(), strPveInput.end(), strPveInput.begin(), ptr_fun <int, int> ( tolower ) );

                cout << "You have encountered " << enemy.name << "\n";
                if (strInput == "a") {
                    // Fight action between the enemy 1vs1
                    FightActions(&enemy);
                } else if(strInput == "b") {
                    // Swap teleported rooms
                    player.TeleportRoom(player.previousRoom);
                    // Move to previous room
                    TeleportToRoom(player.currentRoom);

                    return;
                }

                currentEnemyIndex += 1;
            }
    
            return;
        } else if(strInput == "b") {
            // Swap teleported rooms
            player.TeleportRoom(player.previousRoom);
            // Move to previous room
            TeleportToRoom(player.currentRoom);
        } else {
            cout << "Nope, you cannot select other then a key!\n";
        }
    }
}

void Dungeon::ChestRoom(Room *room) {
    cout << "It is shining this room! So much treasures!";

    string actions[] = {
        "a. Get the chest",
        "b. Move to next room"
    };

    while (true)
    {
        PrintActions(2, actions);

        string strInput;
        cin >> strInput;

        // Transform the result to lower case
        // You cannot store it in str, it's not like JS
        // Has to be an output iterator equal to @p result+(last-first).
        transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

        if (strInput == "a") {
            // Get the chest
            LootActions(room);
    
            return;
        } else if(strInput == "b") {
            // Move to room <Next action in this case from while loop in StartDungeon()> 
            return;
        } else {
            cout << "Nope, you cannot select other then a key!\n";
        }
    }
}

void Dungeon::EmptyRoot(Room *room) {
    cout << "The room you've went seems to be empty!";

    string actions[] = {"a. Move to another room!"};

    while (true)
    {
        PrintActions(1, actions);

        string strInput;
        cin >> strInput;

        // Transform the result to lower case
        // You cannot store it in str, it's not like JS
        // Has to be an output iterator equal to @p result+(last-first).
        transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

        if (strInput == "a") {
            // Move to room <Next action in this case from while loop in StartDungeon()> 
            return;
        } else {
            cout << "Nope, you cannot select other then a key!\n";
        }
    }
}



int Dungeon::EndDungeon() {
    string strInput;
    string actions[] = {
        "a. Yes",
        "b. No",
    };

    while (true)
    {
        PrintActions(2, actions);

        cin >> strInput;

        // Transform the result to lower case
        // You cannot store it in str, it's not like JS
        // Has to be an output iterator equal to @p result+(last-first).
        transform(strInput.begin(), strInput.end(), strInput.begin(), ptr_fun <int, int> ( tolower ) );

        if (strInput == "a") {
            return 1;
        } else if(strInput == "b") {
            return 0;
        } else {
            cout << "Nope, you cannot select other then a key!\n";
        }
    }
    
}

int Dungeon::StartDungeon() {
    cout << "Welcome Atlantis Dungeon! Inside you will find strong enemies but a mine of treasures!";

    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];

    // Be sure that u handle some break conditions in this term, else it will run forever. 
    // Think of this as Update() in unity
    while (true)
    {
        // Go to the respective room
        TeleportToRoom(player.currentRoom);

        if (player.isDead()) {
            // lose the game
            cout << player.name << " dam it, you died! Restart the dungeon?";

            return EndDungeon();

        } else {
            if (player.currentRoom->isExit) {
                if (player.currentRoom->enemies.size() == 0) {
                    cout << player.name << ", you made it! You went through Atlantis dungeon, defeated the enemies and got the treasure! Restart agian the dungeon?";
                    
                    return EndDungeon();
                }
            }
        }
        // Movement actions 
        MovementActions(player.currentRoom);
    }
}