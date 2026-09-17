#pragma once

#include <string>

using namespace std;

extern int health;
extern int maxHealth;
extern int levelOfPlayer;
extern int XP;
extern int maxXP;
extern int givenXP;
extern int mapLevel;
extern int gold;
extern bool canDig;
extern const string orangeText;
extern const string yellowText;
extern const string limeGreenText;
extern const string resetColor;

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