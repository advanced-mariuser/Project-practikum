#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({800, 600});
    shape1.setPosition({0, 0});
    shape1.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({20, 560});
    shape2.setPosition({20, 20});
    shape2.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({100, 20});
    shape3.setPosition({20, 20});
    shape3.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({20, 560});
    shape4.setPosition({120, 20});
    shape4.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({20, 560});
    shape5.setPosition({180, 20});
    shape5.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({120, 20});
    shape6.setPosition({180, 20});
    shape6.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({20, 560});
    shape7.setPosition({340, 20});
    shape7.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape7);

    sf::CircleShape shape8(120);
    shape8.setPosition({340, 20});
    shape8.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape8);

    sf::CircleShape shape9(100);
    shape9.setPosition({360, 40});
    shape9.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape9);

    window.display();

    sf::sleep(sf::seconds(5));
}