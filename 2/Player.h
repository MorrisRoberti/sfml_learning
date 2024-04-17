#pragma once

#include <iostream>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
    // Attributes
    float movementSpeed;
    float hp;
    float hpMax;

    sf::Texture fullHeartTexture;
    sf::Texture halfHeartTexture;
    sf::Texture emptyHeartTexture;

    sf::Texture playerTexture;

    std::vector<sf::Sprite> heartSprites;
    sf::Sprite heartSprite;
    sf::Sprite playerSprite;

    // Methods
    void initVariables();
    void initTextures();
    void initSprites();

public:
    // Constructors / Destructor
    Player(float x = 0.f, float y = 0.f);
    ~Player();

    // Methods
    void takeDamage(const float damage);
    void gainHealth(const float health);

    // Accessors
    const sf::Sprite &getSprite() const;
    const float &getHp() const;
    const float &getMaxHp() const;

    // Update
    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget *target);
    void updateHealthTextures();
    void update(const sf::RenderTarget *target);

    // Render
    void render(sf::RenderTarget *targer);
};