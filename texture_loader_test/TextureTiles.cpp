#include "TextureTiles.h"

const void TextureTiles::slice()
{
    return void();
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize)
{

    textures = std::vector<sf::Texture>();

    textureFile = nullptr;
    textureFileDim = sf::Vector2f(0.0f, 0.0f);

    singleTextureDim = 0.0f;

    container = sf::RectangleShape(containerSize);
    container.setFillColor(sf::Color::Black);
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize, const std::string textureFileName, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    *this = TextureTiles(containerSize);
    this->load(textureFileName, textureFileDimension, singleTextureDimension);
}

TextureTiles::~TextureTiles()
{
}

TextureTiles::TextureTiles(const TextureTiles &other)
{
}

TextureTiles::TextureTiles(TextureTiles &&other)
{
}

TextureTiles &TextureTiles::operator=(const TextureTiles &other)
{
    // TODO: insert return statement here
}

TextureTiles &TextureTiles::operator=(TextureTiles &&other)
{
    // TODO: insert return statement here
}

const void TextureTiles::update()
{
    return void();
}

const void TextureTiles::draw(sf::RenderTarget &window) const
{
    return void();
}

const void TextureTiles::load(const std::string textureFileName, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    return void();
}

const std::vector<sf::Texture> &TextureTiles::getTextures() const
{
    return textures;
}
