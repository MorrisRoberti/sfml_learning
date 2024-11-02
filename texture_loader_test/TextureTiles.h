#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class TextureTiles
{
private:
    std::vector<sf::Texture *> textures;         // this is the array of textures that have to be drawn
    std::vector<sf::Sprite *> spritesOfTextures; // this array is the actual one drawn into the container to show available textures
    sf::Image *textureFile;                      // the original file where the texture are stored together
    std::string textureFileName;
    sf::Vector2f textureFileDim; // the dimension of the file that stores the textures
    float singleTextureDim;      // the dimension of the single textures in the textureFile (the texture have to be square)

    sf::RectangleShape container;

    const void slice();
    void cleanup();

public:
    TextureTiles();

    TextureTiles(const sf::Vector2f containerSize); // only creates the rectangle to contain the textures

    TextureTiles(const sf::Vector2f containerSize, const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension);

    ~TextureTiles();

    TextureTiles(const TextureTiles &other);

    TextureTiles(TextureTiles &&other); // move constructor

    TextureTiles &operator=(const TextureTiles &other);

    TextureTiles &operator=(TextureTiles &&other); // move assignment

    const void update();

    const void draw(sf::RenderTarget &window) const;

    const void load(const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension);

    const std::vector<sf::Texture *> &getTextures() const;
};