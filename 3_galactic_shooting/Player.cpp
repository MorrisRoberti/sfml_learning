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
    this->sprite.setRotation(0);
    this->sprite.setScale(0.3f, 0.3f);
    this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2, this->sprite.getLocalBounds().height / 2);
}

void Player::move(const float dirX, const float dirY)
{

    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// TO FIX
void Player::rotate(const sf::Vector2i &mousePos)
{
    // std::cout << mousePos.x << " - " << mousePos.y << std::endl;
    // angle between (0, 1) and mousePos = arcsin(1 / norm(mousePos))
    sf::Vector2f dirVec = sf::Vector2f(mousePos.x - this->sprite.getOrigin().x, mousePos.y - this->sprite.getOrigin().y);
    float normalized = std::sqrt(std::pow(dirVec.x, 2) + std::pow(dirVec.y, 2));
    float newAngle = std::acos(1 / normalized);

    // std::cout << std::cos(newAngle) << std::endl;

    // if (std::sin(this->sprite.getRotation()) > std::sin(newAngle) && std::cos(this->sprite.getRotation()) > std::cos(newAngle))
    //     this->sprite.rotate(-newAngle * 0.9f);
    // else
    //     this->sprite.rotate(newAngle * 0.9f);

    this->sprite.setRotation(std::atan2(mousePos.y - this->sprite.getPosition().y, mousePos.x - this->sprite.getPosition().x) * 180 / (std::atan(1) * 4) * 1.5f);
}

sf::Vector2f Player::getPosition() const
{
    return this->sprite.getPosition();
}

sf::Vector2f Player::getOrigin() const
{
    return this->sprite.getOrigin();
}

sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

sf::Vector2f Player::getScale() const
{
    return this->sprite.getScale();
}

// UPDATE && RENDER
void Player::update()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}