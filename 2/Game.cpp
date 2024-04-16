#include "Game.h"

// Private methods
void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
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
    this->title.setString("Hello World");
    this->title.setFillColor(sf::Color::White);
    this->title.setCharacterSize(24);
    this->title.setPosition(0.f, 0.f);

    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(16);
    this->guiText.setPosition(0.f, 30.f);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
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
            Ball b(this->window, rand() % BallTypes::NROFTYPES);
            std::cout << "new ball type: " << b.getType() << std::endl;
            this->balls.push_back(b);
            this->spawnTimer = 0.f;
        }
    }
}

// UPDATE & RENDER
void Game::updateCollision()
{
    // Check the collision
    for (int i = 0; i < this->balls.size(); i++)
    {

        // Check if the player collide with any of the balls
        if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
        {
            std::cout << "Type: " << this->balls[i].getType() << std::endl;

            switch (this->balls[i].getType())
            {
            case BallTypes::DEFAULT:
                this->points += 1;
                std::cout << "points" << std::endl;
                break;

            case BallTypes::DAMAGING:
                this->player.takeDamage(1);
                std::cout << "damage" << std::endl;
                break;

            case BallTypes::HEALING:
                this->player.gainHealth(1);
                std::cout << "health" << std::endl;
                break;
            }
            this->balls.erase(this->balls.begin() + i);
        }
    }
}

void Game::updateGui()
{
    std::stringstream ss;
    ss << "Points: " << this->points << std::endl
       << "Health: " << this->player.getHp() << " /" << this->player.getMaxHp() << std::endl;

    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();
    this->spawnBalls();
    this->player.update(this->window);
    this->updateCollision();
    this->updateGui();
}

void Game::renderGui(sf::RenderWindow *target)
{
    target->draw(this->title);
    target->draw(this->guiText);
}
void Game::render()
{
    this->window->clear();

    // Render stuff
    this->player.render(this->window);

    this->renderGui(this->window);

    for (auto i : this->balls)
    {
        i.render(this->window);
    }

    this->window->display();
}