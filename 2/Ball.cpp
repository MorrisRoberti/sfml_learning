#include "Ball.h"

// Constructors / Destructors
Ball::Ball(const sf::RenderWindow *window, int type) : type(type)
{
    this->initSprites(window);
}

Ball::~Ball() {}

// Methods
void Ball::initVariables() {}

void Ball::initSprites(const sf::RenderWindow *window)
{

    this->itemSprite.setScale(0.2f, 0.2f);
    this->itemSprite.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(window->getSize().x - this->itemSprite.getLocalBounds().width)),
                                              static_cast<float>(rand() % static_cast<int>(window->getSize().y - this->itemSprite.getLocalBounds().height))));
}

const sf::Sprite &Ball::getSprite() const
{
    return this->itemSprite;
}

const int &Ball::getType() const
{
    return this->type;
}

void Ball::setSpriteTexture(sf::Texture &texture)
{
    this->itemSprite.setTexture(texture);
}

// UPDATE && RENDER
void Ball::update() {}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->itemSprite);
}