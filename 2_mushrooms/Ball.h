#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum BallTypes
{
    DEFAULT = 0,
    DAMAGING,
    HEALING,
    NROFTYPES
};

class Ball
{
private:
    // Attributes
    sf::Sprite itemSprite;
    int type;

    // Methods
    void initVariables();
    void initSprites(const sf::RenderWindow *window);

public:
    // Constructor / Destructors
    Ball(const sf::RenderWindow *window, int type);
    ~Ball();

    // Accessor
    const sf::Sprite &getSprite() const;
    const int &getType() const;

    // Methods
    void setSpriteTexture(sf::Texture &texture);

    // Update
    void update();

    // Render
    void render(sf::RenderTarget *target);
};