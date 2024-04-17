#include <iostream>
#include "Game.h"

int main()
{
    // initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Game instance
    Game game;

    // Game loop
    while (game.isWindowOpen())
    {
        // update
        game.update();

        // render
        game.render();
    }

    return 0;
}