#include "Player.h"

// constructors / destructors
Player::Player()
{
    this->initVariables();
    this->initTextures();
    this->initSprites();
}

Player::~Player() {}

// methods
void Player::initVariables()
{
    this->movementSpeed = 8.f;
    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;
}

void Player::initTextures()
{
    if (!this->texture.loadFromFile("assets/spaceship.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURES: Spaceship texture not loaded correctly" << std::endl;
}

void Player::initSprites()
{
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(sf::Vector2f(400, 300));
    this->sprite.setScale(0.3f, 0.3f);
    this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2, this->sprite.getLocalBounds().height / 2);
}

void Player::move(const float dirX, const float dirY)
{

    // this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// TO FIX

// float normF(const sf::Vector2f vec)
// {
//     if (vec.x == 0 && vec.y == 0)
//         std::cout << "ATTENTION" << std::endl;
//     return static_cast<float>(std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)));
// }

// float normI(const sf::Vector2i vec)
// {
//     if (vec.x == 0 && vec.y == 0)
//         std::cout << "ATTENTION" << std::endl;
//     return static_cast<float>(std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)));
// }

// sf::Vector2f &normalizeVectorF(const sf::Vector2f vec)
// {
//     float newX = vec.x / normF(vec);
//     float newY = vec.y / normF(vec);
//     sf::Vector2f retV = new sf::Vector2f(newX, newY);
//     return retV;
// }

// sf::Vector2f &normalizeVectorI(const sf::Vector2i vec)
// {
//     float newX = vec.x / normI(vec);
//     float newY = vec.y / normI(vec);
//     sf::Vector2f retV = new sf::Vector2f(newX, newY);

//     return retV;
// }

float dotProduct(sf::Vector2f &v1, sf::Vector2f &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

void Player::rotate(const sf::Vector2i &mousePos)
{

    // normalize the two vectors
    sf::Vector2f oldVector(std::cos(this->sprite.getRotation()), std::sin(this->sprite.getRotation()));
    sf::Vector2f normalizedOld(oldVector.x / static_cast<float>(std::sqrt(std::pow(oldVector.x, 2) + std::pow(oldVector.y, 2))), oldVector.y / static_cast<float>(std::sqrt(std::pow(oldVector.x, 2) + std::pow(oldVector.y, 2))));
    sf::Vector2f normalizedNew(mousePos.x / static_cast<float>(std::sqrt(std::pow(mousePos.x, 2) + std::pow(mousePos.y, 2))), mousePos.y / static_cast<float>(std::sqrt(std::pow(mousePos.x, 2) + std::pow(mousePos.y, 2))));

    // find new angle
    float newAngle = std::acos((oldVector.x * mousePos.x + oldVector.y * mousePos.y) / (static_cast<float>(std::sqrt(std::pow(oldVector.x, 2) + std::pow(oldVector.y, 2))) * (static_cast<float>(std::sqrt(std::pow(mousePos.x, 2) + std::pow(mousePos.y, 2))))));
    std::cout << "jasfasfjkjfkl " << (oldVector.x * mousePos.x + oldVector.y * mousePos.y) / (static_cast<float>(std::sqrt(std::pow(oldVector.x, 2) + std::pow(oldVector.y, 2))) * (static_cast<float>(std::sqrt(std::pow(mousePos.x, 2) + std::pow(mousePos.y, 2))))) << std::endl;

    // std::cout << std::cos(newAngle) << std::endl;

    // if (std::sin(this->sprite.getRotation()) > std::sin(newAngle) && std::cos(this->sprite.getRotation()) > std::cos(newAngle))
    //     this->sprite.rotate(-newAngle * 0.9f);
    // else
    //     this->sprite.rotate(newAngle * 0.9f);

    this->sprite.setRotation(std::atan2(mousePos.y - this->sprite.getPosition().y, mousePos.x - this->sprite.getPosition().x) * 180 / (std::atan(1) * 4) * 1.5f);
    // this->sprite.rotate(newAngle);
}

const bool Player::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

sf::Vector2f Player::getPosition() const
{
    return this->sprite.getPosition();
}

sf::Vector2f Player::getOrigin() const
{
    return this->sprite.getOrigin();
}

float Player::getRotation() const
{
    return this->sprite.getRotation();
}

sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

sf::Vector2f Player::getScale() const
{
    return this->sprite.getScale();
}

void Player::updateAttack()
{

    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

// UPDATE && RENDER
void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}