#include "Game.h"

// constructors / destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

// initializers

void Game::initVariables()
{
    this->videomode = sf::VideoMode(800, 600);
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(this->videomode, "Galactic Shooting", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initTextures() {}

// private methods
void Game::pollEvents()
{

    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {

        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

// methods
void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();

        this->render(this->window);
    }
}

// UPDATE & RENDER
void Game::update()
{
    this->pollEvents();
}

void Game::render(sf::RenderWindow *target)
{
    target->clear();

    target->display();
}