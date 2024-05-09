#pragma once
#include "Player.h"
#include "Bullet.h"

#include <map>
#include <iostream>
#include <cmath>

class Game
{
private:
    // attributes
    sf::VideoMode videomode;
    sf::RenderWindow *window;
    sf::Event event;
    bool endGame;

    // resources
    std::map<std::string, sf::Texture *> textures;

    // scene objects
    Player *player;
    std::vector<Bullet *> bullets;

    float normalize(int x_, int y_);

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
    void updateBullets();

    // render
    void render(sf::RenderWindow *target);
};