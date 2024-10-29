#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TextureTiles
{
private:
    std::vector<sf::Texture> textures; // this is the final array of textures that will be drawn
    sf::Texture *textureFile;          // the original file where the texture are stored together
    sf::Vector2f textureFileDim;       // the dimension of the file that stores the textures
    float singleTextureDim;            // the dimension of the single textures in the textureFile (the texture have to be square)

    sf::RectangleShape container;

    const void slice();

public:
    TextureTiles(const sf::Vector2f containerSize); // only creates the rectangle to contain the textures

    TextureTiles(const sf::Vector2f containerSize, const std::string textureFileName, const sf::Vector2f textureFileDimension, float singleTextureDimension);

    ~TextureTiles();

    TextureTiles(const TextureTiles &other);

    TextureTiles(TextureTiles &&other); // move constructor

    TextureTiles &operator=(const TextureTiles &other);

    TextureTiles &operator=(TextureTiles &&other); // move assignment

    const void update();

    const void draw(sf::RenderTarget &window) const;

    const void load(const std::string textureFileName, const sf::Vector2f textureFileDimension, float singleTextureDimension);

    const std::vector<sf::Texture> &getTextures() const;
};