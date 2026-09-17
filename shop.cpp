#include "shop.h"
#include "globals.h"
#include "game.h"
#include "items.h"
#include <iostream>
#include <string>

using namespace std;

// ============================================================
// SHOP DISPLAY HELPERS
// ============================================================

void shopTitle(const string& text) {
	cout << orangeText << text << resetColor << endl;
}

void shopMessage(const string& text) {
	cout << greenText << text << resetColor << endl;
}

void shopOption(int number, const string& text) {
	cout << limeGreenText << number << ": "
		<< resetColor << greenText << text
		<< resetColor << endl;
}

void shopItem(int number, const string& item, int price) {
	cout << limeGreenText << number << ": "
		<< resetColor << blueText << item
		<< resetColor << greenText << " - "
		<< yellowText << price << " gold"
		<< resetColor << endl;
}

void shopInventorySlot(int number, const string& item) {
	cout << limeGreenText << number << ": "
		<< resetColor << yellowText << item
		<< resetColor << endl;
}

void shopGold() {
	cout << greenText << "You currently have "
		<< yellowText << gold
		<< greenText << " gold."
		<< resetColor << endl;
}

void shopPurchaseMessage(const string& item, int price) {
	cout << greenText << "You bought "
		<< blueText << item
		<< greenText << " for "
		<< yellowText << price
		<< greenText << " gold."
		<< resetColor << endl;
}

void shopSaleMessage(const string& item, int price) {
	cout << greenText << "You sold "
		<< blueText << item
		<< greenText << " for "
		<< yellowText << price
		<< greenText << " gold!"
		<< resetColor << endl;
}

// ============================================================
// ITEM SELL PRICES
// ============================================================

int getSellPrice(const string& item) {

	if (item == "basic ring") {
		return 5;
	}
	else if (item == "scrap") {
		return 3;
	}
	else if (item == "chain") {
		return 5;
	}
	else if (item == "Dagger 4d4-3") {
		return 15;
	}
	else if (item == "Saber 3d4") {
		return 20;
	}
	else if (item == "Axe 2d4") {
		return 20;
	}
	else if (item == "Sythe 1d8") {
		return 15;
	}
	else if (item == "Long Sword 2d8-3") {
		return 25;
	}
	else if (item == "Lance 1d12-3+critchance") {
		return 30;
	}
	else if (item == "Studded lether +5 to Hp") {
		return 30;
	}
	else if (item == "Chainmail +10 to Hp") {
		return 45;
	}
	else if (item == "Plate armor +20 to hp") {
		return 70;
	}
	else if (item == "Scroll of Fireball (1d20)") {
		return 35;
	}
	else if (item == "Scroll of Healing (heal 2d10)") {
		return 30;
	}
	else if (item == "Scroll of Attack (+1d6 to damage)") {
		return 35;
	}
	else if (item == "Scroll of Speed (+1 attack)") {
		return 40;
	}
	else if (item == "Scroll of Divinity (+10 MAX Hp)") {
		return 50;
	}
	else if (item == "Scroll of Chance (x2 attack but can miss)") {
		return 50;
	}
	else if (item == "Ring of Vitality (+10 MAX Hp)") {
		return 50;
	}
	else if (item == "Ring of Strength (+3 to attack)") {
		return 50;
	}
	else if (item == "ring of lightning (free 1d6 attack)") {
		return 60;
	}

	return 5;
}

// ============================================================
// SELL WEAPON
// ============================================================

void sellWeapon() {

	int slot;

	cout << endl;
	shopTitle("Which weapon would you like to sell?");

	cout << limeGreenText << "1: Weapon slot 1 - "
		<< resetColor << blueText << weaponSlots[0]
		<< resetColor << endl;

	cout << limeGreenText << "2: Weapon slot 2 - "
		<< resetColor << blueText << weaponSlots[1]
		<< resetColor << endl;

	shopOption(3, "Go back");
	cin >> slot;

	if (slot == 3) {
		return;
	}

	if (slot != 1 && slot != 2) {
		shopMessage("Invalid choice.");
		return;
	}

	if (weaponSlots[slot - 1] == "nothing atm") {
		shopMessage("There is no weapon in that slot.");
		return;
	}

	string itemSold = weaponSlots[slot - 1];
	int sellPrice = getSellPrice(itemSold);

	weaponSlots[slot - 1] = "nothing atm";
	gold += sellPrice;

	cout << endl;
	shopSaleMessage(itemSold, sellPrice);
	shopGold();
}

// ============================================================
// SELL ACCESSORY
// ============================================================

void sellAccessory() {

	int slot;

	cout << endl;
	shopTitle("Which accessory would you like to sell?");

	cout << limeGreenText << "1: Right hand - "
		<< resetColor << blueText << accessories[0]
		<< resetColor << endl;

	cout << limeGreenText << "2: Left hand - "
		<< resetColor << blueText << accessories[1]
		<< resetColor << endl;

	cout << limeGreenText << "3: Body - "
		<< resetColor << blueText << accessories[2]
		<< resetColor << endl;

	shopOption(4, "Go back");
	cin >> slot;

	if (slot == 4) {
		return;
	}

	if (slot < 1 || slot > 3) {
		shopMessage("Invalid choice.");
		return;
	}

	if (accessories[slot - 1] == "nothing atm") {
		shopMessage("There is nothing equipped in that slot.");
		return;
	}

	string itemSold = accessories[slot - 1];
	int sellPrice = getSellPrice(itemSold);

	accessories[slot - 1] = "nothing atm";
	gold += sellPrice;

	cout << endl;
	shopSaleMessage(itemSold, sellPrice);
	shopGold();
}

// ============================================================
// SELL INVENTORY ITEM
// ============================================================

void sellInventoryItem() {

	int slot;

	cout << endl;
	shopTitle("Which inventory item would you like to sell?");

	shopInventorySlot(1, inventory[0]);
	shopInventorySlot(2, inventory[1]);
	shopInventorySlot(3, inventory[2]);
	shopOption(4, "Go back");

	cin >> slot;

	if (slot == 4) {
		return;
	}

	if (slot < 1 || slot > 3) {
		shopMessage("Invalid choice.");
		return;
	}

	if (inventory[slot - 1] == "nothing atm") {
		shopMessage("There is nothing in that inventory slot.");
		return;
	}

	string itemSold = inventory[slot - 1];
	int sellPrice = getSellPrice(itemSold);

	inventory[slot - 1] = "nothing atm";
	gold += sellPrice;

	cout << endl;
	shopSaleMessage(itemSold, sellPrice);
	shopGold();
}

// ============================================================
// BUY COMMON ITEM
// ============================================================

void buyCommonItem() {

	int choice;

	cout << endl;
	shopTitle("Common items");

	shopItem(1, "Basic ring", 10);
	shopItem(2, "Scrap", 6);
	shopItem(3, "Chain", 10);

	cin >> choice;

	string itemBought;
	int price;

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
		shopMessage("Invalid choice.");
		return;
	}

	if (gold < price) {
		shopMessage("You do not have enough gold.");
		return;
	}

	int slot;

	shopTitle("Which inventory slot would you like to put it in?");
	shopInventorySlot(1, inventory[0]);
	shopInventorySlot(2, inventory[1]);
	shopInventorySlot(3, inventory[2]);

	cin >> slot;

	if (slot >= 1 && slot <= 3 &&
		inventory[slot - 1] == "nothing atm") {

		inventory[slot - 1] = itemBought;
		gold -= price;

		shopPurchaseMessage(itemBought, price);
	}
	else {
		shopMessage("That inventory slot is unavailable.");
	}
}

// ============================================================
// BUY WEAPON
// ============================================================

void buyWeapon() {

	int choice;

	cout << endl;
	shopTitle("Weapons");

	shopItem(1, "Dagger 4d4-3", 30);
	shopItem(2, "Saber 3d4", 35);
	shopItem(3, "Axe 2d4", 35);
	shopItem(4, "Sythe 1d8", 30);
	shopItem(5, "Long Sword 2d8-3", 40);
	shopItem(6, "Lance 1d12-3+critchance", 50);

	cin >> choice;

	string itemBought;
	int price;

	if (choice >= 1 && choice <= 6) {
		itemBought = allItems[1][choice - 1];

		if (choice == 1) {
			price = 30;
		}
		else if (choice == 2 || choice == 3) {
			price = 35;
		}
		else if (choice == 4) {
			price = 30;
		}
		else if (choice == 5) {
			price = 40;
		}
		else {
			price = 50;
		}
	}
	else {
		shopMessage("Invalid choice.");
		return;
	}

	if (gold < price) {
		shopMessage("You do not have enough gold.");
		return;
	}

	int storage;

	shopTitle("Where would you like to store the weapon?");
	shopOption(1, "Weapon slot");
	shopOption(2, "Inventory");
	cin >> storage;

	if (storage == 1) {

		int slot;

		shopTitle("Which weapon slot?");
		shopInventorySlot(1, weaponSlots[0]);
		shopInventorySlot(2, weaponSlots[1]);

		cin >> slot;

		if (slot >= 1 && slot <= 2 &&
			weaponSlots[slot - 1] == "nothing atm") {

			weaponSlots[slot - 1] = itemBought;
			gold -= price;

			shopPurchaseMessage(itemBought, price);
		}
		else {
			shopMessage("That weapon slot is unavailable.");
		}
	}
	else if (storage == 2) {

		int slot;

		shopTitle("Which inventory slot?");
		shopInventorySlot(1, inventory[0]);
		shopInventorySlot(2, inventory[1]);
		shopInventorySlot(3, inventory[2]);

		cin >> slot;

		if (slot >= 1 && slot <= 3 &&
			inventory[slot - 1] == "nothing atm") {

			inventory[slot - 1] = itemBought;
			gold -= price;

			shopPurchaseMessage(itemBought, price);
		}
		else {
			shopMessage("That inventory slot is unavailable.");
		}
	}
	else {
		shopMessage("Invalid storage choice.");
	}
}

// ============================================================
// BUY ARMOR
// ============================================================

void buyArmor() {

	int choice;

	cout << endl;
	shopTitle("Armor");

	shopItem(1, "Studded lether +5 to Hp", 40);
	shopItem(2, "Chainmail +10 to Hp", 60);
	shopItem(3, "Plate armor +20 to hp", 90);

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
		shopMessage("Invalid choice.");
		return;
	}

	if (gold < price) {
		shopMessage("You do not have enough gold.");
		return;
	}

	int storage;

	shopTitle("Where would you like to store the armor?");
	shopOption(1, "Equip armor");
	shopOption(2, "Inventory");
	cin >> storage;

	if (storage == 1) {

		if (accessories[2] == "nothing atm") {

			accessories[2] = itemBought;
			gold -= price;

			cout << greenText << "You bought and equipped "
				<< blueText << itemBought
				<< greenText << " for "
				<< yellowText << price
				<< greenText << " gold."
				<< resetColor << endl;
		}
		else {
			shopMessage("You are already wearing armor.");
		}
	}
	else if (storage == 2) {

		int slot;

		shopTitle("Which inventory slot?");
		shopInventorySlot(1, inventory[0]);
		shopInventorySlot(2, inventory[1]);
		shopInventorySlot(3, inventory[2]);

		cin >> slot;

		bool alreadyCarryingArmor = false;

		for (int i = 0; i < 3; i++) {
			if (isArmor(inventory[i])) {
				alreadyCarryingArmor = true;
			}
		}

		if (alreadyCarryingArmor) {
			shopMessage(
				"You can only carry one armor piece in your inventory."
			);
		}
		else if (slot >= 1 && slot <= 3 &&
			inventory[slot - 1] == "nothing atm") {

			inventory[slot - 1] = itemBought;
			gold -= price;

			shopPurchaseMessage(itemBought, price);
		}
		else {
			shopMessage("That inventory slot is unavailable.");
		}
	}
	else {
		shopMessage("Invalid storage choice.");
	}
}

// ============================================================
// BUY SCROLL
// ============================================================

void buyScroll() {

	int choice;

	cout << endl;
	shopTitle("Scrolls");

	shopItem(1, "Fireball", 50);
	shopItem(2, "Healing", 45);
	shopItem(3, "Attack", 50);
	shopItem(4, "Speed", 60);
	shopItem(5, "Divinity", 70);
	shopItem(6, "Chance", 75);

	cin >> choice;

	if (choice < 1 || choice > 6) {
		shopMessage("Invalid choice.");
		return;
	}

	string itemBought = allItems[3][choice - 1];
	int price;

	if (choice == 1 || choice == 3) {
		price = 50;
	}
	else if (choice == 2) {
		price = 45;
	}
	else if (choice == 4) {
		price = 60;
	}
	else if (choice == 5) {
		price = 70;
	}
	else {
		price = 75;
	}

	if (gold < price) {
		shopMessage("You do not have enough gold.");
		return;
	}

	int slot;

	shopTitle("Which inventory slot would you like to use?");
	shopInventorySlot(1, inventory[0]);
	shopInventorySlot(2, inventory[1]);
	shopInventorySlot(3, inventory[2]);

	cin >> slot;

	if (slot >= 1 && slot <= 3 &&
		inventory[slot - 1] == "nothing atm") {

		inventory[slot - 1] = itemBought;
		gold -= price;

		shopPurchaseMessage(itemBought, price);
	}
	else {
		shopMessage("That inventory slot is unavailable.");
	}
}

// ============================================================
// BUY RING
// ============================================================

void buyRing() {

	int choice;

	cout << endl;
	shopTitle("Legendary Rings");

	shopItem(1, "Ring of Vitality", 100);
	shopItem(2, "Ring of Strength", 100);
	shopItem(3, "Ring of Lightning", 125);

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
		shopMessage("Invalid choice.");
		return;
	}

	if (gold < price) {
		shopMessage("You do not have enough gold.");
		return;
	}

	int storage;

	shopTitle("Where would you like to store the ring?");
	shopOption(1, "Equip ring");
	shopOption(2, "Inventory");
	cin >> storage;

	if (storage == 1) {

		int slot;

		shopTitle("Which ring slot?");
		shopOption(1, "Right hand");
		shopOption(2, "Left hand");
		cin >> slot;

		if (slot >= 1 && slot <= 2 &&
			accessories[slot - 1] == "nothing atm") {

			accessories[slot - 1] = itemBought;
			gold -= price;

			cout << greenText << "You bought and equipped "
				<< blueText << itemBought
				<< greenText << " for "
				<< yellowText << price
				<< greenText << " gold."
				<< resetColor << endl;
		}
		else {
			shopMessage("That ring slot is unavailable.");
		}
	}
	else if (storage == 2) {

		int slot;

		shopTitle("Which inventory slot?");
		shopInventorySlot(1, inventory[0]);
		shopInventorySlot(2, inventory[1]);
		shopInventorySlot(3, inventory[2]);

		cin >> slot;

		if (slot >= 1 && slot <= 3 &&
			inventory[slot - 1] == "nothing atm") {

			inventory[slot - 1] = itemBought;
			gold -= price;

			shopPurchaseMessage(itemBought, price);
		}
		else {
			shopMessage("That inventory slot is unavailable.");
		}
	}
	else {
		shopMessage("Invalid storage choice.");
	}
}

// ============================================================
// SHOP
// ============================================================

void shop() {

	int whatDo;

	cout << endl;
	shopTitle("===== WANDERING MERCHANT =====");
	shopGold();
	cout << endl;

	shopMessage("What would you like to do?");
	shopOption(1, "Sell");
	shopOption(2, "Buy");
	shopOption(3, "Leave shop");

	cin >> whatDo;

	// ========================================================
	// SELL
	// ========================================================

	if (whatDo == 1) {

		int whereSell;

		cout << endl;
		shopTitle("What would you like to sell?");
		shopOption(1, "Weapon");
		shopOption(2, "Accessory");
		shopOption(3, "Inventory item");
		shopOption(4, "Go back");

		cin >> whereSell;

		if (whereSell == 1) {
			sellWeapon();
		}
		else if (whereSell == 2) {
			sellAccessory();
		}
		else if (whereSell == 3) {
			sellInventoryItem();
		}
		else if (whereSell == 4) {
			return;
		}
		else {
			shopMessage("Invalid choice.");
		}

		shop();
		return;
	}

	// ========================================================
	// BUY
	// ========================================================

	if (whatDo == 2) {

		int whatBuy;

		cout << endl;
		shopTitle("What would you like to buy?");
		shopOption(1, "Common items");
		shopOption(2, "Weapons");
		shopOption(3, "Armor");
		shopOption(4, "Scrolls");
		shopOption(5, "Legendary rings");
		shopOption(6, "Go back");

		cin >> whatBuy;

		if (whatBuy == 1) {
			buyCommonItem();
		}
		else if (whatBuy == 2) {
			buyWeapon();
		}
		else if (whatBuy == 3) {
			buyArmor();
		}
		else if (whatBuy == 4) {
			buyScroll();
		}
		else if (whatBuy == 5) {
			buyRing();
		}
		else if (whatBuy == 6) {
			return;
		}
		else {
			shopMessage("Invalid choice.");
		}

		shop();
		return;
	}

	// ========================================================
	// LEAVE SHOP
	// ========================================================

	if (whatDo == 3) {

		cout << endl;
		shopMessage("You leave the wandering merchant.");
		cout << endl;

		restLevel(false, true);
		return;
	}

	shopMessage("Invalid choice.");
	shop();
}