#pragma once

#include <string>

using namespace std;

extern int health;
extern int maxHealth;
extern int levelOfPlayer;
extern int XP;
extern int lvlXP;
extern int mapLevel;
extern int gold;
extern bool canDig;

extern int enemyHealth;
extern int enemyMaxHealth;
extern int enemyDamage;

extern bool abilityUsed[2];
extern bool attackScrollActive;
extern bool speedScrollActive;
extern bool chanceScrollActive;
extern int attacksRemaining;
extern int attackScrollBonus;
extern bool secondWeaponUsed;

extern string inventory[3];
extern string weaponSlots[2];
extern string accessories[3];
extern string allItems[5][6];
extern int itemsPerRarity[5];