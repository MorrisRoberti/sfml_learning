#include <iostream>
#include "Game.h"

int main()
{

    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game engine
    Game game;

    // Game loop
    while (game.windowIsOpen())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}