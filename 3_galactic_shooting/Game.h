#pragma once

#include <iostream>

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game
{
private:
    // attributes
    sf::VideoMode videomode;
    sf::RenderWindow *window;
    sf::Event event;
    bool endGame;

    // initializers
    void initVariables();
    void initWindow();
    void initTextures();

    // private methods
    void pollEvents();

public:
    // constructors / destructors
    Game();
    ~Game();

    // methods
    void run();

    // update
    void update();

    // render
    void render(sf::RenderWindow *target);
};