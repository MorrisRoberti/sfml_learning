#include <SFML/Graphics.hpp>

class Tile
{
public:
    float x;
    float y;

    sf::Color color;

    Tile(float x, float y, sf::Color color);
    Tile();
    Tile(int type);
};