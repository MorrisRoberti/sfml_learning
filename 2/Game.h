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

    sf::Texture mushroomTexture;
    sf::Sprite pointsSprite;
    sf::Text pointsText;
    int points;

    Player player;

    sf::Texture badMushroomTexture;
    sf::Texture healingPotionTexture;
    sf::Texture ballTexture;

    std::vector<Ball> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;

    // Methods
    void initWindow();
    void initVariables();
    void initFonts();
    void initText();
    void initTextures();
    void initSprites();

public:
    // Constructors / Destructor
    Game();
    ~Game();

    // Accessors
    const bool &getEndGame() const;

    // Modifiers
    void setTextureBasedOnType(Ball &ball, const int type);

    // Metods
    const bool isWindowOpen() const;
    void closeWindow();
    void pollEvents();
    void spawnBalls();
    const int randomizeBallType();

    // Update
    void updateCollision();
    void updateGui();
    void update();

    // Render
    void renderGui(sf::RenderWindow *target);
    void render();
};