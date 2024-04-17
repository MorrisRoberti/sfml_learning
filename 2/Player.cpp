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

    if (!this->emptyHeartTexture.loadFromFile("assets/empty_heart.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURES: Empty Heart texture not loaded correctly" << std::endl;
}

void Player::initSprites()
{
    this->playerSprite.setTexture(this->playerTexture);
    this->playerSprite.setScale(0.35f, 0.35f);

    // initializing every heart with the full texture
    this->heartSprite.setTexture(this->fullHeartTexture);
    this->heartSprite.setScale(0.2f, 0.2f);

    for (int i = 0; i < 5; i++)
    {
        this->heartSprite.setPosition(i * 50.f, 30.f);
        this->heartSprites.push_back(this->heartSprite);
    }
}

void Player::takeDamage(const float damage)
{

    if (this->hp > 0)
        this->hp -= damage;

    if (this->hp < damage)
        this->hp = 0;

    this->updateHealthTextures();
}

void Player::gainHealth(const float health)
{

    if (this->hp + health <= this->hpMax)
        this->hp += health;
    else
        this->hp = this->hpMax;
    this->updateHealthTextures();
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

    // setting the right texture for health based on hp calculations
    int numberOfFullHearts = this->hp;
    int numberOfEmptyHearts;
    int numberOfHalfHearts = 0;

    if (std::floor(this->hp) == this->hp)
    {
        // no half hearts
        numberOfEmptyHearts = this->hpMax - this->hp;
    }
    else
    {
        // half heart
        numberOfHalfHearts = 1;
        numberOfFullHearts = std::floor(this->hp);
        numberOfEmptyHearts = std::floor(this->hpMax - this->hp);
    }

    int counter = 0;
    for (; counter < numberOfFullHearts; counter++)
    {
        this->heartSprites[counter].setTexture(this->fullHeartTexture);
    }

    if (numberOfHalfHearts == 1)
    {
        this->heartSprites[counter].setTexture(this->halfHeartTexture);
        counter++;
    }

    for (; counter < numberOfEmptyHearts + numberOfFullHearts; counter++)
        this->heartSprites[counter].setTexture(this->emptyHeartTexture);
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
    for (sf::Sprite s : this->heartSprites)
        target->draw(s);
    target->draw(this->playerSprite);
}