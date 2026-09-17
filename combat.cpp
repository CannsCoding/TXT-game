#include "combat.h"
#include "game.h"
#include "globals.h"
#include "items.h"
#include "player.h"
#include <iostream>

using namespace std;

// ============================================================
// COMBAT
// ============================================================

void combat(string enemyName, bool isBoss) {

	resetCombat();

	if (isBoss) {

		enemyMaxHealth = 5 + (levelOfPlayer * .5) * 3 + rand() % 10 + 1;
		enemyDamage = 2 + levelOfPlayer * .5;
	}

	else {

		enemyMaxHealth = 5 + levelOfPlayer + rand() % 5 + 1;
		enemyDamage = 1 + levelOfPlayer;
	}

	enemyHealth = enemyMaxHealth;

	cout << endl;
	cout << "========================================" << endl;
	cout << "             COMBAT START" << endl;
	cout << "========================================" << endl;

	cout << "You are fighting: " << enemyName << endl;

	while (health > 0 && enemyHealth > 0) {

		// Player turn
		playerTurn();

		// Check if enemy died
		if (enemyHealth <= 0) {

			cout << endl;
			cout << "========================================" << endl;
			cout << "             ENEMY DEFEATED!" << endl;
			cout << "========================================" << endl;

			cout << "You defeated " << enemyName << "!" << endl;

			XP += isBoss ? xpGiven(30) : xpGiven(10);

			cout << "You gained " << XP << " " << " XP!" << endl;


			itemRandomizer();
			return;
		}

		// Enemy turn
		enemyTurn(enemyName);

		// Check if player died
		if (health <= 0) {
			char wouldPlay;
			cout << endl;
			cout << "You have been defeated." << endl;
			cin >> wouldPlay;

			cout << "Would you like to play again? (y/n)" << endl;
			if (wouldPlay == 'y' || wouldPlay == 'Y') {
				startGame();
				return;
			}
			else if (wouldPlay == 'n' || wouldPlay == 'N') {
				return;
			}
			else {
				cout << "Invalid input, try again" << endl;
				combat("NULL", false);
				return;
			}
		}
	}
}

// ============================================================
// ENEMY TURN
// ============================================================

void enemyTurn(string enemyName) {

	if (enemyHealth <= 0) {
		return;
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "             ENEMY TURN" << endl;
	cout << "========================================" << endl;

	int damage = enemyDamage + rand() % 3;

	cout << enemyName << " attacks you!" << endl;
	cout << "You take " << damage << " damage!" << endl;

	health -= damage;

	if (health < 0) {
		health = 0;
	}

	cout << "Your HP: "
		<< health << "/"
		<< maxHealth << endl;
}

// ============================================================
// PLAYER TURN
// ============================================================

void playerTurn() {

	attacksRemaining = 1;
	secondWeaponUsed = false;

	attackScrollActive = false;
	speedScrollActive = false;
	chanceScrollActive = false;

	attackScrollBonus = 0;

	bool turnFinished = false;

	// If the player has a second weapon, they get
	// an additional attack this turn.
	if (weaponSlots[1] != "nothing atm") {
		attacksRemaining = 2;
	}

	while (!turnFinished && enemyHealth > 0) {

		cout << endl;
		cout << "========================================" << endl;
		cout << "             YOUR TURN" << endl;
		cout << "========================================" << endl;

		cout << "Your HP: "
			<< health << "/"
			<< maxHealth << endl;

		cout << "Enemy HP: "
			<< enemyHealth << "/"
			<< enemyMaxHealth << endl;

		cout << endl;

		cout << "What would you like to do?" << endl;
		cout << "1: Use item" << endl;
		cout << "2: Use ability" << endl;

		// Weapon 1
		if (attacksRemaining > 0 &&
			weaponSlots[0] != "nothing atm") {

			cout << "3: Attack with weapon 1 - "
				<< weaponSlots[0] << endl;
		}

		// Weapon 2
		if (attacksRemaining > 0 &&
			weaponSlots[1] != "nothing atm" &&
			!secondWeaponUsed) {

			cout << "4: Attack with weapon 2 - "
				<< weaponSlots[1]
				<< " (-2 damage)" << endl;
		}

		cout << "5: End turn" << endl;

		int choice;
		cin >> choice;

		// =========================================
		// USE ITEM
		// =========================================

		if (choice == 1) {

			useItem();
		}

		// =========================================
		// USE ABILITY
		// =========================================

		else if (choice == 2) {

			useAbility();
		}

		// =========================================
		// WEAPON 1
		// =========================================

		else if (choice == 3) {

			if (attacksRemaining <= 0) {

				cout << "You have no attacks remaining." << endl;
			}

			else if (weaponSlots[0] == "nothing atm") {

				cout << "You do not have a weapon equipped." << endl;
			}

			else {

				attackWithWeapon(0);

				// If enemy died, end the player's turn
				if (enemyHealth <= 0) {
					turnFinished = true;
				}

				// If there are no attacks left, end turn
				else if (attacksRemaining <= 0) {
					turnFinished = true;
				}
			}
		}

		// =========================================
		// WEAPON 2
		// =========================================

		else if (choice == 4) {

			if (attacksRemaining <= 0) {

				cout << "You have no attacks remaining." << endl;
			}

			else if (weaponSlots[1] == "nothing atm") {

				cout << "You do not have a second weapon equipped." << endl;
			}

			else if (secondWeaponUsed) {

				cout << "You already used your second weapon." << endl;
			}

			else {

				attackWithWeapon(1);

				secondWeaponUsed = true;

				// If enemy died, end the player's turn
				if (enemyHealth <= 0) {
					turnFinished = true;
				}

				// If there are no attacks left, end turn
				else if (attacksRemaining <= 0) {
					turnFinished = true;
				}
			}
		}

		// =========================================
		// END TURN
		// =========================================

		else if (choice == 5) {

			cout << "You ended your turn." << endl;

			turnFinished = true;
		}

		else {

			cout << "Invalid choice." << endl;
		}
	}

	// Turn-based scroll effects stop here
	attackScrollActive = false;
	speedScrollActive = false;
	chanceScrollActive = false;
	attackScrollBonus = 0;
}

// ============================================================
// WEAPON ATTACK
// ============================================================

void attackWithWeapon(int weaponSlot) {

	if (weaponSlot < 0 || weaponSlot > 1) {
		return;
	}

	if (weaponSlots[weaponSlot] == "nothing atm") {

		cout << "There is no weapon in that slot!" << endl;
		return;
	}

	string weapon = weaponSlots[weaponSlot];

	int damage = rollWeaponDamage(weapon);

	// Second weapon gets -2 damage
	if (weaponSlot == 1) {

		damage -= 2;

		if (damage < 0) {
			damage = 0;
		}

		cout << "Second weapon penalty: -2 damage." << endl;
	}

	cout << endl;
	cout << "You attack with your " << weapon << "!" << endl;
	cout << "You deal " << damage << " damage!" << endl;

	enemyHealth -= damage;

	if (enemyHealth < 0) {
		enemyHealth = 0;
	}

	cout << "Enemy HP: "
		<< enemyHealth << "/"
		<< enemyMaxHealth << endl;

	attacksRemaining--;

	if (speedScrollActive && attacksRemaining > 0) {
		cout << "Scroll of Speed gives you another attack!" << endl;
	}
}

// ============================================================
// WEAPON DAMAGE
// ============================================================

int rollWeaponDamage(string weapon) {

	int damage = 0;

	if (weapon == "Dagger 4d4-3") {

		damage = ((rand() % 4 + 1) +
			(rand() % 4 + 1) +
			(rand() % 4 + 1) +
			(rand() % 4 + 1)) - 3;
	}

	else if (weapon == "Saber 3d4") {

		damage = ((rand() % 4 + 1) +
			(rand() % 4 + 1) +
			(rand() % 4 + 1));
	}

	else if (weapon == "Axe 2d4") {

		damage = ((rand() % 4 + 1) +
			(rand() % 4 + 1));
	}

	else if (weapon == "Sythe 1d8") {

		damage = (rand() % 8 + 1);
	}

	else if (weapon == "Long Sword 2d8-3") {

		damage = ((rand() % 8 + 1) +
			(rand() % 8 + 1)) - 3;
	}

	else if (weapon == "Lance 1d12-3+critchance") {

		damage = (rand() % 12 + 1) - 3;

		// 50/50 critical chance
		int critChance = rand() % 2;

		if (critChance == 1) {
			damage *= 2;
			cout << "CRITICAL HIT!" << endl;
		}
	}

	// Player level adds to damage
	damage += levelOfPlayer * .5;

	// Ring of Strength
	if (accessories[0] == "Ring of Strength (+3 to attack)" ||
		accessories[1] == "Ring of Strength (+3 to attack)") {

		damage += 3;
	}

	// Scroll of Attack
	if (attackScrollActive) {
		damage += attackScrollBonus;
	}

	// Scroll of Chance
	if (chanceScrollActive) {

		int chance = rand() % 2;

		if (chance == 0) {
			cout << "Your attack MISSED!" << endl;
			return 0;
		}

		damage *= 2;
		cout << "Scroll of Chance activated! DAMAGE DOUBLED!" << endl;
	}

	return damage;
}

// ============================================================
// USE ITEM
// ============================================================

void useItem() {

	cout << endl;
	cout << "===== ITEMS =====" << endl;

	bool hasItem = false;

	for (int i = 0; i < 3; i++) {

		if (inventory[i] != "nothing atm" &&
			isScroll(inventory[i])) {

			cout << i + 1 << ": " << inventory[i] << endl;

			hasItem = true;
		}
	}

	if (!hasItem) {

		cout << "You have no usable items." << endl;
		return;
	}

	cout << "4: Go back" << endl;

	int choice;
	cin >> choice;

	if (choice == 4) {
		return;
	}

	if (choice < 1 || choice > 3) {

		cout << "Invalid item choice." << endl;
		return;
	}

	int slot = choice - 1;

	if (inventory[slot] == "nothing atm" ||
		!isScroll(inventory[slot])) {

		cout << "That is not a usable item." << endl;
		return;
	}

	string item = inventory[slot];

	// =========================================
	// FIREBALL
	// =========================================

	if (item == "Scroll of Fireball (1d20)") {

		int damage = rand() % 20 + 1;

		cout << "You cast Fireball!" << endl;
		cout << "Fireball deals " << damage << " damage!" << endl;

		enemyHealth -= damage;

		if (enemyHealth < 0) {
			enemyHealth = 0;
		}
	}

	// =========================================
	// HEALING
	// =========================================

	else if (item == "Scroll of Healing (heal 2d10)") {

		int healing =
			(rand() % 10 + 1) +
			(rand() % 10 + 1);

		health += healing;

		if (health > maxHealth) {
			health = maxHealth;
		}

		cout << "You healed " << healing << " HP!" << endl;
		cout << "HP: " << health << "/" << maxHealth << endl;
	}

	// =========================================
	// ATTACK
	// =========================================

	else if (item == "Scroll of Attack (+1d6 to damage)") {

		attackScrollActive = true;
		attackScrollBonus = rand() % 6 + 1;

		cout << "Scroll of Attack activated!" << endl;
		cout << "Your attacks gain +"
			<< attackScrollBonus
			<< " damage for the rest of your turn." << endl;
	}

	// =========================================
	// SPEED
	// =========================================

	else if (item == "Scroll of Speed (+1 attack)") {

		speedScrollActive = true;
		attacksRemaining++;

		cout << "Scroll of Speed activated!" << endl;
		cout << "You can make an additional attack this turn." << endl;
	}

	// =========================================
	// DIVINITY
	// =========================================

	else if (item == "Scroll of Divinity (+10 MAX Hp)") {

		maxHealth += 10;
		health += 10;

		cout << "Divinity activated!" << endl;
		cout << "MAX HP increased by 10." << endl;
	}

	// =========================================
	// CHANCE
	// =========================================

	else if (item == "Scroll of Chance (x2 attack but can miss)") {

		chanceScrollActive = true;

		cout << "Scroll of Chance activated!" << endl;
		cout << "Your next attack has a 50% chance to miss." << endl;
		cout << "If it hits, its damage is doubled." << endl;
	}

	// =========================================
	// CONSUME ITEM
	// =========================================

	inventory[slot] = "nothing atm";

	cout << "The scroll was consumed." << endl;

	if (enemyHealth < 0) {
		enemyHealth = 0;
	}
}

// ============================================================
// USE ABILITY
// ============================================================

void useAbility() {

	cout << endl;
	cout << "===== ABILITIES =====" << endl;

	bool hasAbility = false;

	// -----------------------------------------
	// RING SLOT 1
	// -----------------------------------------

	if (accessories[0] != "nothing atm" &&
		isRing(accessories[0]) &&
		!abilityUsed[0]) {

		hasAbility = true;

		cout << "1: " << accessories[0] << endl;
	}

	// -----------------------------------------
	// RING SLOT 2
	// -----------------------------------------

	if (accessories[1] != "nothing atm" &&
		isRing(accessories[1]) &&
		!abilityUsed[1]) {

		hasAbility = true;

		cout << "2: " << accessories[1] << endl;
	}

	if (!hasAbility) {

		cout << "You have no available ring abilities." << endl;
		return;
	}

	cout << "3: Go back" << endl;

	int choice;
	cin >> choice;

	int ringSlot = -1;

	if (choice == 1 &&
		accessories[0] != "nothing atm" &&
		isRing(accessories[0]) &&
		!abilityUsed[0]) {

		ringSlot = 0;
	}

	else if (choice == 2 &&
		accessories[1] != "nothing atm" &&
		isRing(accessories[1]) &&
		!abilityUsed[1]) {

		ringSlot = 1;
	}

	else if (choice == 3) {

		return;
	}

	else {

		cout << "Invalid ability choice." << endl;
		return;
	}

	string ring = accessories[ringSlot];

	// =========================================
	// RING OF VITALITY
	// =========================================

	if (ring == "Ring of Vitality (+10 MAX Hp)") {

		maxHealth += 10;
		health += 10;

		cout << "Ring of Vitality activated!" << endl;
		cout << "Your MAX HP increased by 10." << endl;
		cout << "HP: " << health << "/" << maxHealth << endl;
	}

	// =========================================
	// RING OF STRENGTH
	// =========================================

	else if (ring == "Ring of Strength (+3 to attack)") {

		cout << "Ring of Strength activated!" << endl;
		cout << "You already receive +3 damage from this ring." << endl;
	}

	// =========================================
	// RING OF LIGHTNING
	// =========================================

	else if (ring == "ring of lightning (free 1d6 attack)") {

		int damage = rand() % 6 + 1;

		cout << "Lightning strikes the enemy!" << endl;
		cout << "You deal " << damage << " lightning damage!" << endl;

		enemyHealth -= damage;

		if (enemyHealth < 0) {
			enemyHealth = 0;
		}

		cout << "Enemy HP: "
			<< enemyHealth << "/"
			<< enemyMaxHealth << endl;
	}

	abilityUsed[ringSlot] = true;

	cout << "This ability cannot be used again until the next combat."
		<< endl;
}

// ============================================================
// RESET COMBAT
// ============================================================

void resetCombat() {

	abilityUsed[0] = false;
	abilityUsed[1] = false;

	attackScrollActive = false;
	speedScrollActive = false;
	chanceScrollActive = false;

	attackScrollBonus = 0;

	attacksRemaining = 1;
	secondWeaponUsed = false;
}

// ============================================================
// ENEMY CHOICE
// ============================================================

void enemyChoice(bool isBoss) {

	int enemyGen = rand() % 3 + 1;

	string enemyType;

	if (isBoss) {

		if (enemyGen == 1) {
			enemyType = "giantEnemySpider";
		}
		else if (enemyGen == 2) {
			enemyType = "amalgamation";
		}
		else if (enemyGen == 3) {
			enemyType = "lostSouls";
		}
	}

	else {

		if (enemyGen == 1) {
			enemyType = "splittingSlime";
		}
		else if (enemyGen == 2) {
			enemyType = "allEaterSnail";
		}
		else if (enemyGen == 3) {
			enemyType = "twistedHuman";
		}
	}

	cout << "You are fighting a " << enemyType << "!" << endl;

	combat(enemyType, isBoss);
}