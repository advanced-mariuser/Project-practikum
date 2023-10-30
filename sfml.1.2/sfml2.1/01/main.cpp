#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;

    sf::CircleShape ball(BALL_SIZE);
    ball.setPosition({10, 350});
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    const sf::Vector2f startPosition = ball.getPosition();
    float speedX = 100.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 22;
        const float dt = clock.restart().asSeconds();

        sf::Vector2f position = ball.getPosition();
        position.x += speedX * dt;
        position.y = startPosition.y + amplitudeY * std::sin(position.x / periodY);

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && speedX > 0)
        {
            speedX = -speedX;
        }
        if ((position.x < 0) && speedX < 0)
        {
            speedX = -speedX;
        }

        ball.setPosition(position);

        window.clear();
        window.draw(ball);
        window.display();
    }
}