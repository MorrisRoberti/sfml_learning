#include "TextureTiles.h"

const void TextureTiles::slice()
{
    return void();
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize)
{

    textures = std::vector<sf::Texture>();
    spritesOfTextures = std::vector<sf::Sprite>();

    textureFile = nullptr;
    textureFileName = "";
    textureFileDim = sf::Vector2f(0.0f, 0.0f);

    singleTextureDim = 0.0f;

    container = sf::RectangleShape(containerSize);
    container.setFillColor(sf::Color::Black);
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize, const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    *this = TextureTiles(containerSize);
    this->load(textureFileNameString, textureFileDimension, singleTextureDimension);
}

TextureTiles::~TextureTiles()
{
    textures.~vector();
    delete textureFile;
}

TextureTiles::TextureTiles(const TextureTiles &other)
{
    textures = other.textures;
    spritesOfTextures = other.spritesOfTextures;

    textureFile = other.textureFile;
    textureFileName = other.textureFileName;
    textureFileDim = other.textureFileDim;
    singleTextureDim = other.singleTextureDim;

    container = other.container;
}

TextureTiles::TextureTiles(TextureTiles &&other)
{
    textures = other.textures;
    spritesOfTextures = other.spritesOfTextures;

    textureFile = other.textureFile;
    textureFileName = other.textureFileName;
    textureFileDim = other.textureFileDim;
    singleTextureDim = other.singleTextureDim;

    container = other.container;

    other.textureFile = nullptr;
}

TextureTiles &TextureTiles::operator=(const TextureTiles &other)
{
    if (textureFile != other.textureFile)
    {
        textures = other.textures;
        spritesOfTextures = other.spritesOfTextures;

        delete textureFile;
        textureFile = other.textureFile;
        textureFileName = other.textureFileName;
        textureFileDim = other.textureFileDim;
        singleTextureDim = other.singleTextureDim;
        container = container;
    }

    return *this;
}

TextureTiles &TextureTiles::operator=(TextureTiles &&other)
{
    if (textureFile != other.textureFile)
    {
        textures = other.textures;
        spritesOfTextures = other.spritesOfTextures;

        delete textureFile;
        textureFile = other.textureFile;
        textureFileName = other.textureFileName;
        textureFileDim = other.textureFileDim;
        singleTextureDim = other.singleTextureDim;
        container = container;
    }

    other.textureFile = nullptr;

    return *this;
}

const void TextureTiles::update()
{
    return void();
}

const void TextureTiles::draw(sf::RenderTarget &window) const
{
    // I draw each sprite of the spritesOfTextures array into the container
    window.draw(container);
}

const void TextureTiles::load(const std::string textureFileName, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    // i load the texture -> handle the error

    // i slice them

    // i put them into the spritesOfTextures array ->
}

const std::vector<sf::Texture> &TextureTiles::getTextures() const
{
    return textures;
}
