#pragma once

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
    sf::CircleShape shape;
    int type;

    // Methods
    void initVariables();
    void initShape(const sf::RenderWindow *window);

public:
    // Constructor / Destructors
    Ball(const sf::RenderWindow *window, int type);
    ~Ball();

    // Accessor
    const sf::CircleShape &getShape() const;
    const int &getType() const;

    // Methods

    // Update
    void update();

    // Render
    void render(sf::RenderTarget *target);
};