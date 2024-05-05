#include "Bullet.h"

// constructors / destructors
Bullet::Bullet(sf::Texture &texture, float dirX, float dirY, float movementSpeed)
{

    this->initSprite(texture);

    this->movementSpeed = movementSpeed;

    // setting the starting point of bullet
    this->direction.x = dirX;
    this->direction.y = dirY;
}

Bullet::Bullet() {}

Bullet::~Bullet()
{
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

void Bullet::render(sf::RenderTarget *target)
{
    target.draw(this->sprite);
}
