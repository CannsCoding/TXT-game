#include "combat.h"
#include "game.h"
#include "globals.h"
#include "items.h"
#include "player.h"
#include <iostream>

using namespace std;

void combatHeader(const string& title) {
	cout << '\n';
	cout << blueText
		<< "========================================"
		<< resetColor << endl;

	cout << purpleText
		<< "             " << title
		<< resetColor << endl;

	cout << blueText
		<< "========================================"
		<< resetColor << '\n';
}

void printMessage(const string& message) {
	cout << greenText << message << resetColor << endl;
}

void printOption(int number, const string& message) {
	cout << limeGreenText << number << ": "
		<< resetColor << greenText
		<< message << resetColor << endl;
}

void printValue(const string& label, int value, int maximum) {
	cout << limeGreenText << label << ": "
		<< resetColor << yellowText << value
		<< "/" << maximum << resetColor << endl;
}

// ============================================================
// COMBAT
// ============================================================

void combat(string enemyName, bool isBoss) {

	resetCombat();

	if (isBoss) {
		enemyMaxHealth = 5 + (levelOfPlayer * 1.5) * 3
			+ rand() % 10 + 1;
		enemyDamage = 2 + levelOfPlayer * 1.5;
	}
	else {
		enemyMaxHealth = 5 + levelOfPlayer + rand() % 5 + 1;
		enemyDamage = 1 + levelOfPlayer;
	}

	enemyHealth = enemyMaxHealth;

	combatHeader("COMBAT START");

	cout << greenText << "You are fighting: "
		<< blueText << enemyName
		<< resetColor << endl;

	while (health > 0 && enemyHealth > 0) {

		playerTurn();

		if (enemyHealth <= 0) {
			combatHeader("ENEMY DEFEATED!");

			cout << greenText << "You defeated "
				<< blueText << enemyName
				<< greenText << "!"
				<< resetColor << endl;

			xpGiven(isBoss ? 30 : 10);

			itemRandomizer();
			return;
		}

		enemyTurn(enemyName);

		if (health <= 0) {
			char wouldPlay;

			cout << redText
				<< "You have been defeated."
				<< resetColor << endl;
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

	combatHeader("ENEMY TURN");

	int damage = enemyDamage + rand() % 3;

	cout << blueText << enemyName
		<< greenText << " attacks you!"
		<< resetColor << endl;

	cout << greenText << "You take "
		<< redText << damage
		<< greenText << " damage!"
		<< resetColor << endl;

	health -= damage;

	if (health < 0) {
		health = 0;
	}

	printValue("Your HP", health, maxHealth);
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

	if (weaponSlots[1] != "nothing atm") {
		attacksRemaining = 2;
	}

	while (!turnFinished && enemyHealth > 0) {

		combatHeader("YOUR TURN");

		printValue("Your HP", health, maxHealth);
		printValue("Enemy HP", enemyHealth, enemyMaxHealth);

		cout << '\n';
		cout << greenText
			<< "What would you like to do?"
			<< resetColor << endl;

		printOption(1, "Use item");
		printOption(2, "Use ability");

		if (attacksRemaining > 0 &&
			weaponSlots[0] != "nothing atm") {

			cout << limeGreenText << "3: "
				<< resetColor << greenText
				<< "Attack with weapon 1 - "
				<< blueText << weaponSlots[0]
				<< resetColor << endl;
		}

		if (attacksRemaining > 0 &&
			weaponSlots[1] != "nothing atm" &&
			!secondWeaponUsed) {

			cout << limeGreenText << "4: "
				<< resetColor << greenText
				<< "Attack with weapon 2 - "
				<< blueText << weaponSlots[1]
				<< greenText << " (-2 damage)"
				<< resetColor << endl;
		}

		printOption(5, "End turn");

		int choice;
		cin >> choice;

		if (choice == 1) {
			useItem();
		}
		else if (choice == 2) {
			useAbility();
		}
		else if (choice == 3) {

			if (attacksRemaining <= 0) {
				printMessage("You have no attacks remaining.");
			}
			else if (weaponSlots[0] == "nothing atm") {
				printMessage("You do not have a weapon equipped.");
			}
			else {
				attackWithWeapon(0);

				if (enemyHealth <= 0 ||
					attacksRemaining <= 0) {
					turnFinished = true;
				}
			}
		}
		else if (choice == 4) {

			if (attacksRemaining <= 0) {
				printMessage("You have no attacks remaining.");
			}
			else if (weaponSlots[1] == "nothing atm") {
				printMessage("You do not have a second weapon equipped.");
			}
			else if (secondWeaponUsed) {
				printMessage("You already used your second weapon.");
			}
			else {
				attackWithWeapon(1);
				secondWeaponUsed = true;

				if (enemyHealth <= 0 ||
					attacksRemaining <= 0) {
					turnFinished = true;
				}
			}
		}
		else if (choice == 5) {
			printMessage("You ended your turn.");
			turnFinished = true;
		}
		else {
			printMessage("Invalid choice.");
		}
	}

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
		printMessage("There is no weapon in that slot!");
		return;
	}

	string weapon = weaponSlots[weaponSlot];
	int damage = rollWeaponDamage(weapon);

	if (weaponSlot == 1) {
		damage -= 2;

		if (damage < 0) {
			damage = 0;
		}

		printMessage("Second weapon penalty: -2 damage.");
	}

	cout << greenText << "You attack with your "
		<< blueText << weapon
		<< greenText << "!"
		<< resetColor << endl;

	cout << greenText << "You deal "
		<< redText << damage
		<< greenText << " damage!"
		<< resetColor << endl;

	enemyHealth -= damage;

	if (enemyHealth < 0) {
		enemyHealth = 0;
	}

	printValue("Enemy HP", enemyHealth, enemyMaxHealth);

	attacksRemaining--;

	if (speedScrollActive && attacksRemaining > 0) {
		printMessage("Scroll of Speed gives you another attack!");
	}
}

// ============================================================
// WEAPON DAMAGE
// ============================================================

int rollWeaponDamage(string weapon) {

	int damage = 0;

	if (weapon == "Dagger 4d4-3") {
		damage = (rand() % 4 + 1)
			+ (rand() % 4 + 1)
			+ (rand() % 4 + 1)
			+ (rand() % 4 + 1) - 3;
	}
	else if (weapon == "Saber 3d4") {
		damage = (rand() % 4 + 1)
			+ (rand() % 4 + 1)
			+ (rand() % 4 + 1);
	}
	else if (weapon == "Axe 2d4") {
		damage = (rand() % 4 + 1)
			+ (rand() % 4 + 1);
	}
	else if (weapon == "Sythe 1d8") {
		damage = rand() % 8 + 1;
	}
	else if (weapon == "Long Sword 2d8-3") {
		damage = (rand() % 8 + 1)
			+ (rand() % 8 + 1) - 3;
	}
	else if (weapon == "Lance 1d12-3+critchance") {

		damage = rand() % 12 + 1 - 3;

		if (rand() % 2 == 1) {
			damage *= 2;

			cout << redText
				<< "CRITICAL HIT!"
				<< resetColor << endl;
		}
	}

	damage += levelOfPlayer * .5;

	if (accessories[0] == "Ring of Strength (+3 to attack)" ||
		accessories[1] == "Ring of Strength (+3 to attack)") {
			damage += 3;
	}

	if (attackScrollActive) {
		damage += attackScrollBonus;
	}

	if (chanceScrollActive) {

		if (rand() % 2 == 0) {
			cout << redText
				<< "Your attack MISSED!"
				<< resetColor << endl;

			return 0;
		}

		damage *= 2;

		cout << brightYellowText
			<< "Scroll of Chance activated! DAMAGE DOUBLED!"
			<< resetColor << endl;
	}

	return damage;
}

// ============================================================
// USE ITEM
// ============================================================

void useItem() {

	cout << orangeText
		<< "===== ITEMS ====="
		<< resetColor << endl;

	bool hasItem = false;

	for (int i = 0; i < 3; i++) {

		if (inventory[i] != "nothing atm" &&
			isScroll(inventory[i])) {

			cout << limeGreenText << i + 1 << ": "
				<< resetColor << blueText
				<< inventory[i]
				<< resetColor << endl;

			hasItem = true;
		}
	}

	if (!hasItem) {
		printMessage("You have no usable items.");
		return;
	}

	printOption(4, "Go back");

	int choice;
	cin >> choice;

	if (choice == 4) {
		return;
	}

	if (choice < 1 || choice > 3) {
		printMessage("Invalid item choice.");
		return;
	}

	int slot = choice - 1;

	if (inventory[slot] == "nothing atm" ||
		!isScroll(inventory[slot])) {
		printMessage("That is not a usable item.");
		return;
	}

	string item = inventory[slot];

	if (item == "Scroll of Fireball (1d20)") {

		int damage = rand() % 20 + 1;

		cout << purpleText
			<< "You cast Fireball!"
			<< resetColor << endl;

		cout << greenText << "Fireball deals "
			<< redText << damage
			<< greenText << " damage!"
			<< resetColor << endl;

		enemyHealth -= damage;

		if (enemyHealth < 0) {
			enemyHealth = 0;
		}
	}
	else if (item == "Scroll of Healing (heal 2d10)") {

		int healing = (rand() % 10 + 1)
			+ (rand() % 10 + 1);

		health += healing;

		if (health > maxHealth) {
			health = maxHealth;
		}

		cout << greenText << "You healed "
			<< limeGreenText << healing
			<< greenText << " HP!"
			<< resetColor << endl;

		printValue("HP", health, maxHealth);
	}
	else if (item == "Scroll of Attack (+1d6 to damage)") {

		attackScrollActive = true;
		attackScrollBonus = rand() % 6 + 1;

		cout << purpleText
			<< "Scroll of Attack activated!"
			<< resetColor << endl;

		cout << greenText << "Your attacks gain +"
			<< yellowText << attackScrollBonus
			<< greenText << " damage for the rest of your turn."
			<< resetColor << endl;
	}
	else if (item == "Scroll of Speed (+1 attack)") {

		speedScrollActive = true;
		attacksRemaining++;

		cout << purpleText
			<< "Scroll of Speed activated!"
			<< resetColor << endl;

		printMessage("You can make an additional attack this turn.");
	}
	else if (item == "Scroll of Divinity (+10 MAX Hp)") {

		maxHealth += 10;
		health += 10;

		cout << purpleText
			<< "Divinity activated!"
			<< resetColor << endl;

		printMessage("MAX HP increased by 10.");
	}
	else if (item == "Scroll of Chance (x2 attack but can miss)") {

		chanceScrollActive = true;

		cout << purpleText
			<< "Scroll of Chance activated!"
			<< resetColor << endl;

		printMessage("Your next attack has a 50% chance to miss.");
		printMessage("If it hits, its damage is doubled.");
	}

	inventory[slot] = "nothing atm";
	printMessage("The scroll was consumed.");

	if (enemyHealth < 0) {
		enemyHealth = 0;
	}
}

// ============================================================
// USE ABILITY
// ============================================================

void useAbility() {

	cout << orangeText
		<< "===== ABILITIES ====="
		<< resetColor << endl;

	bool hasAbility = false;

	if (accessories[0] != "nothing atm" &&
		isRing(accessories[0]) &&
		!abilityUsed[0]) {

		hasAbility = true;

		cout << limeGreenText << "1: "
			<< resetColor << blueText
			<< accessories[0]
			<< resetColor << endl;
	}

	if (accessories[1] != "nothing atm" &&
		isRing(accessories[1]) &&
		!abilityUsed[1]) {

		hasAbility = true;

		cout << limeGreenText << "2: "
			<< resetColor << blueText
			<< accessories[1]
			<< resetColor << endl;
	}

	if (!hasAbility) {
		printMessage("You have no available ring abilities.");
		return;
	}

	printOption(3, "Go back");

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
		printMessage("Invalid ability choice.");
		return;
	}

	string ring = accessories[ringSlot];

	if (ring == "Ring of Vitality (+10 MAX Hp)") {

		maxHealth += 10;
		health += 10;

		cout << purpleText
			<< "Ring of Vitality activated!"
			<< resetColor << endl;

		printMessage("Your MAX HP increased by 10.");
		printValue("HP", health, maxHealth);
	}
	else if (ring == "Ring of Strength (+3 to attack)") {

		cout << purpleText
			<< "Ring of Strength activated!"
			<< resetColor << endl;

		printMessage("You already receive +3 damage from this ring.");
	}
	else if (ring == "ring of lightning (free 1d6 attack)") {

		int damage = rand() % 6 + 1;

		cout << purpleText
			<< "Lightning strikes the enemy!"
			<< resetColor << endl;

		cout << greenText << "You deal "
			<< redText << damage
			<< greenText << " lightning damage!"
			<< resetColor << endl;

		enemyHealth -= damage;

		if (enemyHealth < 0) {
			enemyHealth = 0;
		}

		printValue("Enemy HP", enemyHealth, enemyMaxHealth);
	}

	abilityUsed[ringSlot] = true;

	printMessage(
		"This ability cannot be used again until the next combat."
	);
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
		else {
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
		else {
			enemyType = "twistedHuman";
		}
	}

	cout << greenText << "You are fighting a "
		<< blueText << enemyType
		<< greenText << "!"
		<< resetColor << endl;

	combat(enemyType, isBoss);
}