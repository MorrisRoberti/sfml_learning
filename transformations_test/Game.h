#pragma once

#include "Backgorund.h"
#include "TileMap.h"
#include "VectorShape.h"

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
    VectorShape vec;
    VectorShape vec2;

    TileMap *tileMap;
    sf::Texture *tileSet;

    sf::CircleShape mousePointer;

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
