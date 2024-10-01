#include "TileMap.h"

void TileMap::addTileToMap(Tile &tile, sf::Vector2f position)
{
    // upper triangle
    this->map.append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + position) * this->tileWorldDimension, sf::Vector2f(this->tileTextureDimension * tile.x, this->tileTextureDimension * tile.y)));

    this->map.append(sf::Vertex((sf::Vector2f(0.1f, 0.f) + position) * this->tileWorldDimension, sf::Vector2f(this->tileTextureDimension * tile.x + this->tileTextureDimension, this->tileTextureDimension * tile.y)));

    this->map.append(sf::Vertex((sf::Vector2f(0.1f, 0.1f) + position) * this->tileWorldDimension, sf::Vector2f(this->tileTextureDimension * tile.x + this->tileTextureDimension, this->tileTextureDimension * tile.y + this->tileTextureDimension)));

    // lower triangle
    this->map.append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + position) * this->tileWorldDimension, sf::Vector2f(this->tileTextureDimension * tile.x, this->tileTextureDimension * tile.y)));

    this->map.append(sf::Vertex((sf::Vector2f(0.0f, 0.1f) + position) * this->tileWorldDimension, sf::Vector2f(this->tileTextureDimension * tile.x, this->tileTextureDimension * tile.y + this->tileTextureDimension)));

    this->map.append(sf::Vertex((sf::Vector2f(0.1f, 0.1f) + position) * this->tileWorldDimension, sf::Vector2f(this->tileTextureDimension * tile.x + this->tileTextureDimension, this->tileTextureDimension * tile.y + this->tileTextureDimension)));
}

TileMap::TileMap(sf::Texture *tileSet, int width, int height, float tileTextureDimension, float tileWorldDimension)
{
    this->tileSet = tileSet;
    this->width = width;
    this->height = height;
    this->tileTextureDimension = tileTextureDimension;
    this->tileWorldDimension = tileWorldDimension;

    this->map = sf::VertexArray(sf::PrimitiveType::Triangles, (uint)(width * height * 6));
}

void TileMap::draw(sf::RenderWindow *target, sf::RenderStates states)
{
    states.texture = this->tileSet;

    target->draw(this->map, states);
}

void TileMap::loadMap(int vectorMap[7][20], int width, int height)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            Tile *tile = new Tile(vectorMap[i][j]);

            this->addTileToMap(*tile, sf::Vector2f((float)i / 10, (float)j / 10));
        }
}
