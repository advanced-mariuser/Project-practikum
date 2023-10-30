#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({420, 1020}), "Rectangles and circle");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({400, 1000});
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape1);

    sf::CircleShape shape2(150);
    shape2.setPosition({60, 670});
    shape2.setFillColor(sf::Color(0x00, 0x8D, 0x0F));
    window.draw(shape2);

    sf::CircleShape shape3(150);
    shape3.setPosition({60, 350});
    shape3.setFillColor(sf::Color(0xFF, 0xCC, 0x26));
    window.draw(shape3);

    sf::CircleShape shape4(150);
    shape4.setPosition({60, 30});
    shape4.setFillColor(sf::Color(0xF2, 0x0, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}