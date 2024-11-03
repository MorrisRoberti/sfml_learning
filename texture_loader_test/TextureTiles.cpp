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

    int j = 0;
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
            spritesOfTextures.push_back(tmpSprite);
            textures.push_back(tmp);
        }
    }
}

const void TextureTiles::arrangeTexturesInContainer()
{

    float heightOfAllRows = singleTextureDim * 3; // number of columns are 3, so i take the number of rows and multiplying it by texture height

    float scale = view->getSize().x / heightOfAllRows; // Use the smaller scale to fit

    for (int i = 0, tmp = 0, j = 0; i < spritesOfTextures.size(); i++)
    {
        spritesOfTextures[i]->setScale(scale, scale);

        int row = i / 3; // 3 textures per row
        int col = i % 3;
        float x = col * singleTextureDim * scale; // Position based on column
        float y = row * singleTextureDim * scale; // Position based on row

        spritesOfTextures[i]->setPosition(x, y);
    }
}

const void TextureTiles::cleanup()
{
    std::cout << "Cleanup" << std::endl;
    if (textures.size() != 0)
    {

        for (auto p : textures)
        {
            delete p;
        }
    }

    if (spritesOfTextures.size() != 0)
    {

        for (auto p : spritesOfTextures)
        {
            delete p;
        }
    }

    if (textureFile != nullptr)
    {
        delete textureFile;
    }
}

const void TextureTiles::initVariables()
{
    textures = std::vector<sf::Texture *>();
    spritesOfTextures = std::vector<sf::Sprite *>();

    textureFile = nullptr;
    textureFileName = "";
    textureFileDim = sf::Vector2f(0.0f, 0.0f);

    view = nullptr;

    singleTextureDim = 0.0f;
}

TextureTiles::TextureTiles()
{
    std::cout << "Empty Constructor" << std::endl;

    initVariables();

    container = sf::RectangleShape(sf::Vector2f(300.0f, 350.0f));
    container.setPosition(0.0f, 0.0f);
    container.setFillColor(sf::Color::Blue);
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize)
{
    std::cout << "Container only Constructor" << std::endl;

    initVariables();

    container = sf::RectangleShape(containerSize);
    container.setPosition(0.0f, 0.0f);
    container.setFillColor(sf::Color::Blue);
    view = new sf::View(sf::FloatRect(container.getPosition(), containerSize));
}

TextureTiles::TextureTiles(const sf::Vector2f containerSize, const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    std::cout << "Load Constructor" << std::endl;

    initVariables();

    container = sf::RectangleShape(containerSize);
    container.setPosition(0.0f, 0.0f);
    container.setFillColor(sf::Color::Blue);

    view = new sf::View(sf::FloatRect(container.getPosition(), containerSize));
    view->setViewport(sf::FloatRect(container.getPosition(), sf::Vector2f(0.3f, 0.6f)));

    // do some controls to check that: textureFileDimension and singleTextureFiles are >= and the first is >= then the second
    load(textureFileNameString, textureFileDimension, singleTextureDimension);
}

TextureTiles::~TextureTiles()
{
    std::cout << "Destructor" << std::endl;
    cleanup();
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

    textures = std::move(other.textures);

    spritesOfTextures = std::move(other.spritesOfTextures);

    textureFile = other.textureFile;
    textureFileName = other.textureFileName;
    textureFileDim = other.textureFileDim;
    singleTextureDim = other.singleTextureDim;

    container = other.container;

    other.textureFile = nullptr;
}

TextureTiles &TextureTiles::operator=(const TextureTiles &other)
{
    std::cout << "Assignment" << std::endl;

    if (textureFileName != other.textureFileName)
    {
        cleanup();

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

    return *this;
}

TextureTiles &TextureTiles::operator=(TextureTiles &&other)
{
    std::cout << "Move Assigment" << std::endl;

    if (textureFileName != other.textureFileName)
    {

        cleanup();

        textures = std::move(other.textures);

        spritesOfTextures = std::move(other.spritesOfTextures);

        textureFile = other.textureFile;

        textureFileName = other.textureFileName;
        textureFileDim = other.textureFileDim;
        singleTextureDim = other.singleTextureDim;
        container = other.container;
    }

    other.textureFile = nullptr;

    return *this;
}

const void TextureTiles::update()
{
}

const void TextureTiles::draw(sf::RenderTarget &window) const
{
    window.setView(*view);
    window.draw(container);
    for (int i = 0; i < spritesOfTextures.size(); i++)
        window.draw(*spritesOfTextures[i]);
}

const void TextureTiles::load(const std::string textureFileNameString, const sf::Vector2f textureFileDimension, float singleTextureDimension)
{
    std::cout << "Load" << std::endl;

    if (textureFileNameString != textureFileName)
    {

        cleanup();

        textureFile = new sf::Image();
        textureFileName = textureFileNameString;
        textureFileDim = textureFileDimension;

        singleTextureDim = singleTextureDimension;

        textures = std::vector<sf::Texture *>();
        spritesOfTextures = std::vector<sf::Sprite *>();

        if (!(textureFile->loadFromFile(textureFileName)))
        {
            std::cout << "TEXTURES:: Failed to load  the texture" << std::endl;
        }
        else
        {
            std::cout << "successfully loaded" << std::endl;

            slice();

            // now my textures/spritesOfTextures are populated so I can arrange them and draw them inside the container
            arrangeTexturesInContainer();
        }
    }
}

const std::vector<sf::Texture *> &TextureTiles::getTextures() const
{
    return textures;
}
