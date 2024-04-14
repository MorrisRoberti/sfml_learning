#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
    // Attributes
    sf::RectangleShape shape;
    float movementSpeed;

    // Methods
    void initVariables();
    void initShape();

public:
    // Constructors / Destructor
    Player(float x = 0.f, float y = 0.f);
    ~Player();

    // Methods

    // Update
    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget *target);
    void update(const sf::RenderTarget *target);

    // Render
    void render(sf::RenderTarget *targer);
};