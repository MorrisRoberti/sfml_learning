#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include "Player.cpp"

class Game
{
private:
    sf::RenderWindow *m_window;
    float m_delta_time;

    Player *mock_mario;
    const float speed = 100.f;

public:
    Game()
    {
        init();
        loop();
    }

    void init()
    {
        m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mock Mario", sf::Style::Default);
        m_window->setFramerateLimit(60); // oppure 120

        mock_mario = new Player();
    }

    void event_handling()
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                m_window->close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                mock_mario->move(m_delta_time * speed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                mock_mario->move(m_delta_time * -speed, 0);
        }
    }

    ~Game()
    {

        delete mock_mario;
        delete m_window;
    }

    void update()
    {
        mock_mario->update();
    }

    void loop()
    {
        sf::Clock clock;
        while (m_window->isOpen())
        {
            event_handling();
            m_delta_time = clock.restart().asSeconds();

            m_window->clear();

            update();
            mock_mario->draw(m_window);

            m_window->display();
        }
    }
};