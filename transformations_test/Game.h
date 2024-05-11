#pragma once

#include "Backgorund.h"

#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>

class Game
{
private:
    // attributes
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    Background *background;

    // init
    void initWindow();
    void initVariables();
    void pollEvents();

public:
    // constructor / destructor
    Game();
    ~Game();

    // update
    void update();

    // render
    void render(sf::RenderWindow *target);

    void run();
};
