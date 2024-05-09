#include "Bullet.h"

// constructors / destructors
Bullet::Bullet(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float movementSpeed)
{

    this->sprite.setTexture(*texture);

    this->sprite.setPosition(posX, posY);
    this->sprite.setScale(0.2f, 0.2f);

    this->movementSpeed = movementSpeed;

    // setting the starting point of bullet
    this->direction.x = dirX;
    this->direction.y = dirY;
}

Bullet::Bullet() {}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

// initializers
void Bullet::initSprite(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

// UPDATE && RENDER
void Bullet::update()
{

    // movement
    this->sprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
