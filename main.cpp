#include <cstdlib>
#include <ctime>
#include "globals.h"
#include "game.h"
#include "player.h"

int main() {
    srand(time(NULL));

    int playerLVL = rand() % 10 + 1;
    levelOfPlayer = playerLVL;

    calculateHealth(playerLVL, NULL, NULL);
    chooseWeapon();
    playerStats();
    startGame();
}