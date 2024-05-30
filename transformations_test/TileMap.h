#pragma once
#include <iostream>
#include "Tile.h"
#include <SFML/Graphics.hpp>

class TileMap
{
private:
    // attributes
    sf::VertexArray map;
    sf::Texture *tileSet;

    int width;
    int height;
    float tileTextureDimension; // dimension of the tile in the texture
    float tileWorldDimension;   // dimension of the tile once drawn on screen

    void addTileToMap(Tile &tile, sf::Vector2f position);

public:
    // constructor
    TileMap(sf::Texture *tileset, int width, int height, float tileTextureDimension, float tileWorldDimension);
    void draw(sf::RenderWindow *target, sf::RenderStates states);

    void loadMap(int vectorMap[20][7], int width, int height);
};