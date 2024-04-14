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
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
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
            this->balls.push_back(Ball(this->window));
            this->spawnTimer = 0.f;
        }
    }
}

// UPDATE & RENDER

void Game::update()
{
    this->pollEvents();
    this->spawnBalls();
    this->player.update(this->window);
}

void Game::render()
{
    this->window->clear();

    // Render stuff
    this->player.render(this->window);

    for (auto i : this->balls)
    {
        i.render(this->window);
    }

    this->window->display();
}