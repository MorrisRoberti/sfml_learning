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
    float attackCooldown;
    float attackCooldownMax;

    // initializers
    void initVariables();
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
    const bool canAttack();

    // accessors
    sf::Vector2f getPosition() const;
    sf::Vector2f getOrigin() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getScale() const;
    float getRotation() const;

    // update
    void update();
    void updateAttack();

    // render
    void render(sf::RenderTarget &target);
};