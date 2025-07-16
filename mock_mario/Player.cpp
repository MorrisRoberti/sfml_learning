#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
private:
    sf::Sprite *m_sprite;
    std::string m_texture_path;
    sf::Texture *m_texture;
    enum statetype
    {
        IDLE_R,
        IDLE_L,
        IDLE,
        MOVING,
        JUMPING
    } m_state;

    // FSM
    void change_state(float x, float y)
    {

        if (x > 0)
            m_state = IDLE_R;
        if (x < 0)
            m_state = IDLE_L;
    }

    void update_texture()
    {
        switch (m_state)
        {
        case IDLE_R:
            m_sprite->setTextureRect(sf::IntRect(sf::Vector2i(203, 0), sf::Vector2i(29, 29)));
            break;
        case IDLE_L:
            m_sprite->setTextureRect(sf::IntRect(sf::Vector2i(174, 0), sf::Vector2i(29, 29)));
            break;
        default:
            m_sprite->setTextureRect(sf::IntRect(sf::Vector2i(203, 0), sf::Vector2i(29, 29)));
            break;
        }
    }

public:
    Player()
    {

        m_texture_path = "assets/mario_texture.png";
        m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(m_texture_path))
            std::cerr << "PLAYER:: Error loading the texture";

        m_sprite = new sf::Sprite(*m_texture, sf::IntRect(sf::Vector2i(203, 0), sf::Vector2i(29, 29)));
        m_state = IDLE_R;
    }

    ~Player()
    {
        delete m_sprite;
        delete m_texture;
    }

    void move(float offset_x, float offset_y)
    {
        m_sprite->move(offset_x, offset_y);
        change_state(offset_x, offset_y);
    }

    void update()
    {
        update_texture();
    }

    void draw(sf::RenderWindow *window)
    {
        window->draw(*m_sprite);
    }
};