#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
    // Attributes
    sf::RectangleShape shape;
    float movementSpeed;
    int hp;
    int hpMax;

    // Methods
    void initVariables();
    void initShape();

public:
    // Constructors / Destructor
    Player(float x = 0.f, float y = 0.f);
    ~Player();

    // Methods
    void takeDamage(const int damage);
    void gainHealth(const int health);

    // Accessors
    const sf::RectangleShape &getShape() const;
    const int &getHp() const;
    const int &getMaxHp() const;

    // Update
    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget *target);
    void update(const sf::RenderTarget *target);

    // Render
    void render(sf::RenderTarget *targer);
};