#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class Grid
{

private:
    int width;
    int height;
    float cell_width;
    float cell_height;
    sf::Color *gridColor;
    sf::VertexArray *cells; // they have to be square

public:
    Grid(int width, int height, int cell_dimension, sf::Vector2f scale)
    {
        this->cell_width = cell_dimension * scale.y;
        this->cell_height = cell_dimension * scale.y;

        this->gridColor = new sf::Color(211, 211, 211, 130);
        this->cells = new sf::VertexArray(sf::PrimitiveType::Lines, (uint)(width * height * 8));

        // I have to initialize the vertexbuffer and draw the linex
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                this->addCellToTheBuffer(x, y);
            }
        }
    }

    // implement destructor ;P

    void addCellToTheBuffer(int starting_X, int starting_Y)
    {

        // top left vertex
        this->cells->append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, starting_Y * this->cell_height), *this->gridColor));
        //  top right vertex
        this->cells->append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, starting_Y * this->cell_height), *this->gridColor));

        //  top right vertex
        this->cells->append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, starting_Y * this->cell_height), *this->gridColor));
        // bottom right vertex
        this->cells->append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, (starting_Y * this->cell_height) + this->cell_height), *this->gridColor));

        // bottom right vertex
        this->cells->append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, (starting_Y * this->cell_height) + this->cell_height), *this->gridColor));
        // bottom left vertex
        this->cells->append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, (starting_Y * this->cell_height) + this->cell_height), *this->gridColor));

        // bottom left vertex
        this->cells->append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, (starting_Y * this->cell_height) + this->cell_height), *this->gridColor));
        // top left vertex
        this->cells->append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, starting_Y * this->cell_height), *this->gridColor));
    }

    // i set the texture to the cell starting from the top left corner and using the cell_dimension attribute
    void setCellTexture(const sf::Vector2i &cell)
    {
        this->cells[0][10].color = sf::Color::Red;
        // this->cells[1][0].color = sf::Color::Red;

        // this->cells[1][0].color = sf::Color::Red;
        // this->cells[1][1].color = sf::Color::Red;

        // this->cells[1][1].color = sf::Color::Red;
        // this->cells[0][1].color = sf::Color::Red;

        // this->cells[0][1].color = sf::Color::Red;
        // this->cells[0][0].color = sf::Color::Red;
    }

    void checkClickedCell(const sf::Vector2f mousePos)
    {
        std::cout << "hello" << std::endl;
        if (mousePos.x >= 0 && mousePos.x <= (this->cell_width * this->width) && mousePos.y >= 0 && mousePos.y <= (this->cell_height * this->height))
        {
            sf::Vector2i *cellNumber = new sf::Vector2i(static_cast<int>(mousePos.x / this->cell_width), static_cast<int>(mousePos.y / this->cell_height));
            std::cout << "cell (" << static_cast<int>(mousePos.x / this->cell_width) << ", " << static_cast<int>(mousePos.y / this->cell_height) << ")" << std::endl;
            this->setCellTexture(*cellNumber);
        }
    }

    // i remove the texture to the cell starting from the top left corner and using the cell_dimension attribute
    void
    removeTexture(sf::Vector2f top_left_point)
    {
    }

    void draw(sf::RenderWindow *target, sf::RenderStates states)
    {
        target->draw(*this->cells, states);
    }
};