#include "Ball.h"

// Constructors / Destructors
Ball::Ball(const sf::RenderWindow *window, int type) : type(type)
{
    this->initShape(window);
}

Ball::~Ball() {}

// Methods
void Ball::initVariables() {}

void Ball::initShape(const sf::RenderWindow *window)
{
    sf::Color color;
    switch (this->type)
    {
    case DEFAULT:
        color = sf::Color::White;
        break;
    case DAMAGING:
        color = sf::Color::Red;
        break;
    case HEALING:
        color = sf::Color::Green;
        break;
    }

    this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
    this->shape.setFillColor(color);
    this->shape.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(window->getSize().x - this->shape.getGlobalBounds().width)),
                                         static_cast<float>(rand() % static_cast<int>(window->getSize().y - this->shape.getGlobalBounds().height))));
}

const sf::CircleShape &Ball::getShape() const
{
    return this->shape;
}

const int &Ball::getType() const
{
    return this->type;
}

// UPDATE && RENDER
void Ball::update() {}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}