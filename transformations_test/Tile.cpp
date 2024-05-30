#include "Tile.h"

Tile::Tile(float x, float y, sf::Color color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}

Tile::Tile()
{
    this->x = 0;
    this->y = 0;
}

Tile::Tile(int type)
{
    switch (type)
    {
    case 0:
        this->x = 0;
        this->y = 0;
        break;
    case 1:
        this->x = 0;
        this->y = 1;
        break;
    case 2:
        this->x = 10;
        this->y = 12;
        break;
    }
    this->color = sf::Color::White;
}