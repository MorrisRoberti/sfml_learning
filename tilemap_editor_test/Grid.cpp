#include <vector>
#include <SFML/Graphics.hpp>

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
        this->cell_height = cell_dimension * scale.x;
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
    void setTexture(sf::Texture &texture, sf::Vector2f top_left_point) {}

    // i remove the texture to the cell starting from the top left corner and using the cell_dimension attribute
    void removeTexture(sf::Vector2f top_left_point) {}

    void draw(sf::RenderWindow *target, sf::RenderStates states)
    {

        target->draw(*this->cells, states);
    }
};