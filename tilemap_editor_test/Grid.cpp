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
    sf::VertexArray *gridCells; // they have to be square
    sf::VertexArray *actualTextureCells;

public:
    Grid(int width, int height, int cell_dimension, sf::Vector2f scale)
    {
        this->cell_width = cell_dimension * scale.y;
        this->cell_height = cell_dimension * scale.y;

        this->gridColor = new sf::Color(211, 211, 211, 130);
        this->gridCells = new sf::VertexArray(sf::PrimitiveType::Lines, (uint)(width * height * 8));
        this->actualTextureCells = new sf::VertexArray(sf::PrimitiveType::Triangles, (uint)(width * height * 6));

        // I have to initialize the vertexbuffer and draw the linex
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                this->addCellToTheBuffer(*this->gridCells, x, y, *this->gridColor, this->gridCells->getPrimitiveType());
            }
        }
    }

    // implement destructor ;P

    void addCellToTheBuffer(sf::VertexArray &cells, int starting_X, int starting_Y, const sf::Color &color, const sf::PrimitiveType primitiveType)
    {

        switch (primitiveType)
        {

        case sf::PrimitiveType::Lines:
            // top left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, starting_Y * this->cell_height), color));
            //  top right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, starting_Y * this->cell_height), color));

            //  top right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, starting_Y * this->cell_height), color));
            // bottom right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));

            // bottom right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));
            // bottom left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));

            // bottom left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));
            // top left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, starting_Y * this->cell_height), color));
            break;

        case sf::PrimitiveType::Triangles:

            // TOP RIGHT TRIANGLE
            // top left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, starting_Y * this->cell_height), color));
            //  top right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, starting_Y * this->cell_height), color));
            // bottom right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));

            // BOTTOM LEFT TRIANGLE
            // top left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, starting_Y * this->cell_height), color));
            // bottom left vertex
            cells.append(sf::Vertex(sf::Vector2f(starting_X * this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));
            // bottom right vertex
            cells.append(sf::Vertex(sf::Vector2f((starting_X * this->cell_width) + this->cell_width, (starting_Y * this->cell_height) + this->cell_height), color));
            break;

        default:
            break;
        }
    }

    bool checkClickedCell(const sf::Vector2f mousePos)
    {

        if (mousePos.x >= 0 && mousePos.x <= (this->cell_width * this->width) && mousePos.y >= 0 && mousePos.y <= (this->cell_height * this->height))
        {
            return true;
        }
        return false;
    }

    // i set the texture to the cell starting from the top left corner and using the cell_dimension attribute
    void setCellTexture(const sf::Vector2f mousePos)
    {
        if (this->checkClickedCell(mousePos))
        {
            sf::Vector2i cell = sf::Vector2i(static_cast<int>(mousePos.x / this->cell_width), static_cast<int>(mousePos.y / this->cell_height));
            this->addCellToTheBuffer(*this->actualTextureCells, cell.x, cell.y, sf::Color::Red, this->actualTextureCells->getPrimitiveType());
        }
    }

    // i remove the texture to the cell starting from the top left corner and using the cell_dimension attribute
    void removeTexture(const sf::Vector2f mousePos)
    {
        if (this->checkClickedCell(mousePos))
        {
            sf::Vector2i cell = sf::Vector2i(static_cast<int>(mousePos.x / this->cell_width), static_cast<int>(mousePos.y / this->cell_height));
            // this has to be fixed, because it doesn't really remove the thing, it just adds a black layer on top (I THINK)
            this->addCellToTheBuffer(*this->actualTextureCells, cell.x, cell.y, sf::Color::White, this->actualTextureCells->getPrimitiveType());
        }
    }

    void draw(sf::RenderWindow *target, sf::RenderStates states)
    {
        target->draw(*this->gridCells, states);
        target->draw(*this->actualTextureCells, states);
    }
};