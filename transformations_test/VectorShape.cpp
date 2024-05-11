#include "VectorShape.h"

// constructors
VectorShape::VectorShape()
{
    this->x = 0;
    this->y = 0;
    this->origin = sf::Vector2i(0, 0);
    this->color = sf::Color::White;
    this->magnitude = 0;
    this->initVariables();
}

VectorShape::VectorShape(float x, float y, const sf::Vector2i origin)
{
    this->x = x;
    this->y = y;
    this->origin = origin;
    this->color = sf::Color::White;
    this->magnitude = 10;
    this->initVariables();
}

VectorShape::VectorShape(float x, float y, const sf::Vector2i origin, float magnitude)
{
    this->x = x;
    this->y = y;
    this->origin = origin;
    this->color = sf::Color::White;
    this->magnitude = magnitude;
    this->initVariables();
}

// init
void VectorShape::initVariables()
{
    this->line = sf::VertexArray(sf::Lines, 2);
    this->line.append(sf::Vertex(sf::Vector2f(this->origin.x, this->origin.y)));

    this->line[0].position = sf::Vector2f(this->origin.x, this->origin.y);
    this->line[0].color = this->color;

    this->line[1].position = sf::Vector2f(this->origin.x + this->x, this->origin.y + this->y);
    this->line[1].color = this->color;
}

// getters
const float VectorShape::getX() const
{
    return this->x;
}

const float VectorShape::getY() const
{
    return this->y;
}

const float VectorShape::getMagnitude() const
{
    return this->magnitude;
}

const sf::Color VectorShape::getColor() const
{
    return this->color;
}

// setter
void VectorShape::setX(float newX)
{
    this->x = newX;
}

void VectorShape::setY(float newY)
{
    this->y = newY;
}

void VectorShape::setMagnitude(float magnitude)
{
    this->magnitude = magnitude;
}

void VectorShape::setColor(sf::Color color)
{
    this->color = color;
}

// update
void VectorShape::update()
{
    this->line[0].position = sf::Vector2f(this->origin.x, this->origin.y);
    this->line[0].color = this->color;
}

void VectorShape::render(sf::RenderWindow *target)
{
    target->draw(this->line);
}