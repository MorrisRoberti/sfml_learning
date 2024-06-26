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

    float currentAngle;

    sf::Vector2i origin;

    // init
    void initVariables();

public:
    sf::VertexArray line;
    // constructor
    VectorShape();
    VectorShape(const VectorShape &vec);
    VectorShape(float x, float y, const sf::Vector2i origin);

    // getter
    const float getX() const;
    const float getY() const;
    const float getMagnitude() const;

    const sf::Color getColor() const;
    const sf::Vector2i getOrigin() const;

    // setter
    void setX(float newX);
    void setY(float newY);
    void setColor(sf::Color color);

    // operators
    float operator*(const VectorShape &vec2) const;
    VectorShape &operator/(const sf::Vector2f &vec2) const;

    // utilities
    float getNorm() const;
    VectorShape normalize(float x, float y, const float &radius);
    void rotate(float angle);

    // update
    void update();

    // render
    void render(sf::RenderWindow *target);
};