#include "../Headers/Character.h"


Character::Character(string n, int h, int a, int d, int l) {
    name = n;
    maxHp = h;
    currHp = h;
    attack = a;
    defence = d;
    level = l;
}

int Character::TakeDamage(int amount) {
    int damage = amount - defence;

    if (damage < 0) {
        damage = 0;
    } 

    currHp -= damage;

    return damage;
}

bool Character::isDead() {
    return currHp <= 0;
}