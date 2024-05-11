#pragma once

#include <iostream>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class VectorShape
{
private:
    // attributes
    float x;
    float y;
    float magnitude;
    sf::Color color;

    sf::Vector2i origin;

    sf::VertexArray line;
    sf::VertexArray arrowHead;

    // init
    void initVariables();

public:
    // constructor
    VectorShape();
    VectorShape(float x, float y, const sf::Vector2i origin);
    VectorShape(float x, float y, const sf::Vector2i origin, float magnitude);

    // getter
    const float getX() const;
    const float getY() const;

    const float getMagnitude() const;
    const sf::Color getColor() const;

    // setter
    void setX(float newX);
    void setY(float newY);
    void setMagnitude(float magnitude);
    void setColor(sf::Color color);

    // operators

    // utilities

    // update
    void update();

    // render
    void render(sf::RenderWindow *target);
};