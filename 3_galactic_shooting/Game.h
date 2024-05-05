#pragma once
#include "Player.h"
#include "Bullet.h"

#include <map>
#include <iostream>

class Game
{
private:
    // attributes
    sf::VideoMode videomode;
    sf::RenderWindow *window;
    sf::Event event;
    bool endGame;

    // resources
    std::map<std::string, sf::Texture> textures;

    // scene objects
    Player *player;

    // initializers
    void initVariables();
    void initWindow();
    void initTextures();
    void initPlayer();

public:
    // constructors / destructors
    Game();
    ~Game();

    // methods
    void run();

    // update
    void update();
    void updatePollEvents();
    void updateInput();

    // render
    void render(sf::RenderWindow *target);
};