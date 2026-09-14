#include "game.h"
#include "combat.h"
#include "items.h"
#include "shop.h"
#include "player.h"
#include "globals.h"
#include <iostream>

using namespace std;

// =========================
// START GAME
// =========================

void startGame() {
	int wouldDo;

	cout << "you are starting your journey but before you head off you are at a rest site what would you like to do?" << endl;
	cout << "1: head off to my adventure." << endl;
	cin >> wouldDo;

	if (wouldDo == 1) {
		startJourney();
	}
	else {
		cout << "Invalid choice." << endl;

		startGame();
	}
}

// =========================
// START JOURNEY
// =========================

void startJourney() {

	cout << endl;
	cout << "========================================" << endl;
	cout << "        YOU ENTER THE WILDERNESS" << endl;
	cout << "========================================" << endl;

	cout << "You start your journey into the wilderness." << endl;
	cout << "There is no point in ever doing this when you enter this forest." << endl;
	cout << "Time and space distorts it is IMPOSSIBLE to get out." << endl;
	cout << endl;

	cout << "Though through many years your civilization found a way" << endl;
	cout << "to bring people back from the forest." << endl;
	cout << endl;

	cout << "There is a caveat: the only way they can bring people back" << endl;
	cout << "is if they die. They will lose EVERYTHING but gain experience." << endl;
	cout << endl;

	cout << "The only reason you are doing this is just for the love of the game." << endl;
	cout << endl;

	lvlGenerator(false);
}

// =========================
// GENERATE LEVEL
// =========================

void lvlGenerator(bool previousWasRest) {

	int levelType = rand() % 6 + 1;

	// Normal level
	if (levelType == 1 || levelType == 2) {
		normalLevel();
	}

	// Rest level
	else if (levelType > 2 && levelType < 6) {


		if (previousWasRest) {
			lvlGenerator(true);
			return;
		}

		restLevel(false, false);
	}

	// Boss level
	else if (levelType == 6) {
		bossLevel();
	}
}

// =========================
// NORMAL LEVEL
// =========================

void normalLevel() {
	cout << "you encounterd a basic enemy!" << endl;
	health += maxHealth * .30;
	if (health > maxHealth) {
		health = maxHealth;
	}
	enemyChoice(false);
}

// =========================
// BOSS LEVEL
// =========================

void bossLevel() {
	cout << "you encounterd a boss enemy!" << endl;
	health += maxHealth * .50;
	if (health > maxHealth) {
		health = maxHealth;
	}
	enemyChoice(true);
}

// =========================
// REST LEVEL
// =========================

void restLevel(bool dontAllowDigging, bool dontAllowShop) {
	int healthPercent = maxHealth * 0.15;
	round(healthPercent);
	int wouldDo;
	cout << "you have found a safe place in the woods where a wandering merchant seems to be, while you are here what would you like to do?" << endl;
	cout << "1: rest (heal 30% of max hp " << healthPercent << ") and continue on my current journey" << endl;
	cout << "2: Talk to the wandering merchant. (can only do once per rest site)" << endl;
	cout << "3: dig for loot (can only do once per rest site)." << endl;
	cin >> wouldDo;

	if (wouldDo == 1) {
		cout << "you heal " << healthPercent << " HP and continue on with your journey.";
		health += maxHealth * .30;
		if (health > maxHealth) {
			health = maxHealth;
		}
		lvlGenerator(true);
	}
	else if (wouldDo == 2) {
		cout << "you head over to chat with the wandering merchant" << endl;
		shop();
	}
	else if (wouldDo == 3) {
		digging();
	}
}