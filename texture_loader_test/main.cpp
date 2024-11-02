#include <SFML/Graphics.hpp>
#include "TextureTiles.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    sf::Vector2f containerSize = sf::Vector2f(200.0f, 250.0f);
    sf::Vector2f textureFileDimension = sf::Vector2f(96.0f, 96.0f);
    sf::Vector2f textureFileDimension2 = sf::Vector2f(1152.0f, 1536.0f);

    TextureTiles textureTiles = TextureTiles(containerSize, "all_gnomes.png", textureFileDimension, 32.0f);
    TextureTiles t2;
    t2 = textureTiles;
    t2.load("Warrior_Yellow.png", textureFileDimension2, 192);
    ;
    // textureTiles.load("Warrior_Yellow.png", textureFileDimension2, 192);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();

        // draw
        t2.draw(window);

        window.display();
    }

    return 0;
}