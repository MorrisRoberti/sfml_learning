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

VectorShape::VectorShape(const VectorShape &vec2)
{
    this->x = vec2.x;
    this->y = vec2.y;
    this->origin = vec2.getOrigin();
    this->color = vec2.getColor();
    this->magnitude = vec2.getMagnitude();
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

    this->line[0].position = sf::Vector2f(this->origin.x, this->origin.y);
    this->line[0].color = this->color;

    this->line[1].position = sf::Vector2f(this->origin.x + this->x, this->origin.y + this->y);
    this->line[1].color = this->color;
}

// operators
float VectorShape::operator*(const VectorShape &vec2) const
{
    return this->line[1].position.x * vec2.getX() + this->line[1].position.y * vec2.getY();
}

VectorShape &VectorShape::operator/(const sf::Vector2f &vec2) const
{
    VectorShape *newVector = new VectorShape(*this);
    newVector->setX(this->line[1].position.x / (this->origin.x + vec2.x));
    newVector->setY(this->line[1].position.y / (this->origin.y + vec2.y));
    return *newVector;
}
// utilities
float VectorShape::getNorm() const
{

    return static_cast<float>(std::sqrt(std::pow(this->line[1].position.x, 2) + std::pow(this->line[1].position.y, 2)));
}

VectorShape &VectorShape::normalize()
{
    sf::Vector2f normalizedVector(this->x / this->getNorm(), this->y / this->getNorm());
    std::cout << this->x << " - " << this->y << " // " << normalizedVector.x << " - " << normalizedVector.y << std::endl;
    VectorShape *returnVector = new VectorShape(normalizedVector.x * this->origin.x, normalizedVector.y * this->origin.y, this->origin, this->magnitude);

    returnVector->setColor(sf::Color::Blue);

    return *returnVector;
}

// getters
const float VectorShape::getX() const
{
    return this->line[1].position.x;
}

const float VectorShape::getY() const
{
    return this->line[1].position.y;
}

const float VectorShape::getMagnitude() const
{
    return this->magnitude;
}

const sf::Color VectorShape::getColor() const
{
    return this->color;
}

const sf::Vector2i VectorShape::getOrigin() const
{
    return this->origin;
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
    this->line[0].color = this->color;
    this->line[1].color = this->color;
}

// update
void VectorShape::update()
{
    this->line[1].position = sf::Vector2f(this->origin.x, this->origin.y);
    this->line[1].color = this->color;
}

void VectorShape::render(sf::RenderWindow *target)
{
    target->draw(this->line);
}