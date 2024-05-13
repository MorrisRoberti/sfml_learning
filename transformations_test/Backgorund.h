#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Background
{
private:
    // attributes
    int xAxis;
    int yAxis;

    sf::RectangleShape xAxisShape;
    sf::RectangleShape yAxisShape;

    sf::CircleShape unitCircle;

    sf::Color xAxisColor;
    sf::Color yAxisColor;

    // init
    void initVariables(sf::RenderWindow *target);

public:
    // constructor
    Background(sf::RenderWindow *target);
    ~Background();

    // getters
    const int getXAxis() const;
    const int getYAxis() const;

    const sf::Color &getXAxisColor() const;
    const sf::Color &getYAxisColor() const;

    const sf::Vector2i getOrigin() const;

    // setter
    void setXAxis(int yValue);
    void setYAxis(int xValue);

    void setXAxisColor(sf::Color color, int opacity);
    void setYAxisColor(sf::Color color, int opacity);

    // update
    void update();

    // render
    void render(sf::RenderWindow *target);
};
