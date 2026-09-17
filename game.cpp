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

	cout << greenText;
	cout << "you are starting your journey but before you head off you are at a rest site what would you like to do?" << endl;
	cout << resetColor;

	cout << limeGreenText;
	cout << "1: ";
	cout << resetColor;

	cout << purpleText;
	cout << "head off to my adventure." << endl;
	cout << resetColor;
	cin >> wouldDo;

	if (wouldDo == 1) {
		startJourney();
	}
	else {
		cout << redText;
		cout << "Invalid choice." << endl;
		cout << resetColor;

		startGame();
	}
}

// =========================
// START JOURNEY
// =========================

void startJourney() {

	cout << endl;
	cout << blueText;
	cout << '\n';
	cout << "========================================" << endl;
	cout << resetColor;

	cout << purpleText;
	cout << "        YOU ENTER THE WILDERNESS" << endl;
	cout << resetColor;

	cout << blueText;
	cout << "========================================" << endl;
	cout << '\n';
	cout << resetColor;

	cout << greenText;
	cout << "You start your journey into the wilderness." << endl;
	cout << "There is no point in ever doing this when you enter this forest." << endl;
	cout << "Time and space distorts it is";
	cout << resetColor;


	cout << redText;
	cout << " IMPOSSIBLE ";
	cout << resetColor;

	cout << greenText;
	cout << "to get out." << endl;
	cout << endl;

	cout << "Though through many years your civilization found a way" << endl;
	cout << "to bring people back from the forest." << endl;
	cout << endl;

	cout << "There is a caveat: the only way they can bring people back" << endl;
	cout << "is if they die. They will lose";
	cout << resetColor;

	cout << redText;
	cout << " EVERYTHING ";
	cout << resetColor;

	cout << greenText;
	cout << "but gain experience." << endl;
	cout << endl;

	cout << "The only reason you are doing this is just for the";
	cout << resetColor;

	cout << redText;
	cout << " love of the game..." << endl;
	cout << resetColor;
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
	cout << greenText;
	cout << "you encounterd a";
	cout << resetColor;

	cout << orangeText;
	cout << " basic enemy!" << endl;
	cout << resetColor;

	health = health + maxHealth * .30;
	if (health > maxHealth) {
		health = maxHealth;
	}
	enemyChoice(false);
}

// =========================
// BOSS LEVEL
// =========================

void bossLevel() {
	cout << greenText;
	cout << "you encounterd a";
	cout << resetColor;

	cout << redText;
	cout << " boss enemy!" << endl;
	cout << resetColor;

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
	int healthPercent = maxHealth * 0.30;
	int wouldDo;
	playerStats();
	cout << greenText;
	cout << "you have found a safe place in the woods where a wandering merchant seems to be, while you are here what would you like to do?" << endl;
	cout << resetColor;

	cout << limeGreenText;
	cout << "1: ";
	cout << resetColor;
	cout << orangeText;
	cout << "rest " << limeGreenText;
	cout << "(heal 30% of max hp " << yellowText;
	cout << healthPercent << limeGreenText << ")" << greenText;
	cout << " and continue on my current journey" << endl;
	cout << resetColor;

	cout << limeGreenText;
	cout << "2: ";
	cout << resetColor;
	cout << greenText;
	cout << blueText << "Talk" << greenText
		<< " to the " << purpleText << "wandering merchant" << greenText
		<< ". (can only do once per rest site)" << endl;
	cout << resetColor;

	cout << limeGreenText;
	cout << "3: ";
	cout << resetColor;
	cout << greenText;
	cout << brownText << "dig" << greenText
		<< " for " << brightYellowText << "loot" << greenText
		<< " (can only do once per rest site)." << endl;
	cout << resetColor;
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