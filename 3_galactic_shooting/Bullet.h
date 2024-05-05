#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet
{
private:
    // attributes
    sf::Sprite sprite;
    float movementSpeed;
    sf::Vector2f direction;

    // initializers
    void initSprite(sf::Texture &texture);

public:
    // constructors / destructors
    Bullet(sf::Texture &texture, float dirX, float dirY, float movementSpeed);
    ~Bullet();

    // update
    void update();

    // render
    void render(sf::RenderTarget *target);
};