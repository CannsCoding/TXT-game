#include <cstdlib>
#include <ctime>
#include "globals.h"
#include "game.h"
#include "player.h"

int main() {
    srand(time(NULL));

    givePlayerName();
    calculateFirstLvl(easterEggStats);
    chooseWeapon();
    playerStats();
    startGame();

    return 0;
}