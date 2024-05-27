#include "VectorShape.h"

// constructors
VectorShape::VectorShape()
{
    this->x = 0;
    this->y = 0;
    this->origin = sf::Vector2i(0, 0);
    this->color = sf::Color::White;
    this->initVariables();
}

VectorShape::VectorShape(const VectorShape &vec2)
{
    this->x = -vec2.x;
    this->y = -vec2.y;
    this->origin = vec2.getOrigin();
    this->color = vec2.getColor();
    this->initVariables();
}

VectorShape::VectorShape(float x, float y, const sf::Vector2i origin)
{
    this->x = -x;
    this->y = -y;
    this->origin = origin;
    this->color = sf::Color::White;
    this->initVariables();
}

// init
void VectorShape::initVariables()
{
    this->line = sf::VertexArray(sf::Lines, 2);
    this->currentAngle = 0;

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

    return static_cast<float>(std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2)));
}

VectorShape VectorShape::normalize(float x, float y, const float &radius)
{
    sf::Vector2f normalizedVector(x / this->getNorm(), y / this->getNorm());
    return VectorShape(normalizedVector.x * radius, normalizedVector.y * radius, this->origin);
}

void VectorShape::rotate(float angle)
{

    this->currentAngle += angle;

    this->line[1].position.x = -((this->x * std::cos(this->currentAngle)) - (this->y * std::sin(this->currentAngle)));
    this->line[1].position.y = -((this->x * std::sin(this->currentAngle)) + (this->y * std::cos(this->currentAngle)));

    this->x = this->line[1].position.x;
    this->y = this->line[1].position.y;

    // this->normalize(200);
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
    this->line[1].position.x = this->x;
}

void VectorShape::setY(float newY)
{
    this->y = newY;
    this->line[1].position.y = this->y;
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
    this->line[0].color = this->color;
    this->line[1].color = this->color;
}

void VectorShape::render(sf::RenderWindow *target)
{
    target->draw(this->line);
}