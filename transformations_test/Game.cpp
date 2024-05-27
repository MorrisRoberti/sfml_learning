
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

    this->mousePointer.setFillColor(sf::Color::Blue);
    this->mousePointer.setRadius(10);
    this->mousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
    this->mousePointer.setOrigin(this->mousePointer.getLocalBounds().height / 2, this->mousePointer.getLocalBounds().width / 2);
};

void Game::pollEvents()
{
    float norm;
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
        case sf::Event::MouseMoved:
            this->mousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));

            // direction vector
            sf::Vector2f dir = {(static_cast<float>(sf::Mouse::getPosition(*window).x) - this->vec2.getOrigin().x), (static_cast<float>(sf::Mouse::getPosition(*window).y) - this->vec2.getOrigin().y)};

            // normalization
            norm = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
            dir = (dir / norm);
            dir.x *= 200;
            dir.y *= 200;

            this->vec2.setX(dir.x + this->vec2.getOrigin().x);
            this->vec2.setY(dir.y + this->vec2.getOrigin().y);

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
    this->vec2.render(target);
    target->draw(this->mousePointer);

    target->display();
}