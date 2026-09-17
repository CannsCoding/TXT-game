#include "player.h"
#include "globals.h"
#include <iostream>

using namespace std;

// =========================================
// CALCULATE PLAYER HEALTH
// =========================================

int calculateHealth(int playerLVL, int usedScroll, int wearigRing) {
	health = health + playerLVL * 1.5 + rand() % 3 + 1 + wearigRing + usedScroll;
	maxHealth = health;
	return 0;
}

// =========================================
// CALCULATE XP GIVEN
// =========================================

int xpGiven(int xpAmount) {
	givenXP = xpAmount;
	XP += givenXP;
	cout << greenText;
	cout << "You gained " << brightYellowText << XP << greenText << "XP!" << endl;
	cout << resetColor;
	didLVLUp();

	return givenXP;
}

// =========================================
// CALCULATE LVL UP
// =========================================

int didLVLUp() {
	bool leveledUp = false;

	while (XP >= maxXP && maxXP > 0) {
		XP -= maxXP;
		levelOfPlayer++;

		// Increase the player's maximum health each level.
		maxHealth += levelOfPlayer * 1.5 + rand() % 3 + 1;
		health = maxHealth;

		calculateMaxXP();

		leveledUp = true;
	}

	if (leveledUp) {
		cout << blueText;
		cout << '\n';
		cout << "========================================" << endl;
		cout << resetColor;

		cout << purpleText;
		cout << "             YOU LEVELED UP!" << endl;
		cout << resetColor;

		cout << blueText;
		cout << "========================================" << endl;
		cout << '\n';
		cout << resetColor;

		cout << greenText;
		cout << "You are now level " << levelOfPlayer << "!" << endl;
		cout << "Your maximum health is now " << maxHealth << "." << endl;
		cout << "Your next level requires " << maxXP << " XP." << endl;
		cout << resetColor;
	}

	return leveledUp ? 1 : 0;
}

// =========================================
// CALCULATE PLAYER MAX XP
// =========================================

void calculateMaxXP() {
    // XP requirements increase as the player's level increases.
    maxXP = 10 + levelOfPlayer * 5;
}

// =========================================
// CALCULATE PLAYER STARTING LVL
// =========================================

void calculateFirstLvl() {
	levelOfPlayer = rand() % 10 + 5;

	XP = 0;
	maxXP = 0;
	health = 0;
	maxHealth = 0;

	calculateMaxXP();
	calculateHealth(levelOfPlayer, 0, 0);
}

// =========================================
// SHOW THE PLAYER THEIR STATS
// =========================================

void playerStats() {
	cout << blueText;
	cout << '\n';
	cout << "========================================" << endl;
	cout << resetColor;

	cout << purpleText;
	cout << "\t\tPLAYER" << endl;
	cout << resetColor;

	cout << blueText;
	cout << "========================================" << endl;
	cout << '\n';
	cout << resetColor;

	// Player stats
	cout << orangeText << "--- Player Stats ---" << resetColor << endl;
	cout << '\n';

	cout << limeGreenText << "Player LVL: " << resetColor
		<< yellowText << levelOfPlayer << resetColor << endl;

	cout << limeGreenText << "HP: " << resetColor
		<< yellowText << health << "/" << maxHealth
		<< resetColor << endl;

	cout << limeGreenText << "XP: " << resetColor
		<< yellowText << XP << "/" << maxXP
		<< resetColor << endl;

	cout << '\n';

	// Weapons
	cout << orangeText << "--- Player's Weapons ---" << resetColor << endl;
	cout << '\n';

	cout << limeGreenText << "Right hand, Weapon slot 1: "
		<< resetColor << yellowText << weaponSlots[0]
		<< resetColor << endl;

	cout << limeGreenText << "Left hand, Weapon slot 2: "
		<< resetColor << yellowText << weaponSlots[1]
		<< " (-2)" << resetColor << endl;

	cout << '\n';

	// Accessories
	cout << orangeText << "--- Player's Accessories ---" << resetColor << endl;
	cout << '\n';

	cout << limeGreenText << "Right hand, Accessory: "
		<< resetColor << yellowText << accessories[0]
		<< resetColor << endl;

	cout << limeGreenText << "Left hand, Accessory: "
		<< resetColor << yellowText << accessories[1]
		<< resetColor << endl;

	cout << limeGreenText << "Body, Accessory: "
		<< resetColor << yellowText << accessories[2]
		<< resetColor << endl;

	cout << '\n';

	// Inventory
	cout << orangeText << "--- Player's Inventory ---" << resetColor << endl;
	cout << '\n';

	cout << limeGreenText << "Gold: "
		<< resetColor << yellowText << gold
		<< resetColor << endl;

	cout << limeGreenText << "Inventory slot 1: "
		<< resetColor << yellowText << inventory[0]
		<< resetColor << endl;

	cout << limeGreenText << "Inventory slot 2: "
		<< resetColor << yellowText << inventory[1]
		<< resetColor << endl;

	cout << limeGreenText << "Inventory slot 3: "
		<< resetColor << yellowText << inventory[2]
		<< resetColor << endl;

	cout << '\n';
}

// =========================================
// CALCULATE DAMAGE
// =========================================

void calculateDamage(int pLVL, int Weapon) {
	cout << "you are lvl: " << pLVL << " meaning you did " << pLVL * 1.5 + Weapon;
}

// =========================================
// PLAYER CHOOSE WEAPON
// =========================================

void chooseWeapon() {

	int weaponOfChoice;

	cout << greenText;
	cout << "What is your weapon of choice:";
	cout << resetColor << endl;

	cout << limeGreenText;
	cout << "1: ";
	cout << resetColor;

	cout << blueText;
	cout << "Scythe";
	cout << resetColor;

	cout << greenText;
	cout << " - ";
	cout << resetColor;

	cout << redText;
	cout << "1d8";
	cout << resetColor << endl;


	cout << limeGreenText;
	cout << "2: ";
	cout << resetColor;

	cout << blueText;
	cout << "Axe";
	cout << resetColor;

	cout << greenText;
	cout << " - ";
	cout << resetColor;

	cout << redText;
	cout << "2d4";
	cout << resetColor << endl;


	cout << limeGreenText;
	cout << "3: ";
	cout << resetColor;

	cout << blueText;
	cout << "Long sword";
	cout << resetColor;

	cout << greenText;
	cout << " - ";
	cout << resetColor;

	cout << redText;
	cout << "2d8 -3";
	cout << resetColor << endl;


	cout << limeGreenText;
	cout << "4: ";
	cout << resetColor;

	cout << blueText;
	cout << "Dagger";
	cout << resetColor;

	cout << greenText;
	cout << " - ";
	cout << resetColor;

	cout << redText;
	cout << "4d4 -3";
	cout << resetColor << endl;


	cout << limeGreenText;
	cout << "5: ";
	cout << resetColor;

	cout << blueText;
	cout << "Lance";
	cout << resetColor;

	cout << greenText;
	cout << " - ";
	cout << resetColor;

	cout << redText;
	cout << "1d12 -3";
	cout << resetColor << endl;


	cout << limeGreenText;
	cout << "6: ";
	cout << resetColor;

	cout << blueText;
	cout << "Saber";
	cout << resetColor;

	cout << greenText;
	cout << " - ";
	cout << resetColor;

	cout << redText;
	cout << "3d4";
	cout << resetColor << endl;

	cin >> weaponOfChoice;
	cout << brightYellowText;
	if (weaponOfChoice == 1) {
		cout << " " << endl;
	
		cout << "added scythe to weapon slot one" << endl;
		cout << resetColor;
		cout << " " << endl;
		weaponSlots[0] = allItems[1][3];
	}
	else if (weaponOfChoice == 2) {
		cout << " " << endl;
		cout << "added axe to weapon slot one" << endl;
		cout << " " << endl;
		weaponSlots[0] = allItems[1][2];
	}
	else if (weaponOfChoice == 3) {
		cout << " " << endl;
		cout << "added long sword to weapon slot one" << endl;
		cout << " " << endl;
		weaponSlots[0] = allItems[1][4];
	}
	else if (weaponOfChoice == 4) {
		cout << " " << endl;
		cout << "added dagger to weapon slot one" << endl;
		cout << " " << endl;
		weaponSlots[0] = allItems[1][0];
	}
	else if (weaponOfChoice == 5) {
		cout << " " << endl;
		cout << "added lance to weapon slot one" << endl;
		cout << " " << endl;
		weaponSlots[0] = allItems[1][5];
	}
	else if (weaponOfChoice == 6) {
		cout << " " << endl;
		cout << "added saber to weapon slot one" << endl;
		cout << " " << endl;
		weaponSlots[0] = allItems[1][1];
	}
	else {
		cout << " " << endl;
		cout << "Invalid weapon choice." << endl;
		cout << " " << endl;
		chooseWeapon();
	}
	cout << resetColor;
}