#include "Animation.cpp"
#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
private:
	sf::Sprite* m_sprite;
	std::string m_texture_path;
	sf::Texture* m_texture;
	Animation* m_animation;

	enum State {
		IDLE,
		RUNNING,
		HITTING
	} m_state;


	sf::Keyboard::Scancode* m_keypressed;

	const float m_speed = 100.f;
	bool m_face_right;
	unsigned int m_row;

public:
	Player() {

		m_face_right = true;
		m_row = 0;

		m_state = State::IDLE;

		m_texture_path = "assets/Warrior_Yellow.png";
		m_texture = new sf::Texture();

		if (!m_texture->loadFromFile(m_texture_path))
			std::cerr << "PLAYER:: Error loading the texture";

		m_animation = new Animation(m_texture, sf::Vector2u({ 6, 8 }), 0.17);
		m_sprite = new sf::Sprite(*m_texture, sf::IntRect(sf::Vector2i(203, 0), sf::Vector2i(29, 29)));
		m_sprite->setPosition(sf::Vector2f({ 400.f, 300.f }));
	}

	~Player() {
		delete m_sprite;
		delete m_texture;
		delete m_animation;
		delete m_keypressed;
	}

	void setKeypressed(sf::Keyboard::Scancode keypressed) {
		sf::Keyboard::Scancode* k = new sf::Keyboard::Scancode(keypressed);
		m_keypressed = k;
	}

	void update_state(State new_state) {
		if (m_state == new_state)
			return;

		m_state = new_state;

		switch (m_state) {
			case State::IDLE:
				m_row = 0;
				break;
			case State::RUNNING:
				m_row = 1;
				break;
			case State::HITTING:
				m_row = 2;
				break;

			default:
				m_row = 0;
				break;
		}


		if (m_state == State::IDLE)
			std::cout << "IDLE" << std::endl;
		else
			std::cout << (m_state == State::RUNNING ? "RUNNING" : "HITTING") << std::endl;
	};



	void update(float delta_time) {

		// change state
		State new_state;

		sf::Vector2f movement({ 0.f, 0.f });

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
			movement.x += delta_time * m_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
			movement.x -= delta_time * m_speed;

		// se il movimento orizzontale e' nullo allora mi posiziono nella prima riga, cioe' quella delle animazioni idle
		if (movement.x == 0.0f) {
			new_state = State::IDLE;
		}
		else {
			// altrimenti vado nella riga successiva e se mi muovo a destra metto destra altrimenti metto sinistra
			new_state = State::RUNNING;
			if (movement.x > 0)
				m_face_right = true;
			else
				m_face_right = false;
		}


		// ho bisogno di catturare un solo click e devo aspettare che l'animazione del colpo sia terminata
		if (m_keypressed != nullptr && *m_keypressed == sf::Keyboard::Scancode::E && m_state != State::HITTING)
			new_state = State::HITTING;


		update_state(new_state);


		// aggiorno l'animazione con i nuovi valori e do al giocatore la nuova texture calcolata
		m_animation->update(m_row, delta_time, m_face_right);
		m_sprite->setTextureRect(m_animation->m_texture_rect);

		if (m_state == State::HITTING && (m_animation->getCurrentImageX() + 1) % 5 == 0) {
			delete m_keypressed;
			m_keypressed = nullptr;
		}

		// muovo il giocatore
		m_sprite->move(movement);
	}

	void draw(sf::RenderWindow* window) {
		window->draw(*m_sprite);
	}
};