#include "Ball.h"

// Constructors / Destructors
Ball::Ball(const sf::RenderWindow *window, int type) : type(type)
{
    std::cout << "Type: " << this->type;
    this->initTextures();
    this->initSprites(window);
}

Ball::~Ball() {}

// Methods
void Ball::initVariables() {}

void Ball::initTextures()
{
    if (!this->goodMushroomTexture.loadFromFile("assets/mushroom.png"))
        std::cout << "ERROR::BALL::INITTEXTURES: Mushroom texture not loaded correctly" << std::endl;

    if (!this->badMushroomTexture.loadFromFile("assets/bad_mushroom.png"))
        std::cout << "ERROR::BALL::INITTEXTURES: Mushroom texture not loaded correctly" << std::endl;

    if (!this->healingPotionTexture.loadFromFile("assets/healing_potion.png"))
        std::cout << "ERROR::BALL::INITTEXTURES: Healing Potion texture not loaded correctly" << std::endl;
}

void Ball::initSprites(const sf::RenderWindow *window)
{
    sf::Texture itemTexture;
    switch (this->type)
    {
    case DEFAULT:
        itemTexture = this->goodMushroomTexture;
        break;
    case DAMAGING:
        itemTexture = this->badMushroomTexture;
        break;
    case HEALING:
        itemTexture = this->healingPotionTexture;
        break;
    }

    this->itemSprite.setTexture(this->goodMushroomTexture);
    // this->itemSprite.setScale(10.f, 1.f);
    this->itemSprite.setScale(0.3f, 0.3f);
    this->itemSprite.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(window->getSize().x - this->itemSprite.getGlobalBounds().width)),
                                              static_cast<float>(rand() % static_cast<int>(window->getSize().y - this->itemSprite.getGlobalBounds().height))));
}

const sf::Sprite &Ball::getSprite() const
{
    return this->itemSprite;
}

const int &Ball::getType() const
{
    return this->type;
}

// UPDATE && RENDER
void Ball::update() {}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->itemSprite);
}