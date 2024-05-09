#pragma once

#include <iostream>
#include <cmath>

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
    // attributes
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;

    // initializers
    void initTextures();
    void initSprites();

    // private methods

public:
    // constructors / destructors
    Player();
    ~Player();

    // methods
    void move(const float dirX, const float dirY);
    void rotate(const sf::Vector2i &mousePos);

    // accessors
    sf::Vector2f getPosition() const;
    sf::Vector2f getOrigin() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getScale() const;

    // update
    void update();

    // render
    void render(sf::RenderTarget &target);
};