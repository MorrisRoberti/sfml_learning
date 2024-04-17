#include "Game.h"

// Private methods
void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Mushrooms", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxBalls = 10;
    this->points = 0;
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("assets/medieval_font.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS: Font not loaded correctly" << std::endl;
    }
}

void Game::initText()
{
    this->title.setFont(this->font);
    this->title.setString("Mushrooms");
    this->title.setFillColor(sf::Color::White);
    this->title.setCharacterSize(24);
    this->title.setPosition(0.f, 0.f);

    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(16);
    this->guiText.setPosition(0.f, 30.f);

    this->pointsText.setFont(this->font);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setCharacterSize(26);
    this->pointsText.setPosition(50.f, 68.f);
}

void Game::initTextures()
{
    if (!this->mushroomTexture.loadFromFile("assets/mushroom.png"))
        std::cout << "ERROR::GAME::INITTEXTURES: Mushroom texture not loaded correctly" << std::endl;
    if (!this->badMushroomTexture.loadFromFile("assets/bad_mushroom.png"))
        std::cout << "ERROR::GAME::INITTEXTURES: Bad Mushroom texture not loaded correctly" << std::endl;
    if (!this->healingPotionTexture.loadFromFile("assets/healing_potion.png"))
        std::cout << "ERROR::GAME::INITTEXTURES: Healing Potion texture not loaded correctly" << std::endl;
    if (!this->backgroundTexture.loadFromFile("assets/background.png"))
        std::cout << "ERROR::GAME::INITTEXTURES: Background texture not loaded correctly" << std::endl;
}

void Game::initSprites()
{
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->backgroundSprite.setPosition(0.f, 0.f);
    this->pointsSprite.setTexture(this->mushroomTexture);
    this->pointsSprite.setScale(0.17f, 0.17f);
    this->pointsSprite.setPosition(5.f, 67.f);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initTextures();
    this->initSprites();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool &Game::getEndGame() const
{
    return this->endGame;
}

// Modifiers
void Game::setTextureBasedOnType(Ball &ball, const int type)
{
    switch (type)
    {
    case BallTypes::DEFAULT:
        ball.setSpriteTexture(this->mushroomTexture);
        break;

    case BallTypes::DAMAGING:
        ball.setSpriteTexture(this->badMushroomTexture);
        break;

    case BallTypes::HEALING:
        ball.setSpriteTexture(this->healingPotionTexture);
        break;
    }
}

// Methods

const bool Game::isWindowOpen() const
{
    return this->window->isOpen();
}

void Game::closeWindow()
{
    this->window->close();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->closeWindow();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->closeWindow();
            break;
        }
    }
}

void Game::spawnBalls()
{
    // Timer
    if (this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 1.f;
    else
    {
        if (this->balls.size() < this->maxBalls)
        {

            int type = this->randomizeBallType();
            Ball b(this->window, type);

            this->setTextureBasedOnType(b, type);

            this->balls.push_back(b);
            this->spawnTimer = 0.f;
        }
    }
}

const int Game::randomizeBallType()
{
    int type = BallTypes::DEFAULT;
    int randValue = rand() % 100 + 1;

    // 30% of probability to get DAMAGING balls
    // 10% of probability to get HEALING balls
    // 60% of probability to get DEFAULT balls

    if (randValue > 60 && randValue <= 90)
        type = BallTypes::DAMAGING;
    else if (randValue > 90 && randValue <= 100)
        type = BallTypes::HEALING;

    return type;
}

// UPDATE & RENDER
void Game::updateCollision()
{
    // Check the collision
    for (int i = 0; i < this->balls.size(); i++)
    {

        // Check if the player collide with any of the balls
        if (this->player.getSprite().getGlobalBounds().intersects(this->balls[i].getSprite().getGlobalBounds()))
        {

            switch (this->balls[i].getType())
            {
            case BallTypes::DEFAULT:
                this->points += 1;
                break;

            case BallTypes::DAMAGING:
                this->player.takeDamage(0.5);
                break;

            case BallTypes::HEALING:
                this->player.gainHealth(0.5);
                break;
            }
            this->balls.erase(this->balls.begin() + i);
        }
    }
}

void Game::updateGui()
{

    std::stringstream guiString;
    std::stringstream pointsString;
    if (this->endGame == false)
    {
        pointsString << this->points;
    }
    else
    {
        guiString << "   Game Over" << std::endl
                  << "Your score is: " << this->points;
        this->guiText.setPosition(this->window->getSize().x / 2 - this->guiText.getGlobalBounds().width / 2, this->window->getSize().y / 2 - this->guiText.getGlobalBounds().height / 2);
        this->guiText.setCharacterSize(26);
    }

    this->pointsText.setString(pointsString.str());
    this->guiText.setString(guiString.str());
}

void Game::update()
{
    this->pollEvents();
    if (this->endGame == false)
    {
        this->spawnBalls();
        this->player.update(this->window);
        this->updateCollision();
    }
    this->updateGui();
    if (this->player.getHp() == 0)
        this->endGame = true;
}

void Game::renderGui(sf::RenderWindow *target)
{
    target->draw(this->backgroundSprite);
    target->draw(this->title);
    target->draw(this->pointsText);
    target->draw(this->guiText);
}
void Game::render()
{
    this->window->clear();
    // Render stuff
    this->renderGui(this->window);
    if (this->endGame == false)
    {
        this->window->draw(this->pointsSprite);
        this->player.render(this->window);
        for (auto i : this->balls)
        {
            i.render(this->window);
        }
    }
    this->window->display();
}