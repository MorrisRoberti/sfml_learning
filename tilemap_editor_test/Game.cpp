#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Grid.cpp"

class Game
{
private:
    sf::RenderWindow *window;
    sf::Texture *background;
    sf::Sprite backgroundSprite;

    sf::RectangleShape *sidebarRectangle;
    sf::RectangleShape *standardViewRectangle;
    sf::RectangleShape *textureViewRectangle;
    sf::RectangleShape *loadTextureButton;

    sf::View standardView;
    sf::View sidebarView;
    sf::View textureView;

    float cursor_speed;

    Grid *grid;

    void initializeWindow()
    {
        this->window = new sf::RenderWindow(sf::VideoMode(1024, 720), "Map Editor", sf::Style::Default | sf::Style::Resize);
        this->window->setFramerateLimit(60);

        this->cursor_speed = 15;

        // main view
        this->standardView.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
        this->standardView.setViewport(sf::FloatRect(0.2f, 0.0f, 1, 1));

        this->grid = new Grid(20, 20, 100, sf::Vector2f(1, 1));

        // sidebar view
        this->sidebarView.setViewport(sf::FloatRect(0.0f, 0.0f, 0.2f, 1));
        this->sidebarRectangle = new sf::RectangleShape(sf::Vector2f(this->sidebarView.getSize().x, this->sidebarView.getSize().y));
        this->sidebarRectangle->setPosition(0.f, 0.f);
        this->sidebarRectangle->setFillColor(sf::Color(42, 43, 51, 255));

        this->loadTextureButton = new sf::RectangleShape(sf::Vector2f(this->sidebarRectangle->getSize().x - (0.05f * this->sidebarRectangle->getSize().x), 0.05f * this->sidebarRectangle->getSize().y));
        this->loadTextureButton->setPosition(0.025f * this->sidebarRectangle->getSize().x, 0.63f * this->sidebarRectangle->getSize().y);
        this->loadTextureButton->setFillColor(sf::Color(25.0f, 26.0f, 36.0f, 255));

        // texture view
        this->textureView.setViewport(sf::FloatRect(0.005f, 0.7f, 0.190f, 0.295f));
        this->textureViewRectangle = new sf::RectangleShape(sf::Vector2f(this->textureView.getSize().x, this->textureView.getSize().y));
        this->textureViewRectangle->setPosition(0.f, 0.f);
        this->textureViewRectangle->setFillColor(sf::Color(0, 0, 0, 255));
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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // I map the pixel to the view coordinates
                    const sf::Vector2f pixelCoords = this->window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), this->standardView);
                    this->grid->removeTexture(pixelCoords);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {

                    // I map the pixel to the view coordinates
                    const sf::Vector2f pixelCoords = this->window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), this->standardView);
                    this->grid->setCellTexture(pixelCoords);
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
        this->window->draw(*this->loadTextureButton);

        this->window->setView(this->textureView);
        this->window->draw(*this->textureViewRectangle);

        this->window->setView(this->standardView);
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