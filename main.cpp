#include <iostream>
#include "Game.h"

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    Game game;

    while (game.isWindowOpen()) {
        game.update();
        game.render();
    }

    return 0;
}
