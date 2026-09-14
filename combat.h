#pragma once

#include <string>

using namespace std;

void combat(string enemyName, bool isBoss);
void playerTurn();
void enemyTurn(string enemyName);
void attackWithWeapon(int weaponSlot);
int rollWeaponDamage(string weapon);
void useItem();
void useAbility();
void resetCombat();
void enemyChoice(bool isBoss);