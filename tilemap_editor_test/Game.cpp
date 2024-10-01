#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.cpp"

class Game
{
private:
    sf::RenderWindow *window;
    sf::Texture *background;
    sf::Sprite backgroundSprite;
    sf::View standardView;
    sf::RectangleShape *sidebarRectangle;
    sf::View sidebarView;

    float cursor_speed;

    Grid *grid;

    void initializeWindow()
    {
        this->window = new sf::RenderWindow(sf::VideoMode(1024, 720), "Map Editor", sf::Style::Default | sf::Style::Resize);
        this->window->setFramerateLimit(60);

        this->cursor_speed = 15;

        this->grid = new Grid(20, 20, 100, sf::Vector2f(0.8f, 1));

        // main view
        this->standardView.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
        this->standardView.setViewport(sf::FloatRect(0.2f, 0.0f, 0.8f, 1));

        // sidebar view
        this->sidebarView.setViewport(sf::FloatRect(0.0f, 0.0f, 0.2f, 1));
        this->sidebarRectangle = new sf::RectangleShape(sf::Vector2f(this->sidebarView.getSize().x, this->sidebarView.getSize().y));
        this->sidebarRectangle->setPosition(0.f, 0.f);
        this->sidebarRectangle->setFillColor(sf::Color(42, 43, 51, 255));
    }

public:
    Game()
    {

        this->initializeWindow();
    }

    void pollEvents()
    {
        // Event processing
        sf::Event event;
        while (this->window->pollEvent(event))
        {

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect standardVisibleArea(0.f, 0.f, event.size.width, event.size.height);
                this->standardView.setSize(standardVisibleArea.width, standardVisibleArea.height);
            }
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                this->window->close();

            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::P:
                    this->standardView.zoom(0.9f);
                    break;

                case sf::Keyboard::M:
                    this->standardView.zoom(1.1f);
                    break;

                case sf::Keyboard::W:
                    this->standardView.move(0, -10 * this->cursor_speed);
                    break;

                case sf::Keyboard::S:
                    this->standardView.move(0, 10 * this->cursor_speed);
                    break;

                case sf::Keyboard::A:
                    this->standardView.move(-10 * this->cursor_speed, 0);
                    break;

                case sf::Keyboard::D:
                    this->standardView.move(10 * this->cursor_speed, 0);
                    break;

                case sf::Keyboard::Escape:
                    this->window->close();
                    break;

                default:
                    break;
                }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta < 0)
                {

                    this->standardView.move(0, 10 * this->cursor_speed);
                }
                else if (event.mouseWheelScroll.delta >= 0)
                {
                    this->standardView.move(0, -10 * this->cursor_speed);
                }
            }
        }
    }

    void update()
    {
        this->pollEvents();
    }

    void render()
    {
        // Clear the whole window before rendering a new frame
        this->window->clear();

        this->window->setView(this->sidebarView);
        this->window->draw(*this->sidebarRectangle);

        this->window->setView(this->standardView);
        // this->window->draw(this->backgroundSprite);
        this->grid->draw(this->window, sf::RenderStates::Default);

        // End the current frame and display its contents on screen
        this->window->display();
    }

    void run()
    {
        while (this->window->isOpen())
        {

            this->update();

            this->render();
        }
    }
};