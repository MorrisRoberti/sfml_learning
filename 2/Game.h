#pragma once

#include <iostream>
#include <ctime>
#include <vector>

#include "Player.h"
#include "Ball.h"

class Game
{
private:
    // Attributes
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;
    bool endGame;

    Player player;

    std::vector<Ball> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;

    // Methods
    void initWindow();
    void initVariables();

public:
    // Constructors / Destructor
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Metods
    const bool isWindowOpen() const;
    void closeWindow();
    void pollEvents();
    void spawnBalls();

    // Update
    void update();

    // Render
    void render();
};