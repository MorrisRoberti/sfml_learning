#include "Player.cpp"
#include <map>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Level {
private:
	enum LevelLayers {
		BACKGROUND,
		BACK,
		FRONT,
		GROUND
	};
	std::vector<std::pair<LevelLayers, sf::Sprite*>> m_map_background;

	std::vector<sf::Texture*> m_textures;
public:
	Level(std::string background_path) {

		for (int i = 0; i < 4; ++i) {
			sf::Texture* tex = new sf::Texture();
			m_textures.push_back(tex);
		}


		if (!m_textures[0]->loadFromFile(background_path + "\\background.png") || !m_textures[1]->loadFromFile(background_path + "\\back.png") || !m_textures[2]->loadFromFile(background_path + "\\front.png") || !m_textures[3]->loadFromFile(background_path + "\\ground.png"))
			std::cerr << "ERROR LOADING THE BACKGROUND OF LEVEL" << std::endl;


		sf::Vector2f scaling_factor({ 4.0f, 3.0f });

		sf::Sprite* background_sprite = new sf::Sprite(*m_textures[0]);
		background_sprite->setScale(scaling_factor);

		m_map_background.push_back(std::pair<LevelLayers, sf::Sprite*>(LevelLayers::BACKGROUND, background_sprite));

		sf::Sprite* back_sprite = new sf::Sprite(*m_textures[1]);
		back_sprite->setScale(scaling_factor);

		m_map_background.push_back(std::pair<LevelLayers, sf::Sprite*>(LevelLayers::BACK, back_sprite));


		sf::Sprite* front_sprite = new sf::Sprite(*m_textures[2]);
		front_sprite->setScale(scaling_factor);

		m_map_background.push_back(std::pair<LevelLayers, sf::Sprite*>(LevelLayers::FRONT, front_sprite));



		sf::Sprite* ground_sprite = new sf::Sprite(*m_textures[3]);
		ground_sprite->setScale(scaling_factor);

		m_map_background.push_back(std::pair<LevelLayers, sf::Sprite*>(LevelLayers::GROUND, ground_sprite));

	}


	void draw(sf::RenderWindow* window) {

		for (int i = 0; i < 4; ++i)
			window->draw(*(m_map_background[i].second));
	}

	~Level() {
		for (int i = 0; i < m_map_background.size(); ++i)
			delete m_map_background[i].second;

		for (int i = 0; i < m_textures.size(); ++i)
			delete m_textures[i];

	}
};


class Game {
private:
	sf::RenderWindow* m_window;
	float m_delta_time;

	Player* mock_mario;
	Level* level;
	const float speed = 100.f;

public:
	Game() {
		init();
		loop();
	}

	void init() {
		m_window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }), "Mock Mario", sf::Style::Default);
		m_window->setFramerateLimit(60); // oppure 120
		m_window->setKeyRepeatEnabled(false);

		mock_mario = new Player();
		level = new Level("assets/Jungle");
	}

	// precondition: keyPressed is never nullptr
	void input_handle(const sf::Event::KeyPressed* keyPressed) {

		if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			m_window->close();

		mock_mario->input_handle(keyPressed);
	}

	void event_handling() {
		while (const std::optional event = m_window->pollEvent()) {

			if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>(); keyPressed != nullptr) {

				input_handle(keyPressed);

			}
		}
	}

	~Game() {

		delete mock_mario;
		delete level;
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

			level->draw(m_window);
			mock_mario->draw(m_window);

			m_window->display();
		}
	}
};