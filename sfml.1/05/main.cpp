#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::ConvexShape triangle;
    triangle.setFillColor(sf::Color(0xFF, 0x80, 0));
    triangle.setPosition({200, 120});
    triangle.setPointCount(3);
    triangle.setPoint(0, {50, -20});
    triangle.setPoint(1, {50, 20});
    triangle.setPoint(2, {-100, 0});

    sf::ConvexShape trapeze;
    triangle.setFillColor(sf::Color(0xFF, 0, 0xFF));
    triangle.setPosition({400, 300});
    triangle.setPointCount(4);
    triangle.setPoint(0, {-90, 0});
    triangle.setPoint(1, {+90, 0});
    triangle.setPoint(2, {+120, 60});
    triangle.setPoint(3, {-120, 60});

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Convex Shapes");
    window.clear();
    window.draw(triangle);
    window.draw(trapeze);
    window.display();

    sf::sleep(sf::seconds(5));
}