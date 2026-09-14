#include "items.h"
#include "globals.h"
#include "player.h"
#include "game.h"
#include <iostream>

using namespace std;

// =========================================
// DIGGING ACTION
// =========================================

int digging() {
	cout << "you begin to dig for loot" << endl;
	cout << "." << endl;
	cout << "." << endl;
	cout << "." << endl;
	itemRandomizer();
	return 0;
}

// =========================================
// ITEM RANDOMIZATION
// =========================================

void itemRandomizer() {

	int itemRarity = rand() % 100 + 1;
	int rarityIndex;
	int itemChance;
	string itemGiven;

	// =========================
	// CHOOSE RARITY
	// =========================

	if (itemRarity <= 40) {
		// Common - 40%
		rarityIndex = 0;
	}
	else if (itemRarity <= 67) {
		// Uncommon - 27%
		rarityIndex = 1;
	}
	else if (itemRarity <= 87) {
		// Rare - 20%
		rarityIndex = 2;
	}
	else if (itemRarity <= 97) {
		// Epic - 10%
		rarityIndex = 3;
	}
	else {
		// Legendary - 3%
		rarityIndex = 4;
	}

	// =========================
	// CHOOSE ITEM
	// =========================

	itemChance = rand() % itemsPerRarity[rarityIndex];

	itemGiven = allItems[rarityIndex][itemChance];

	storeItem(itemGiven, rarityIndex);
}

// =========================================
// STORING ITEM
// =========================================

void storeItem(string itemGiven, int itemType) {

	char wouldStore;

	cout << "You received: " << itemGiven << endl;
	cout << "Would you like to store this item? (y/n)" << endl;
	cin >> wouldStore;

	if (wouldStore == 'n' || wouldStore == 'N') {
		cout << "You decided not to keep the item." << endl;
		playerStats();
		lvlGenerator(false);
		return;
	}

	if (wouldStore != 'y' && wouldStore != 'Y') {
		cout << "Invalid choice." << endl;
		storeItem(itemGiven, itemType);
		return;
	}

	int whereStore;

	// =========================================
	// GARBAGE - INVENTORY ONLY
	// =========================================

	if (itemType == 0) {

		cout << "Garbage can only be stored in your inventory." << endl;

		int slot;

		cout << "Which inventory slot?" << endl;
		cout << "1: Inventory slot 1" << endl;
		cout << "2: Inventory slot 2" << endl;
		cout << "3: Inventory slot 3" << endl;
		cin >> slot;

		if (slot >= 1 && slot <= 3) {

			if (inventory[slot - 1] == "nothing atm") {
				inventory[slot - 1] = itemGiven;
				cout << itemGiven << " was stored in inventory slot "
					<< slot << "." << endl;
			}
			else {
				cout << "That inventory slot is full." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else {
			cout << "Invalid slot." << endl;
			storeItem(itemGiven, itemType);
		}
	}

	// =========================================
	// WEAPON - WEAPON SLOTS OR INVENTORY
	// =========================================

	else if (itemType == 1) {

		cout << "Where would you like to store your weapon?" << endl;
		cout << "1: Weapon slots" << endl;
		cout << "2: Inventory" << endl;
		cin >> whereStore;

		if (whereStore == 1) {

			int slot;

			cout << "Which weapon slot?" << endl;
			cout << "1: Weapon slot 1" << endl;
			cout << "2: Weapon slot 2" << endl;
			cin >> slot;

			if (slot == 1 || slot == 2) {

				if (weaponSlots[slot - 1] == "nothing atm") {
					weaponSlots[slot - 1] = itemGiven;

					cout << itemGiven << " was stored in weapon slot "
						<< slot << "." << endl;
				}
				else {
					cout << "That weapon slot is full." << endl;
					storeItem(itemGiven, itemType);
				}

			}
			else {
				cout << "Invalid slot." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else if (whereStore == 2) {

			int slot;

			cout << "Which inventory slot?" << endl;
			cout << "1: Inventory slot 1" << endl;
			cout << "2: Inventory slot 2" << endl;
			cout << "3: Inventory slot 3" << endl;
			cin >> slot;

			if (slot >= 1 && slot <= 3) {

				if (inventory[slot - 1] == "nothing atm") {
					inventory[slot - 1] = itemGiven;

					cout << itemGiven << " was stored in inventory slot "
						<< slot << "." << endl;
				}
				else {
					cout << "That inventory slot is full." << endl;
					storeItem(itemGiven, itemType);
				}

			}
			else {
				cout << "Invalid slot." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else {
			cout << "Invalid storage choice." << endl;
			storeItem(itemGiven, itemType);
		}
	}

	// =========================================
	// ARMOR - BODY SLOT OR INVENTORY
	// =========================================

	else if (itemType == 2) {

		cout << "Where would you like to store your armor?" << endl;
		cout << "1: Wear armor" << endl;
		cout << "2: Inventory" << endl;
		cin >> whereStore;

		if (whereStore == 1) {

			// accessories[2] is the body/armor slot.
			if (accessories[2] == "nothing atm") {

				accessories[2] = itemGiven;
				cout << itemGiven << " was equipped as your armor." << endl;
			}
			else {
				int armorInventorySlot = -1;
				int emptyInventorySlot = -1;

				for (int i = 0; i < 3; i++) {
					if (isArmor(inventory[i])) armorInventorySlot = i;
					if (inventory[i] == "nothing atm" && emptyInventorySlot == -1) emptyInventorySlot = i;
				}

				cout << "You are currently wearing: " << accessories[2] << endl;
				cout << "1: Drop current armor and equip the new armor" << endl;
				if (armorInventorySlot == -1 && emptyInventorySlot != -1) {
					cout << "2: Put current armor in inventory and equip the new armor" << endl;
					cout << "3: Keep current armor and store the new armor in inventory" << endl;
				}
				cout << "4: Keep current armor and do not store the new armor" << endl;

				int replaceChoice;
				cin >> replaceChoice;

				if (replaceChoice == 1) {
					cout << "You dropped " << accessories[2] << "." << endl;
					accessories[2] = itemGiven;
					cout << itemGiven << " was equipped as your armor." << endl;
				}
				else if (replaceChoice == 2 && armorInventorySlot == -1 && emptyInventorySlot != -1) {
					inventory[emptyInventorySlot] = accessories[2];
					accessories[2] = itemGiven;
					cout << "Your previous armor was moved to inventory slot "
						<< emptyInventorySlot + 1 << "." << endl;
					cout << itemGiven << " was equipped as your armor." << endl;
				}
				else if (replaceChoice == 3 && armorInventorySlot == -1 && emptyInventorySlot != -1) {
					int slot;

					cout << "Which inventory slot would you like to use?" << endl;
					cout << "1: " << inventory[0] << endl;
					cout << "2: " << inventory[1] << endl;
					cout << "3: " << inventory[2] << endl;
					cin >> slot;

					if (slot >= 1 && slot <= 3 && inventory[slot - 1] == "nothing atm") {
						inventory[slot - 1] = itemGiven;
						cout << itemGiven << " was stored in inventory slot " << slot << "." << endl;
					}
					else {
						cout << "That inventory slot is unavailable." << endl;
						storeItem(itemGiven, itemType);
						return;
					}
				}
				else if (replaceChoice == 4) {
					cout << "You kept your current armor." << endl;
					cout << "You did not store the new armor." << endl;
				}
				else {
					cout << "That option is unavailable." << endl;
					storeItem(itemGiven, itemType);
					return;
				}
			}

		}
		else if (whereStore == 2) {

			int slot;

			cout << "Which inventory slot?" << endl;
			cout << "1: Inventory slot 1" << endl;
			cout << "2: Inventory slot 2" << endl;
			cout << "3: Inventory slot 3" << endl;
			cin >> slot;

			bool alreadyCarryingArmor = false;
			for (int i = 0; i < 3; i++) {
				if (isArmor(inventory[i])) alreadyCarryingArmor = true;
			}

			if (alreadyCarryingArmor) {
				cout << "You can only carry one armor piece in your inventory." << endl;
				storeItem(itemGiven, itemType);
				return;
			}

			if (slot >= 1 && slot <= 3) {

				if (inventory[slot - 1] == "nothing atm") {

					inventory[slot - 1] = itemGiven;

					cout << itemGiven << " was stored in inventory slot "
						<< slot << "." << endl;
				}
				else {
					cout << "That inventory slot is full." << endl;
					storeItem(itemGiven, itemType);
				}

			}
			else {
				cout << "Invalid slot." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else {
			cout << "Invalid storage choice." << endl;
			storeItem(itemGiven, itemType);
		}
	}

	// =========================================
	// SCROLL - INVENTORY ONLY
	// =========================================

	else if (itemType == 3) {

		cout << "Scrolls can only be stored in your inventory." << endl;

		int slot;

		cout << "Which inventory slot?" << endl;
		cout << "1: Inventory slot 1" << endl;
		cout << "2: Inventory slot 2" << endl;
		cout << "3: Inventory slot 3" << endl;
		cin >> slot;

		if (slot >= 1 && slot <= 3) {

			if (inventory[slot - 1] == "nothing atm") {

				inventory[slot - 1] = itemGiven;

				cout << itemGiven << " was stored in inventory slot "
					<< slot << "." << endl;
			}
			else {
				cout << "That inventory slot is full." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else {
			cout << "Invalid slot." << endl;
			storeItem(itemGiven, itemType);
		}
	}

	// =========================================
	// POWER RING - ACCESSORIES OR INVENTORY
	// =========================================

	else if (itemType == 4) {

		cout << "Where would you like to store your ring?" << endl;
		cout << "1: Wear ring" << endl;
		cout << "2: Inventory" << endl;
		cin >> whereStore;

		if (whereStore == 1) {

			int slot;

			cout << "Which ring slot?" << endl;
			cout << "1: Right hand" << endl;
			cout << "2: Left hand" << endl;
			cin >> slot;

			if (slot == 1 || slot == 2) {

				if (accessories[slot - 1] == "nothing atm") {

					accessories[slot - 1] = itemGiven;

					cout << itemGiven << " was equipped on your "
						<< (slot == 1 ? "right" : "left")
						<< " hand." << endl;
				}
				else {
					cout << "That ring slot is already full." << endl;
					storeItem(itemGiven, itemType);
				}

			}
			else {
				cout << "Invalid ring slot." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else if (whereStore == 2) {

			int slot;

			cout << "Which inventory slot?" << endl;
			cout << "1: Inventory slot 1" << endl;
			cout << "2: Inventory slot 2" << endl;
			cout << "3: Inventory slot 3" << endl;
			cin >> slot;

			if (slot >= 1 && slot <= 3) {

				if (inventory[slot - 1] == "nothing atm") {

					inventory[slot - 1] = itemGiven;

					cout << itemGiven << " was stored in inventory slot "
						<< slot << "." << endl;
				}
				else {
					cout << "That inventory slot is full." << endl;
					storeItem(itemGiven, itemType);
				}

			}
			else {
				cout << "Invalid slot." << endl;
				storeItem(itemGiven, itemType);
			}

		}
		else {
			cout << "Invalid storage choice." << endl;
			storeItem(itemGiven, itemType);
		}
	}

	playerStats();
	lvlGenerator(false);
}

// ============================================================
// CHECK IF AN ITEM IS A RING
// ============================================================

bool isRing(string item) {

	if (item == "Ring of Vitality (+10 MAX Hp)" ||
		item == "Ring of Strength (+3 to attack)" ||
		item == "ring of lightning (free 1d6 attack)") {

		return true;
	}

	return false;
}

// ============================================================
// CHECK IF AN ITEM IS A SCROLL
// ============================================================

bool isScroll(string item) {

	if (item == "Scroll of Fireball (1d20)" ||
		item == "Scroll of Healing (heal 2d10)" ||
		item == "Scroll of Attack (+1d6 to damage)" ||
		item == "Scroll of Speed (+1 attack)" ||
		item == "Scroll of Divinity (+10 MAX Hp)" ||
		item == "Scroll of Chance (x2 attack but can miss)") {

		return true;
	}

	return false;
}

// ============================================================
// CHECK IF AN ITEM IS ARMOR
// ============================================================

bool isArmor(string item) {

	return item == "Studded lether +5 to Hp" ||
		item == "Chainmail +10 to Hp" ||
		item == "Plate armor +20 to hp";
}
