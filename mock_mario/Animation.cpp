#include <SFML/Graphics.hpp>

class Animation {
private:
	sf::Texture* m_texture;

	sf::Vector2u m_current_image; // posizione texture attuale
	sf::Vector2u m_image_count;   // numero di immagini totali

	float m_total_time;  // tempo di animazione totale passato
	float m_switch_time; // tempo che passa tra un cambio di texture e l'altro

public:
	sf::IntRect m_texture_rect;

	Animation(sf::Texture* texture, sf::Vector2u image_count, float switch_time) : m_image_count(image_count), m_switch_time(switch_time), m_total_time(0.0f) {

		m_current_image.x = 0; // all'inizio l'immagine attuale e' nella prima colonna

		// imposto le dimensioni del rettangolo che conterra' la texture alla dim della texture
		// diviso il numero di texture, in questo modo conosco la dimensione delle mie texture rect
		int width = texture->getSize().x / static_cast<float>(image_count.x);
		int height = texture->getSize().y / static_cast<float>(image_count.y);
		m_texture_rect.size.x = width;
		m_texture_rect.size.y = height;
	}

	float getTotalTime() {
		return m_total_time;
	}
	float getSwitchTime() {
		return m_switch_time;
	}

	int getCurrentImageX() {
		return m_current_image.x;
	}

	void update(int row, float delta_time, bool face_right) {

		// imposto la row attuale, perche' ad esempio quella in cui ho le texture del movimento e' la 1
		m_current_image.y = row;

		// al tempo tempo totale dell'animazione fin'ora aggiungo il tempo passato dall'ultimo frame
		m_total_time += delta_time;

		// in pratica quando termina l'animazione ricomincia dalla prima texture dell'animazione corrente
		if (m_total_time >= m_switch_time) {

			m_total_time -= m_switch_time;

			// faccio in modo di non uscire dalla texture
			m_current_image.x = (m_current_image.x + 1) % m_image_count.x;
		}

		// prendo l'immagine attuale nella riga m_current_image.y e nella colonna m_current_image.x
		// e le moltiplico per la larghezza e altezza di un singolo texture rect, in questo modo mi prendo
		// l'angolo in alto a sinistra della texture successiva
		int top = m_current_image.y * m_texture_rect.size.y;
		int left = m_current_image.x * m_texture_rect.size.x;

		// imposto la parte superiore
		m_texture_rect.position.y = top;

		// se sto guardando a destra allora la ok, la dimensione della texture e' positiva
		if (face_right) {
			m_texture_rect.position.x = left;
			m_texture_rect.size.x = abs(m_texture_rect.size.x);
		}
		else {
			// se sto guardando a sinistra, prendo non l'angolo in alto a sinistra ma quello in alto a destra
			// cioe' quello dove il texture rect che voglio termina e lo moltiplico per la dimensione che ora deve
			// essere negativa perche' sto prendendo la texture da destra a sinistra (all'indietro)
			m_texture_rect.position.x = (m_current_image.x + 1) * abs(m_texture_rect.size.x);
			m_texture_rect.size.x = -abs(m_texture_rect.size.x);
		}
	}
};