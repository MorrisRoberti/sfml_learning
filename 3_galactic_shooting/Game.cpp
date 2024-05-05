#include "Game.h"

// constructors / destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initPlayer();
}

Game::~Game()
{
    delete this->window;
    delete this->player;
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
    this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{

    // loading textures and inserting them in the textures map
}

void Game::initPlayer()
{
    this->player = new Player();
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

void Game::updatePollEvents()
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

void Game::updateInput()
{
    // move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);
}

// UPDATE & RENDER
void Game::update()
{
    this->updatePollEvents();
    this->updateInput();
}

void Game::render(sf::RenderWindow *target)
{
    target->clear();

    this->player->render(*target);

    target->display();
}