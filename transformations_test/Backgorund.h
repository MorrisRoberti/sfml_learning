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

    sf::Color xAxisColor;
    sf::Color yAxisColor;

    // init
    void initVariables(sf::RenderWindow *target);

public:
    // constructor
    Background(sf::RenderWindow *target);
    ~Background();

    // methods
    void setXAxis(int yValue);
    void setYAxis(int xValue);

    void setXAxisColor(sf::Color color, int opacity);
    void setYAxisColor(sf::Color color, int opacity);

    int getXAxis();
    int getYAxis();

    sf::Color &getXAxisColor();
    sf::Color &getYAxisColor();

    // update
    void update();

    // render
    void render(sf::RenderWindow *target);
};
