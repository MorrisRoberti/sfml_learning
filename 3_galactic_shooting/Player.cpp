#include "Player.h"

// constructors / destructors
Player::Player()
{
    this->movementSpeed = 8.f;

    this->initTextures();
    this->initSprites();
}

Player::~Player() {}

// methods
void Player::initTextures()
{
    if (!this->texture.loadFromFile("assets/spaceship.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURES: Spaceship texture not loaded correctly" << std::endl;
}

void Player::initSprites()
{
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(sf::Vector2f(0, 0));
    this->sprite.setScale(0.3f, 0.3f);
}

void Player::move(const float dirX, const float dirY)
{

    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// UPDATE && RENDER
void Player::update() {}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}