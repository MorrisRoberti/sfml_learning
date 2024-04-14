#include "Ball.h"

// Constructors / Destructors
Ball::Ball(const sf::RenderWindow *window)
{
    this->initShape(window);
}

Ball::~Ball() {}

// Methods
void Ball::initVariables() {}

void Ball::initShape(const sf::RenderWindow *window)
{
    this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
    sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
    this->shape.setFillColor(color);
    this->shape.setPosition(sf::Vector2f(static_cast<float>(rand() % window->getSize().x - this->shape.getGlobalBounds().width),
                                         static_cast<float>(rand() % window->getSize().y - this->shape.getGlobalBounds().height)));
}

// UPDATE && RENDER
void Ball::update() {}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}