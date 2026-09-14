#include "shop.h"
#include "globals.h"
#include "game.h"
#include "items.h"
#include <iostream>

using namespace std;

void shop() {

	int whatDo;

	cout << "You currently have " << gold << " gold." << endl;
	cout << endl;

	cout << "What would you like to do?" << endl;
	cout << "1: Sell" << endl;
	cout << "2: Buy" << endl;
	cout << "3: Leave shop" << endl;
	cin >> whatDo;


	// =========================================
	// SELL
	// =========================================

	if (whatDo == 1) {

		int whereSell;

		cout << endl;
		cout << "What would you like to sell?" << endl;
		cout << "1: Weapon" << endl;
		cout << "2: Accessory" << endl;
		cout << "3: Inventory item" << endl;
		cout << "4: Go back" << endl;
		cin >> whereSell;


		// -----------------------------------------
		// SELL WEAPON
		// -----------------------------------------

		if (whereSell == 1) {

			int slot;

			cout << endl;
			cout << "Which weapon would you like to sell?" << endl;
			cout << "1: Weapon slot 1 - " << weaponSlots[0] << endl;
			cout << "2: Weapon slot 2 - " << weaponSlots[1] << endl;
			cout << "3: Go back" << endl;
			cin >> slot;


			if (slot == 1 || slot == 2) {

				if (weaponSlots[slot - 1] == "nothing atm") {

					cout << "There is no weapon in that slot." << endl;
					shop();
					return;
				}

				string itemSold = weaponSlots[slot - 1];
				int sellPrice = 0;


				// Weapon prices
				if (itemSold == "Dagger 4d4-3") {
					sellPrice = 15;
				}
				else if (itemSold == "Saber 3d4") {
					sellPrice = 20;
				}
				else if (itemSold == "Axe 2d4") {
					sellPrice = 20;
				}
				else if (itemSold == "Sythe 1d8") {
					sellPrice = 15;
				}
				else if (itemSold == "Long Sword 2d8-3") {
					sellPrice = 25;
				}
				else if (itemSold == "Lance 1d12-3+critchance") {
					sellPrice = 30;
				}
				else {
					sellPrice = 10;
				}


				weaponSlots[slot - 1] = "nothing atm";
				gold += sellPrice;

				cout << endl;
				cout << "You sold " << itemSold << " for "
					<< sellPrice << " gold!" << endl;

				cout << "You now have " << gold << " gold." << endl;

				shop();
				return;
			}


			else if (slot == 3) {
				shop();
				return;
			}


			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}
		}


		// -----------------------------------------
		// SELL ACCESSORY
		// -----------------------------------------

		else if (whereSell == 2) {

			int slot;

			cout << endl;
			cout << "Which accessory would you like to sell?" << endl;
			cout << "1: Right hand - " << accessories[0] << endl;
			cout << "2: Left hand - " << accessories[1] << endl;
			cout << "3: Body - " << accessories[2] << endl;
			cout << "4: Go back" << endl;
			cin >> slot;


			if (slot >= 1 && slot <= 3) {

				if (accessories[slot - 1] == "nothing atm") {

					cout << "There is nothing equipped in that slot." << endl;
					shop();
					return;
				}

				string itemSold = accessories[slot - 1];
				int sellPrice = 0;


				// Ring prices
				if (itemSold == "Ring of Vitality (+10 MAX Hp)") {
					sellPrice = 50;
				}
				else if (itemSold == "Ring of Strength (+3 to attack)") {
					sellPrice = 50;
				}
				else if (itemSold == "ring of lightning (free 1d6 attack)") {
					sellPrice = 60;
				}

				// Armor prices
				else if (itemSold == "Studded lether +5 to Hp") {
					sellPrice = 30;
				}
				else if (itemSold == "Chainmail +10 to Hp") {
					sellPrice = 45;
				}
				else if (itemSold == "Plate armor +20 to hp") {
					sellPrice = 70;
				}
				else {
					sellPrice = 10;
				}


				accessories[slot - 1] = "nothing atm";
				gold += sellPrice;

				cout << endl;
				cout << "You sold " << itemSold << " for "
					<< sellPrice << " gold!" << endl;

				cout << "You now have " << gold << " gold." << endl;

				shop();
				return;
			}


			else if (slot == 4) {
				shop();
				return;
			}


			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}
		}


		// -----------------------------------------
		// SELL INVENTORY ITEM
		// -----------------------------------------

		else if (whereSell == 3) {

			int slot;

			cout << endl;
			cout << "Which inventory item would you like to sell?" << endl;
			cout << "1: " << inventory[0] << endl;
			cout << "2: " << inventory[1] << endl;
			cout << "3: " << inventory[2] << endl;
			cout << "4: Go back" << endl;
			cin >> slot;


			if (slot >= 1 && slot <= 3) {

				if (inventory[slot - 1] == "nothing atm") {

					cout << "There is nothing in that inventory slot." << endl;
					shop();
					return;
				}

				string itemSold = inventory[slot - 1];
				int sellPrice = 0;


				// Common items
				if (itemSold == "basic ring") {
					sellPrice = 5;
				}
				else if (itemSold == "scrap") {
					sellPrice = 3;
				}
				else if (itemSold == "chain") {
					sellPrice = 5;
				}

				// Weapons
				else if (itemSold == "Dagger 4d4-3") {
					sellPrice = 15;
				}
				else if (itemSold == "Saber 3d4") {
					sellPrice = 20;
				}
				else if (itemSold == "Axe 2d4") {
					sellPrice = 20;
				}
				else if (itemSold == "Sythe 1d8") {
					sellPrice = 15;
				}
				else if (itemSold == "Long Sword 2d8-3") {
					sellPrice = 25;
				}
				else if (itemSold == "Lance 1d12-3+critchance") {
					sellPrice = 30;
				}

				// Armor
				else if (itemSold == "Studded lether +5 to Hp") {
					sellPrice = 30;
				}
				else if (itemSold == "Chainmail +10 to Hp") {
					sellPrice = 45;
				}
				else if (itemSold == "Plate armor +20 to hp") {
					sellPrice = 70;
				}

				// Scrolls
				else if (itemSold == "Scroll of Fireball (1d20)") {
					sellPrice = 35;
				}
				else if (itemSold == "Scroll of Healing (heal 2d10)") {
					sellPrice = 30;
				}
				else if (itemSold == "Scroll of Attack (+1d6 to damage)") {
					sellPrice = 35;
				}
				else if (itemSold == "Scroll of Speed (+1 attack)") {
					sellPrice = 40;
				}
				else if (itemSold == "Scroll of Divinity (+10 MAX Hp)") {
					sellPrice = 50;
				}
				else if (itemSold == "Scroll of Chance (x2 attack but can miss)") {
					sellPrice = 50;
				}

				// Legendary rings
				else if (itemSold == "Ring of Vitality (+10 MAX Hp)") {
					sellPrice = 50;
				}
				else if (itemSold == "Ring of Strength (+3 to attack)") {
					sellPrice = 50;
				}
				else if (itemSold == "ring of lightning (free 1d6 attack)") {
					sellPrice = 60;
				}

				else {
					sellPrice = 5;
				}


				inventory[slot - 1] = "nothing atm";
				gold += sellPrice;

				cout << endl;
				cout << "You sold " << itemSold << " for "
					<< sellPrice << " gold!" << endl;

				cout << "You now have " << gold << " gold." << endl;

				shop();
				return;
			}


			else if (slot == 4) {
				shop();
				return;
			}


			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}
		}


		else if (whereSell == 4) {
			shop();
			return;
		}


		else {
			cout << "Invalid choice." << endl;
			shop();
			return;
		}
	}


	// =========================================
	// BUY
	// =========================================

	else if (whatDo == 2) {

		int whatBuy;

		cout << endl;
		cout << "What would you like to buy?" << endl;
		cout << "1: Common items" << endl;
		cout << "2: Weapons" << endl;
		cout << "3: Armor" << endl;
		cout << "4: Scrolls" << endl;
		cout << "5: Legendary rings" << endl;
		cout << "6: Go back" << endl;
		cin >> whatBuy;


		// -----------------------------------------
		// COMMON ITEMS
		// -----------------------------------------

		if (whatBuy == 1) {

			int choice;
			string itemBought;
			int price;

			cout << endl;
			cout << "Common items:" << endl;
			cout << "1: Basic ring - 10 gold" << endl;
			cout << "2: Scrap - 6 gold" << endl;
			cout << "3: Chain - 10 gold" << endl;
			cin >> choice;


			if (choice == 1) {
				itemBought = "basic ring";
				price = 10;
			}
			else if (choice == 2) {
				itemBought = "scrap";
				price = 6;
			}
			else if (choice == 3) {
				itemBought = "chain";
				price = 10;
			}
			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}


			if (gold < price) {
				cout << "You do not have enough gold." << endl;
				shop();
				return;
			}


			int slot;

			cout << "Which inventory slot would you like to put it in?" << endl;
			cout << "1: " << inventory[0] << endl;
			cout << "2: " << inventory[1] << endl;
			cout << "3: " << inventory[2] << endl;
			cin >> slot;


			if (slot >= 1 && slot <= 3 &&
				inventory[slot - 1] == "nothing atm") {

				inventory[slot - 1] = itemBought;
				gold -= price;

				cout << "You bought " << itemBought << " for "
					<< price << " gold." << endl;
			}
			else {
				cout << "That inventory slot is unavailable." << endl;
			}

			shop();
			return;
		}


		// -----------------------------------------
		// WEAPONS
		// -----------------------------------------

		else if (whatBuy == 2) {

			int choice;

			cout << endl;
			cout << "Weapons:" << endl;
			cout << "1: Dagger 4d4-3 - 30 gold" << endl;
			cout << "2: Saber 3d4 - 35 gold" << endl;
			cout << "3: Axe 2d4 - 35 gold" << endl;
			cout << "4: Sythe 1d8 - 30 gold" << endl;
			cout << "5: Long Sword 2d8-3 - 40 gold" << endl;
			cout << "6: Lance 1d12-3+critchance - 50 gold" << endl;
			cin >> choice;


			string itemBought;
			int price;


			if (choice == 1) {
				itemBought = allItems[1][0];
				price = 30;
			}
			else if (choice == 2) {
				itemBought = allItems[1][1];
				price = 35;
			}
			else if (choice == 3) {
				itemBought = allItems[1][2];
				price = 35;
			}
			else if (choice == 4) {
				itemBought = allItems[1][3];
				price = 30;
			}
			else if (choice == 5) {
				itemBought = allItems[1][4];
				price = 40;
			}
			else if (choice == 6) {
				itemBought = allItems[1][5];
				price = 50;
			}
			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}


			if (gold < price) {
				cout << "You do not have enough gold." << endl;
				shop();
				return;
			}


			int storage;
			cout << "Where would you like to store the weapon?" << endl;
			cout << "1: Weapon slot" << endl;
			cout << "2: Inventory" << endl;
			cin >> storage;


			if (storage == 1) {

				int slot;

				cout << "Which weapon slot?" << endl;
				cout << "1: " << weaponSlots[0] << endl;
				cout << "2: " << weaponSlots[1] << endl;
				cin >> slot;


				if (slot >= 1 && slot <= 2 &&
					weaponSlots[slot - 1] == "nothing atm") {

					weaponSlots[slot - 1] = itemBought;
					gold -= price;

					cout << "You bought " << itemBought << " for "
						<< price << " gold." << endl;
				}
				else {
					cout << "That weapon slot is unavailable." << endl;
				}
			}


			else if (storage == 2) {

				int slot;

				cout << "Which inventory slot?" << endl;
				cout << "1: " << inventory[0] << endl;
				cout << "2: " << inventory[1] << endl;
				cout << "3: " << inventory[2] << endl;
				cin >> slot;

				if (slot >= 1 && slot <= 3 &&
					inventory[slot - 1] == "nothing atm") {

					inventory[slot - 1] = itemBought;
					gold -= price;

					cout << "You bought " << itemBought << " for "
						<< price << " gold." << endl;
				}
				else {
					cout << "That inventory slot is unavailable." << endl;
				}
			}


			else {
				cout << "Invalid storage choice." << endl;
			}


			shop();
			return;
		}


		// -----------------------------------------
		// ARMOR
		// -----------------------------------------

		else if (whatBuy == 3) {

			int choice;

			cout << endl;
			cout << "Armor:" << endl;
			cout << "1: Studded lether +5 to Hp - 40 gold" << endl;
			cout << "2: Chainmail +10 to Hp - 60 gold" << endl;
			cout << "3: Plate armor +20 to hp - 90 gold" << endl;
			cin >> choice;


			string itemBought;
			int price;


			if (choice == 1) {
				itemBought = allItems[2][0];
				price = 40;
			}
			else if (choice == 2) {
				itemBought = allItems[2][1];
				price = 60;
			}
			else if (choice == 3) {
				itemBought = allItems[2][2];
				price = 90;
			}
			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}


			if (gold < price) {
				cout << "You do not have enough gold." << endl;
				shop();
				return;
			}


			int storage;

			cout << "Where would you like to store the armor?" << endl;
			cout << "1: Equip armor" << endl;
			cout << "2: Inventory" << endl;
			cin >> storage;


			if (storage == 1) {

				if (accessories[2] == "nothing atm") {

					accessories[2] = itemBought;
					gold -= price;

					cout << "You bought and equipped "
						<< itemBought << " for "
						<< price << " gold." << endl;
				}
				else {
					cout << "You are already wearing armor." << endl;
				}
			}


			else if (storage == 2) {

				int slot;

				cout << "Which inventory slot?" << endl;
				cout << "1: " << inventory[0] << endl;
				cout << "2: " << inventory[1] << endl;
				cout << "3: " << inventory[2] << endl;
				cin >> slot;

				bool alreadyCarryingArmor = false;
				for (int i = 0; i < 3; i++) {
					if (isArmor(inventory[i])) alreadyCarryingArmor = true;
				}

				if (alreadyCarryingArmor) {
					cout << "You can only carry one armor piece in your inventory." << endl;
				}
				else if (slot >= 1 && slot <= 3 &&
					inventory[slot - 1] == "nothing atm") {

					inventory[slot - 1] = itemBought;
					gold -= price;

					cout << "You bought " << itemBought << " for "
						<< price << " gold." << endl;
				}
				else {
					cout << "That inventory slot is unavailable." << endl;
				}
			}


			else {
				cout << "Invalid storage choice." << endl;
			}


			shop();
			return;
		}


		// -----------------------------------------
		// SCROLLS
		// -----------------------------------------

		else if (whatBuy == 4) {

			int choice;

			cout << endl;
			cout << "Scrolls:" << endl;
			cout << "1: Fireball - 50 gold" << endl;
			cout << "2: Healing - 45 gold" << endl;
			cout << "3: Attack - 50 gold" << endl;
			cout << "4: Speed - 60 gold" << endl;
			cout << "5: Divinity - 70 gold" << endl;
			cout << "6: Chance - 75 gold" << endl;
			cin >> choice;


			string itemBought;
			int price;


			if (choice >= 1 && choice <= 6) {

				itemBought = allItems[3][choice - 1];

				if (choice == 1) price = 50;
				else if (choice == 2) price = 45;
				else if (choice == 3) price = 50;
				else if (choice == 4) price = 60;
				else if (choice == 5) price = 70;
				else price = 75;
			}
			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}


			if (gold < price) {
				cout << "You do not have enough gold." << endl;
				shop();
				return;
			}


			int slot;

			cout << "Which inventory slot would you like to use?" << endl;
			cout << "1: " << inventory[0] << endl;
			cout << "2: " << inventory[1] << endl;
			cout << "3: " << inventory[2] << endl;
			cin >> slot;


			if (slot >= 1 && slot <= 3 &&
				inventory[slot - 1] == "nothing atm") {

				inventory[slot - 1] = itemBought;
				gold -= price;

				cout << "You bought " << itemBought << " for "
					<< price << " gold." << endl;
			}
			else {
				cout << "That inventory slot is unavailable." << endl;
			}


			shop();
			return;
		}


		// -----------------------------------------
		// LEGENDARY RINGS
		// -----------------------------------------

		else if (whatBuy == 5) {

			int choice;

			cout << endl;
			cout << "Legendary Rings:" << endl;
			cout << "1: Ring of Vitality - 100 gold" << endl;
			cout << "2: Ring of Strength - 100 gold" << endl;
			cout << "3: Ring of Lightning - 125 gold" << endl;
			cin >> choice;


			string itemBought;
			int price;


			if (choice == 1) {
				itemBought = allItems[4][0];
				price = 100;
			}
			else if (choice == 2) {
				itemBought = allItems[4][1];
				price = 100;
			}
			else if (choice == 3) {
				itemBought = allItems[4][2];
				price = 125;
			}
			else {
				cout << "Invalid choice." << endl;
				shop();
				return;
			}


			if (gold < price) {
				cout << "You do not have enough gold." << endl;
				shop();
				return;
			}


			int storage;

			cout << "Where would you like to store the ring?" << endl;
			cout << "1: Equip ring" << endl;
			cout << "2: Inventory" << endl;
			cin >> storage;


			if (storage == 1) {

				int slot;

				cout << "Which ring slot?" << endl;
				cout << "1: Right hand" << endl;
				cout << "2: Left hand" << endl;
				cin >> slot;


				if (slot >= 1 && slot <= 2 &&
					accessories[slot - 1] == "nothing atm") {

					accessories[slot - 1] = itemBought;
					gold -= price;

					cout << "You bought and equipped "
						<< itemBought << " for "
						<< price << " gold." << endl;
				}
				else {
					cout << "That ring slot is unavailable." << endl;
				}
			}


			else if (storage == 2) {

				int slot;

				cout << "Which inventory slot?" << endl;
				cout << "1: " << inventory[0] << endl;
				cout << "2: " << inventory[1] << endl;
				cout << "3: " << inventory[2] << endl;
				cin >> slot;


				if (slot >= 1 && slot <= 3 &&
					inventory[slot - 1] == "nothing atm") {

					inventory[slot - 1] = itemBought;
					gold -= price;

					cout << "You bought " << itemBought << " for "
						<< price << " gold." << endl;
				}
				else {
					cout << "That inventory slot is unavailable." << endl;
				}
			}


			else {
				cout << "Invalid storage choice." << endl;
			}


			shop();
			return;
		}


		else if (whatBuy == 6) {
			shop();
			return;
		}


		else {
			cout << "Invalid choice." << endl;
			shop();
			return;
		}
	}


	// =========================================
	// LEAVE SHOP
	// =========================================

	else if (whatDo == 3) {

		cout << endl;
		cout << "You leave the wandering merchant." << endl;
		cout << endl;
		restLevel(NULL, true);

		return;
	}


	// =========================================
	// INVALID CHOICE
	// =========================================

	else {

		cout << "Invalid choice." << endl;
		shop();
		return;
	}
}
