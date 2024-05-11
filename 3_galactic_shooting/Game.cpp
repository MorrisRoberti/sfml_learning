#include "Game.h"

// constructors / destructors
Game::Game()
{
    this->initVariables();
    this->initTextures();
    this->initWindow();
    this->initPlayer();
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    // deallocates the textures
    for (auto &i : this->textures)
        delete i.second;

    // deallocates bullets
    for (auto *bullet : this->bullets)
        delete bullet;
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
    this->textures["BULLET"] = new sf::Texture();
    if (!this->textures["BULLET"]->loadFromFile("assets/bullet.png"))
        std::cout << "ERROR::GAME::INITTEXTURES: Bullet texture not loaded correctly" << std::endl;
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

    std::cout << this->player->getRotation() << std::endl;
    this->player->rotate(sf::Mouse::getPosition(*this->window));

    // shoot
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
    {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x, this->player->getPosition().y, sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y, 0.01f));
    }
}

void Game::updateBullets()
{
    int counter = 0;
    for (auto *bullet : this->bullets)
    {
        bullet->update();

        // bullet culing (top screen)
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            // delete bullet
            this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
            --counter;
        }
        counter++;
    }
}

// UPDATE & RENDER
void Game::update()
{
    this->updatePollEvents();
    this->updateInput();
    this->player->update();
    this->updateBullets();
}

void Game::render(sf::RenderWindow *target)
{
    target->clear();

    for (auto *bullet : this->bullets)
        bullet->render(*target);

    this->player->render(*target);

    target->display();
}