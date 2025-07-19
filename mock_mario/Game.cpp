#include "Player.cpp"
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game {
private:
	sf::RenderWindow* m_window;
	float m_delta_time;

	Player* mock_mario;
	const float speed = 100.f;

public:
	Game() {
		init();
		loop();
	}

	void init() {
		m_window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }), "Mock Mario", sf::Style::Default);
		m_window->setFramerateLimit(60); // oppure 120

		mock_mario = new Player();
	}

	void event_handling() {
		while (const std::optional event = m_window->pollEvent()) {

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>(); keyPressed != nullptr) {

				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					m_window->close();
			}

		}
	}

	~Game() {

		delete mock_mario;
		delete m_window;
	}

	void update() {
		mock_mario->update(m_delta_time);
	}

	void loop() {
		sf::Clock clock;
		while (m_window->isOpen()) {
			event_handling();
			m_delta_time = clock.restart().asSeconds();

			m_window->clear();

			update();

			mock_mario->draw(m_window);

			m_window->display();
		}
	}
};