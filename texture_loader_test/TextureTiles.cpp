#include "TextureTiles.h"

const void TextureTiles::slice()
{
    // at first I slice the textureFile according to the dimensions

    sf::Vector2i numberOfTextures = sf::Vector2i(static_cast<int>(textureFileDim.x / singleTextureDim), static_cast<int>(textureFileDim.y / singleTextureDim));
    std::vector<sf::IntRect> rectsToSliceTexture = std::vector<sf::IntRect>();
    // then for each texture stored I create a pointer and insert it in the textures array
    for (int i = 0; i < numberOfTextures.x; i++)
    {
        for (int j = 0; j < numberOfTextures.y; j++)
        {
            sf::IntRect tmp = sf::IntRect(sf::Vector2i(i * singleTextureDim, j * singleTextureDim), sf::Vector2i(singleTextureDim, singleTextureDim));
            rectsToSliceTexture.push_back(tmp);
        }
    }

    std::cout << (numberOfTextures.x * numberOfTextures.y) << std::endl;
    for (int i = 0; i < numberOfTextures.x * numberOfTextures.y; i++)
    {
        sf::Texture *tmp = new sf::Texture();
        if (!tmp->loadFromImage(*textureFile, rectsToSliceTexture[i]))
        {
            std::cout << "failed" << std::endl;
        }
        else
        {
            sf::Sprite *tmpSprite = new sf::Sprite(*tmp);
            tmpSprite->setPosition(50, i * 20);
            spritesOfTextures.push_back(tmpSprite);
            textures.push_back(tmp);
        }
    }
}

TextureTiles::TextureTiles()
{
    std::cout << "Empty Constructor" << std::endl;

    textures = std::vector<sf::Texture *>();
    spritesOfTextures = std::vector<sf::Sprite *>();

    textureFile = new sf::Image();
    textureFileName = "";
    textureFileDim = sf::Vector2f(0.0f, 0.0f);

    singleTextureDim = 0.0f;

    container = sf::RectangleShape(sf::Vector2f(0.0f, 0.0f));
    container.setPosition(0.0f, 0.0f);
    container.setFillColor(sf::Color::Blue);
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize)
{
    std::cout << "Container only Constructor" << std::endl;

    textures = std::vector<sf::Texture *>();
    spritesOfTextures = std::vector<sf::Sprite *>();

    textureFile = new sf::Image();
    textureFileName = "";
    textureFileDim = sf::Vector2f(0.0f, 0.0f);

    singleTextureDim = 0.0f;

    container = sf::RectangleShape(containerSize);
    container.setPosition(0.0f, 0.0f);
    container.setFillColor(sf::Color::Blue);
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize, const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    std::cout << "Load Constructor" << std::endl;

    textures = std::vector<sf::Texture *>();
    spritesOfTextures = std::vector<sf::Sprite *>();

    textureFile = new sf::Image();

    container = sf::RectangleShape(containerSize);
    container.setPosition(0.0f, 0.0f);
    container.setFillColor(sf::Color::Blue);

    // do some controls to check that: textureFileDimension and sinleTextureFiles are >= and the first is >= then the second

    load(textureFileNameString, textureFileDimension, singleTextureDimension);
}

TextureTiles::~TextureTiles()
{
    std::cout << "Destructor" << std::endl;
    for (auto p : textures)
    {
        delete p;
    }

    for (auto p : spritesOfTextures)
    {
        delete p;
    }

    std::cout << "hwlo" << std::endl;
    delete textureFile;
}

TextureTiles::TextureTiles(const TextureTiles &other)
{

    std::cout << "Copy Constructor" << std::endl;

    for (auto p : other.textures)
    {
        sf::Texture *tmp = new sf::Texture(*p);
        textures.push_back(tmp);
    }

    for (auto p : other.spritesOfTextures)
    {
        sf::Sprite *tmp = new sf::Sprite(*p);
        spritesOfTextures.push_back(tmp);
    }

    textureFile = new sf::Image(*other.textureFile);
    textureFileName = other.textureFileName;
    textureFileDim = other.textureFileDim;
    singleTextureDim = other.singleTextureDim;

    container = other.container;
}

TextureTiles::TextureTiles(TextureTiles &&other)
{
    std::cout << "Move Constructor" << std::endl;

    for (auto p : other.textures)
    {
        sf::Texture *tmp;
        tmp = new sf::Texture(*p);
        textures.push_back(tmp);
    }
    for (auto p : other.spritesOfTextures)
    {
        sf::Sprite *tmp;
        tmp = new sf::Sprite(*p);
        spritesOfTextures.push_back(tmp);
    }

    textureFile = new sf::Image(*other.textureFile);
    textureFileName = other.textureFileName;
    textureFileDim = other.textureFileDim;
    singleTextureDim = other.singleTextureDim;

    container = other.container;
}

TextureTiles &TextureTiles::operator=(const TextureTiles &other)
{
    std::cout << "Assignment" << std::endl;

    if (textureFile != other.textureFile)
    {
        for (auto p : other.textures)
        {
            sf::Texture *tmp = new sf::Texture(*p);
            textures.push_back(tmp);
        }
        for (auto p : other.spritesOfTextures)
        {
            sf::Sprite *tmp = new sf::Sprite(*p);
            spritesOfTextures.push_back(tmp);
        }

        delete textureFile;
        textureFile = new sf::Image(*other.textureFile);

        textureFileName = other.textureFileName;
        textureFileDim = other.textureFileDim;
        singleTextureDim = other.singleTextureDim;
        container = container;
    }

    return *this;
}

TextureTiles &TextureTiles::operator=(TextureTiles &&other)
{
    std::cout << "Move Assigment" << std::endl;

    if (textureFile != other.textureFile)
    {
        for (auto p : other.textures)
        {
            sf::Texture *tmp;
            tmp = new sf::Texture(*p);
            textures.push_back(tmp);
        }

        for (auto p : other.spritesOfTextures)
        {
            sf::Sprite *tmp;
            tmp = new sf::Sprite(*p);
            spritesOfTextures.push_back(tmp);
        }

        delete textureFile;

        textureFile = new sf::Image(*other.textureFile);

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
    window.draw(container);
    for (int i = 0; i < spritesOfTextures.size(); i++)
        window.draw(*spritesOfTextures[i]);
}

const void TextureTiles::load(const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    std::cout << "Load" << std::endl;

    delete textureFile;

    textureFile = new sf::Image();
    textureFileName = textureFileNameString;
    textureFileDim = textureFileDimension;

    singleTextureDim = singleTextureDimension;

    if (!(textureFile->loadFromFile(textureFileName)))
    {
        std::cout << "TEXTURES:: Failed to load  the texture" << std::endl;
    }
    else
    {
        std::cout << "successfully loaded" << std::endl;

        slice();
    }
}

const std::vector<sf::Texture *> &TextureTiles::getTextures() const
{
    return textures;
}
