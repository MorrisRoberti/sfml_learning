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

    this->unitCircle.setPosition(this->yAxis, this->xAxis);
    this->unitCircle.setRadius(200);
    this->unitCircle.setOrigin(this->unitCircle.getLocalBounds().width / 2, this->unitCircle.getGlobalBounds().height / 2);
    this->unitCircle.setOutlineThickness(2);
    this->unitCircle.setOutlineColor(this->xAxisColor);
    this->unitCircle.setFillColor(sf::Color::Transparent);
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
const int Background::getXAxis() const
{
    return this->xAxis;
}
const int Background::getYAxis() const
{
    return this->yAxis;
}

const sf::Color &Background::getXAxisColor() const
{
    return this->xAxisColor;
}
const sf::Color &Background::getYAxisColor() const
{
    return this->yAxisColor;
}

const sf::Vector2i Background::getOrigin() const
{
    return sf::Vector2i(this->yAxis, this->xAxis);
}

const sf::CircleShape Background::getUnitCircle() const
{
    return this->unitCircle;
}
// update
void Background::update() {}

// render
void Background::render(sf::RenderWindow *target)
{
    target->draw(this->xAxisShape);
    target->draw(this->yAxisShape);
    target->draw(this->unitCircle);
}