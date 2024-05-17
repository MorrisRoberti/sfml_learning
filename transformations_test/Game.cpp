
#include "Game.h"

// constructor / destructor
Game::Game()
{
    this->initWindow();
    this->initVariables();
}

Game::~Game()
{
    delete this->background;
    delete this->window;
}

// init
void Game::initWindow()
{
    this->videoMode = sf::VideoMode(900, 900);
    this->window = new sf::RenderWindow(this->videoMode, "Transformations", sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initVariables()
{
    this->background = new Background(this->window);
    this->vec = VectorShape(200.f, 50.f, this->background->getOrigin());
    this->vec2 = VectorShape(this->vec);
    this->vec2.normalize(this->background->getUnitCircle().getRadius());
};

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
        switch (this->event.type)
        {

        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            else if (this->event.key.code == sf::Keyboard::D)
                this->vec2.rotate(0.01f);
            else if (this->event.key.code == sf::Keyboard::A)
                this->vec2.rotate(-0.01f);

            break;
        }
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();

        this->render(this->window);
    }
}

// update
void Game::update()
{
    this->pollEvents();
    this->vec2.update();
}

void Game::render(sf::RenderWindow *target)
{
    target->clear();

    this->background->render(target);
    // this->vec.render(target);
    this->vec2.render(target);

    target->display();
}