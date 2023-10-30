#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

void drawArrow(sf::RenderWindow &window)
{
    window.clear();

    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setPosition({0, 0});
    background.setSize({800, 600});

    sf::ConvexShape arrow;
    arrow.setPosition({350,300});
    arrow.setFillColor(sf::Color::Yellow);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(2);
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, 0});
    arrow.setPoint(1, {0, -50});
    arrow.setPoint(2, {-20, -50});
    arrow.setPoint(3, {+20, -100});
    arrow.setPoint(4, {+60, -50});
    arrow.setPoint(5, {+40, -50});
    arrow.setPoint(6, {+40, 0});

    window.draw(background);
    window.draw(arrow);
    window.display();

    sf::sleep(sf::seconds(5));
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main() {
    constexpr int pointCount = 200;
    const sf::Vector2f scleraRadius = {80.f, 200.f};

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
            "Arrow follows mouse", sf::Style::Default, settings);

    drawArrow(window);
}
