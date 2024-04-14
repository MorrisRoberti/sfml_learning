#include <iostream>
#include "Game.h"

// Private Methods

void Game::initVariables()
{
    this->window = nullptr;

    // Game Logic
    this->paused = true;
    this->endGame = false;
    this->points = 0;
    this->health = 30;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "My First Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initBackground()
{
    // Endgame background loading
    if (!this->textureBackgroundEndGame.loadFromFile("assets/end_game_bg.png"))
    {
        std::cout << "ERROR::GAME::INITBACKGROUND: Endgame background texture not loaded correctly" << std::endl;
    }

    // Ingame background loading
    if (!this->textureBackground.loadFromFile("assets/background.png"))
    {
        std::cout << "ERROR::GAME::INITBACKGROUND: Background texture not loaded correctly" << std::endl;
    }
    this->spriteBackground.setTexture(this->textureBackground);
    this->spriteBackground.setScale(1.5f, 1.9f);
    this->spriteBackground.setPosition(0.f, 0.f);
}

void Game::initEmemies()
{
    if (!this->enemyTexture.loadFromFile("assets/enemy.png"))
    {
        std::cout << "ERROR::GAME::INITENEMIES: Enemies texture not loaded correctly" << std::endl;
    }
    this->enemy.setTexture(this->enemyTexture);
    this->enemy.setPosition(sf::Vector2f(0.f, 0.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("assets/pixel_art_font.ttf"))
    {
        std::cout << "ERROR::GAM::INITFONTS: Font not loaded correctly" << std::endl;
    }
}

void Game::initTexts()
{
    // Title
    this->title.setString("Catch the bees");
    this->title.setFont(this->font);
    this->title.setCharacterSize(64);
    this->title.setFillColor(sf::Color::White);
    this->title.setPosition(this->window->getSize().x / 2 - this->title.getCharacterSize() * 4, this->window->getSize().y / 2 - this->title.getCharacterSize());

    // Other Text
    this->text.setCharacterSize(48);
    this->text.setFont(this->font);
    this->text.setPosition(5.f, 0.f);
    this->text.setFillColor(sf::Color::White);
}

// Constructor / Destructor

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initBackground();
    this->initFonts();
    this->initTexts();
    this->initEmemies();
}

Game::~Game()
{
    delete this->window;
}

// Methods

void Game::spawnEnemy()
{
    /*
    @return void

        Spawns enemies and sets theri colors and positions.

        - Sets a random position.
        - Sets a random color.
        - Adds enemy to the vector.
    */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyTexture.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemyTexture.getSize().y)));

    // Spawn the enemy
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
    // event polling
    while (this->window->pollEvent(event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            else if (this->event.key.code == sf::Keyboard::Return)
            {
                this->paused = false;
            }
            break;
        }
    }
}

void Game::updateMousePositions()
{
    /*
    @return void

        Updates the mouse positions.

        - Mouse positions relative to window (Vector2i)
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    if (this->endGame == false)
    {

        if (this->enemies.size() < this->maxEnemies)
        {
            /*
            @return void

                Updates the enemy spawn timer and spawns enemies when the total
                amount of enemies is smaller than the maximum.
                Moves the enemies downwards.
                Removes the enemies at the edge of the screen.
            */

            if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
            {
                // Spawn enemy and reset the timer
                this->spawnEnemy();
                this->enemySpawnTimer = 0.f;
            }
            else
                this->enemySpawnTimer += 1.f;
        }

        // Moving and updating enemies
        for (int i = 0; i < this->enemies.size(); i++)
        {
            bool deleted = false;
            this->enemies[i].move(0.f, 3.f);

            if (this->enemies[i].getPosition().y > this->window->getSize().y)
            {
                this->enemies.erase(this->enemies.begin() + i); // removes from the vector the i-th enemy

                this->health -= 1;
            }
        }

        // Check if clicked upon
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->mouseHeld == false)
            {
                this->mouseHeld = true;
                bool deleted = false;
                for (int i = 0; i < this->enemies.size() && deleted == false; i++)
                {

                    if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                    {
                        // Delete the enemy
                        deleted = true;
                        this->enemies.erase(this->enemies.begin() + i); // removes from the vector the i-th enemy

                        // Gain points
                        this->points += 1;
                    }
                }
            }
        }
        else
        {
            this->mouseHeld = false;
        }
    }
}

void Game::updateText()
{

    if (this->endGame == true)
    {

        std::stringstream ss;
        ss << "Game Over" << std::endl
           << "Points: " << this->points;

        this->text.setString(ss.str());
        this->text.setPosition((this->window->getSize().x / 2) - 150, (this->window->getSize().y / 2) - 150);
    }
    else
    {

        std::stringstream ss;

        ss << "Points: " << this->points << std::endl
           << "Health: " << this->health;
        this->text.setString(ss.str());
    }
}

void Game::updateBackground()
{
    if (this->endGame == true)
    {
        this->spriteBackground.setTexture(this->textureBackgroundEndGame);
    }
}

void Game::update()
{

    this->pollEvents();

    if (this->paused == false)
    {

        this->updateMousePositions();

        this->updateBackground();

        this->updateText();

        this->updateEnemies();
    }

    // endGame condition
    if (this->health <= 0)
        this->endGame = true;
}

void Game::renderEnemies()
{
    if (this->endGame == false)
    { // Rendering all the enemies
        for (auto &e : this->enemies)
        {
            this->window->draw(e);
        }
    }
}

void Game::renderBackground()
{
    this->window->draw(this->spriteBackground);
}

void Game::renderText(sf::RenderTarget &target)
{
    if (this->paused == true)
    {
        target.draw(this->title);
    }
    target.draw(this->text);
}

void Game::render()
{
    /*
    @return void

        Renders the game objects.

        - clears old frame
        - render objects
        - display frame in window
    */

    this->window->clear();

    // Draw Game

    this->renderBackground();

    this->renderEnemies();

    this->renderText(*this->window);
    this->window->display();
}

const bool Game::windowIsOpen() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}
