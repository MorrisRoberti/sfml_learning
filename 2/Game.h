#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Ball.h"

class Game
{
private:
    // Attributes
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Font font;
    sf::Text guiText;
    sf::Text title;
    bool endGame;
    int points;

    Player player;

    std::vector<Ball> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;

    // Methods
    void initWindow();
    void initVariables();
    void initFonts();
    void initText();

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
    void updateCollision();
    void updateGui();
    void update();

    // Render
    void renderGui(sf::RenderWindow *target);
    void render();
};