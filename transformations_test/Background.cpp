#include "Backgorund.h"

// constructor / destructor
Background::Background(sf::RenderWindow *target)
{
    this->initVariables(target);
}

Background::~Background() {}

void Background::initVariables(sf::RenderWindow *target)
{
    this->xAxis = target->getSize().y / 2;
    this->yAxis = target->getSize().x / 2;

    this->xAxisColor = sf::Color(255, 0, 0, 100);
    this->yAxisColor = this->xAxisColor;

    this->xAxisShape = sf::RectangleShape(sf::Vector2f(target->getSize().x, 2));
    this->xAxisShape.setFillColor(this->xAxisColor);
    this->xAxisShape.setPosition(0, xAxis);

    this->yAxisShape = sf::RectangleShape(sf::Vector2f(2, target->getSize().y));
    this->yAxisShape.setFillColor(this->yAxisColor);
    this->yAxisShape.setPosition(yAxis, 0);
}

// setters
void Background::setXAxis(int yValue)
{
    this->xAxis = yValue;
}
void Background::setYAxis(int xValue)
{
    this->yAxis = xValue;
}

void Background::setXAxisColor(sf::Color color, int opacity)
{
    if (opacity < 0 || opacity > 255)
        std::cout << "opacity must be included in [0, 255]" << std::endl;
    else
        this->xAxisColor = color;
}
void Background::setYAxisColor(sf::Color color, int opacity)
{
    if (opacity < 0 || opacity > 255)
        std::cout << "opacity must be included in [0, 255]" << std::endl;
    else
        this->xAxisColor = color;
}

// getters
int Background::getXAxis()
{
    return this->xAxis;
}
int Background::getYAxis()
{
    return this->yAxis;
}

sf::Color &Background::getXAxisColor()
{
    return this->xAxisColor;
}
sf::Color &Background::getYAxisColor()
{
    return this->yAxisColor;
}

// update
void Background::update() {}

// render
void Background::render(sf::RenderWindow *target)
{
    target->draw(this->xAxisShape);
    target->draw(this->yAxisShape);
}