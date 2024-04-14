#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Ball
{
private:
    // Attributes
    sf::CircleShape shape;

    // Methods
    void initVariables();
    void initShape(const sf::RenderWindow *window);

public:
    // Constructor / Destructors
    Ball(const sf::RenderWindow *window);
    ~Ball();

    // Update
    void update();

    // Render
    void render(sf::RenderTarget *target);
};