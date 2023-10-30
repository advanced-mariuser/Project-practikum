#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Cat", sf::Style::Default, settings);

    sf::Texture catTexture;
    if (!catTexture.loadFromFile("cat.png"))
    {
        std::wcerr << L"Failed to load cat image" << std::endl;
        exit(1);
    }

    sf::Sprite cat(catTexture);
    cat.setPosition(
            WINDOW_WIDTH / 2,
            WINDOW_HEIGHT / 2
    );
    sf::Vector2f targetSize(70, 70);

    cat.setScale(
            targetSize.x / cat.getLocalBounds().width,
            targetSize.y / cat.getLocalBounds().height);

    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setPosition({0, 0});
    background.setSize({800, 600});

    window.clear();
    window.draw(background);
    window.draw(cat);
    window.display();

    sf::sleep(sf::seconds(5));
}