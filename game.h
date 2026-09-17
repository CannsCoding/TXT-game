#pragma once

#include <string>

using namespace std;

void startGame();
void startJourney();
void lvlGenerator(bool previousWasRest);
void normalLevel();
void bossLevel();
void restLevel(bool dontAllowDigging, bool dontAllowShop);
