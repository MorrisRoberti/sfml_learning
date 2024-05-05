#pragma once

#include <iostream>

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

    // update
    void update();

    // render
    void render(sf::RenderTarget &target);
};