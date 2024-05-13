
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
}

void Game::initVariables()
{
    this->background = new Background(this->window);
    this->vec = VectorShape(200.f, 50.f, this->background->getOrigin());
    this->vec2 = this->vec.normalize(this->background->getUnitCircle().getRadius());
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
            break;
        }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(*this->window).x == this->vec2.getX()) && (sf::Mouse::getPosition(*this->window).y == this->vec2.getY()))
        std::cout << "hello" << std::endl;
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