#include "Player.h"

// Constructors / Destructors
Player::Player(float x, float y)
{
    this->playerSprite.setPosition(x, y);
    this->initVariables();
    this->initTextures();
    this->initSprites();
}

Player::~Player() {}

// Methods

void Player::initVariables()
{
    this->movementSpeed = 7.f;
    this->hpMax = 5;
    this->hp = hpMax;
}

void Player::initTextures()
{
    if (!this->playerTexture.loadFromFile("assets/player.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURES: Player texture not loaded correctly" << std::endl;

    if (!this->fullHeartTexture.loadFromFile("assets/full_heart.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURES: Full Heart texture not loaded correctly" << std::endl;

    if (!this->halfHeartTexture.loadFromFile("assets/half_heart.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURES: Half Heart texture not loaded correctly" << std::endl;
}

void Player::initSprites()
{
    this->playerSprite.setTexture(this->playerTexture);
    this->playerSprite.setScale(0.35f, 0.35f);

    this->heartSprite.setTexture(this->fullHeartTexture);
    this->heartSprite.setScale(0.5f, 0.5f);

    for (int i = 0; i < 5; i++)
        this->heartSprites.push_back(this->heartSprite);
}

void Player::takeDamage(const float damage)
{
    if (this->hp > 0)
        this->hp -= damage;

    if (this->hp < damage)
        this->hp = 0;
}

void Player::gainHealth(const float health)
{

    if (this->hp + health <= this->hpMax)
        this->hp += health;
    else
        this->hp = this->hpMax;
}

const sf::Sprite &Player::getSprite() const
{
    return this->playerSprite;
}

const float &Player::getHp() const
{
    return this->hp;
}

const float &Player::getMaxHp() const
{
    return this->hpMax;
}
// UPDATE && RENDER
void Player::updateInput()
{
    // Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->playerSprite.move(-this->movementSpeed, 0.f);
    } // Right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->playerSprite.move(this->movementSpeed, 0.f);
    } // Up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->playerSprite.move(0.f, -this->movementSpeed);
    } // Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->playerSprite.move(0.f, this->movementSpeed);
    }
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget *target)
{
    // Left
    if (this->playerSprite.getGlobalBounds().left <= 0.f)
        this->playerSprite.setPosition(0.f, this->playerSprite.getGlobalBounds().top);

    // Right
    if (this->playerSprite.getGlobalBounds().left + this->playerSprite.getGlobalBounds().width >= target->getSize().x)
        this->playerSprite.setPosition(target->getSize().x - this->playerSprite.getGlobalBounds().width, this->playerSprite.getGlobalBounds().top);

    // Top
    if (this->playerSprite.getGlobalBounds().top <= 0.f)
        this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, 0.f);

    // Bottom
    if (this->playerSprite.getGlobalBounds().top + this->playerSprite.getGlobalBounds().height >= target->getSize().y)
        this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, target->getSize().y - this->playerSprite.getGlobalBounds().height);
}

void Player::updateHealthTextures()
{

    // TODO: I want to update the texture of the hearts by the hp value
}

void Player::update(const sf::RenderTarget *target)
{

    // Keyboard input
    this->updateInput();

    // Window bounds collision
    this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(this->fullHeartSprite);
    target->draw(this->halfHeartSprite);
    target->draw(this->playerSprite);
}