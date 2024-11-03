#include <SFML/Graphics.hpp>
#include "TextureTiles.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");

    sf::Vector2f containerSize = sf::Vector2f(500.0f, 600.0f);
    sf::Vector2f textureFileDimension = sf::Vector2f(96.0f, 96.0f);
    sf::Vector2f textureFileDimension2 = sf::Vector2f(1152.0f, 1536.0f);
    sf::Vector2f textureFileDimension3 = sf::Vector2f(384.0f, 64.0f);
    sf::Vector2f textureFileDimension4 = sf::Vector2f(1344.0f, 960.0f);

    TextureTiles textureTiles = TextureTiles(containerSize, "all_gnomes.png", textureFileDimension, 32.0f);
    TextureTiles t2 = TextureTiles(std::move(textureTiles));
    t2.load("Warrior_Yellow.png", textureFileDimension2, 192);
    // t2.load("Dynamite.png", textureFileDimension3, 64.0f);
    // textureTiles.load("Torch_Red.png", textureFileDimension4, 192.0f);

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