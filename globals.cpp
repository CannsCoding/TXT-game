#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "globals.h"

int health;
int maxHealth;
int levelOfPlayer;
int XP;
int maxXP;
int givenXP;
int mapLevel;
int gold;
bool canDig = true;

// =========================
// COMBAT VARIABLES
// =========================

int enemyHealth;
int enemyMaxHealth;
int enemyDamage;

bool abilityUsed[2] = { false, false };

// Turn-based effects
bool attackScrollActive = false;
bool speedScrollActive = false;
bool chanceScrollActive = false;

// How many weapon attacks the player has available this turn
int attacksRemaining = 1;

// Damage bonus from Scroll of Attack
int attackScrollBonus = 0;

// Whether the player has already used their second weapon this turn
bool secondWeaponUsed = false;

string inventory[3]{
	"nothing atm",
	"nothing atm",
	"nothing atm"
};

string weaponSlots[2]{
	"nothing atm",
	"nothing atm"
};

string accessories[3]{
	"nothing atm",
	"nothing atm",
	"nothing atm"
};
string allItems[5][6] = {
	// Garbage Common - 3 items
	{
		"basic ring",
		"scrap",
		"chain"
	},

	// Weapon Uncommon - 6 items
	{
		"Dagger 4d4-3",
		"Saber 3d4",
		"Axe 2d4",
		"Sythe 1d8",
		"Long Sword 2d8-3",
		"Lance 1d12-3+critchance"
	},

	// Armor Rare - 3 items
	{
		"Studded lether +5 to Hp",
		"Chainmail +10 to Hp",
		"Plate armor +20 to hp"
	},

	// Scrolls Epic - 6 items
	{
		"Scroll of Fireball (1d20)",
		"Scroll of Healing (heal 2d10)",
		"Scroll of Attack (+1d6 to damage)",
		"Scroll of Speed (+1 attack)",
		"Scroll of Divinity (+10 MAX Hp)",
		"Scroll of Chance (x2 attack but can miss)"
	},

	// Power Rings Legendary - 3 items
	{
		"Ring of Vitality (+10 MAX Hp)",
		"Ring of Strength (+3 to attack)",
		"ring of lightning (free 1d6 attack)"
	}
};
int itemsPerRarity[5] = {
	3,  // Common
	6,  // Uncommon
	3,  // Rare
	6,  // Epic
	3   // Legendary
};