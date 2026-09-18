#pragma once

#include <string>

using namespace std;

void calculateFirstLvl(bool egg);
void givePlayerName();
int calculateHealth(int playerLVL, int usedScroll, int wearingRing);
void playerStats();
void calculateDamage(int pLVL, int weapon);
void chooseWeapon();
void calculateMaxXP();
int xpGiven(int xpAmount);
int didLVLUp();