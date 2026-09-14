#include "player.h"
#include "globals.h"
#include <iostream>

using namespace std;

// =========================================
// CALCULATE PLAYER HEALTH
// =========================================

int calculateHealth(int playerLVL, int usedScroll, int wearigRing) {
	health = health + playerLVL * 1.5 + rand() % 3 + 1;
	maxHealth = health;
	return 0;
}

// =========================================
// SHOW THE PLAYER THEIR STATS
// =========================================

void playerStats() {
	cout << "--- PLayer Stats ---" << endl;
	cout << "Player LVL: " << levelOfPlayer << endl;
	cout << "HP: " << health << "/" << maxHealth << endl;
	cout << " " << endl;
	cout << "--- PLayer's Weapons ---" << endl;
	cout << "Right hand, Weapon slot 1: " << weaponSlots[0] << endl;
	cout << "Left hand, Weapon slot 2: " << weaponSlots[1] << " (-2)" << endl;
	cout << " " << endl;
	cout << "--- PLayer's Accessories ---" << endl;
	cout << "Right hand, Accessory: " << accessories[0] << endl;
	cout << "Left hand, Accessory: " << accessories[1] << endl;
	cout << "Body, Accessory: " << accessories[2] << endl;
	cout << " " << endl;
	cout << "--- PLayer's inventory ---" << endl;
	cout << "Gold: " << gold << endl;
	cout << "Inventory slot 1: " << inventory[0] << endl;
	cout << "Inventory slot 2: " << inventory[1] << endl;
	cout << "Inventory slot 3: " << inventory[2] << endl;
	cout << " " << endl;
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

	cout << "What is your weapon of choice:" << endl;
	cout << "1: Scythe - 1d8" << endl;
	cout << "2: Axe - 2d4" << endl;
	cout << "3: Long sword - 2d8 -3" << endl;
	cout << "4: Dagger - 4d4 -3" << endl;
	cout << "5: Lance - 1d12 -3" << endl;
	cout << "6: Saber - 3d4" << endl;

	cin >> weaponOfChoice;

	if (weaponOfChoice == 1) {
		cout << " " << endl;
		cout << "added scythe to weapon slot one" << endl;
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
}