#pragma once

#include <vector>

#include <ctime>

#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
    Class that acts as the game engine.
    Wrapper class.
*/
class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow *window;
    sf::Event event;
    sf::VideoMode videoMode;
    sf::Texture textureBackground;
    sf::Texture textureBackgroundEndGame;
    sf::Sprite spriteBackground;

    // Text
    sf::Font font;
    sf::Text title;
    sf::Text text;

    // Mouse Positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Game Logic
    bool paused;
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    // Game Objects
    sf::Texture enemyTexture;
    std::vector<sf::Sprite> enemies;
    sf::Sprite enemy;

    // Private Methods
    void initVariables();
    void initWindow();
    void initBackground();
    void initEmemies();
    void initFonts();
    void initTexts();

public:
    // Constructor / Destructors
    Game();
    virtual ~Game();

    // Accessors
    const bool windowIsOpen() const;
    const bool getEndGame() const;

    // Methods
    void spawnEnemy();
    void pollEvents();

    void updateEnemies();
    void updateBackground();
    void updateMousePositions();
    void updateText();
    void update();

    void renderEnemies();
    void renderBackground();
    void renderText(sf::RenderTarget &target);
    void render();
    // void moveEnemy();
};