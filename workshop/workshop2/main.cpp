#include <SFML/Graphics.hpp>
#include <cmath>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition({350,300});

    arrow.setFillColor(sf::Color::Yellow);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(2);

    arrow.setPointCount(7);
    arrow.setPoint(0, { -60, -20 });
    arrow.setPoint(1, { 0, -20 });
    arrow.setPoint(2, { 0, -50 });
    arrow.setPoint(3, { 50, 0 });
    arrow.setPoint(4, { 0, 50 });
    arrow.setPoint(5, { 0, 20 });
    arrow.setPoint(6, { -60, 20 });
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                onMouseMove(event.mouseMove, mousePosition);
                break;
            default:
                break;
        }
    }
}

void updateArrow(const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, float dt, float angle)
{
    float rotation;
    float predRotation = arrow.getRotation();

    if (angle < 0)
    {
        angle += 360;
    }
    if (std::abs(360 - predRotation + angle) > 360)
    {
        angle -= 360;
    }
    if (std::abs(360 - predRotation + angle) > std::abs(angle - predRotation))
    {
        rotation = -90 * dt;
    }
    else
    {
        rotation = 90 * dt;
    }
    arrow.rotate(rotation);
    const sf::Vector2f deltaPosition = mousePosition - arrow.getPosition();
    const float deltaLength = std::sqrt(deltaPosition.x * deltaPosition.x + deltaPosition.y * deltaPosition.y);
    if (deltaLength != 0)
    {
        const sf::Vector2f direction = { deltaPosition.x / deltaLength, deltaPosition.y / deltaLength };
        const float speed = 20.0f;
        arrow.move(direction * speed * dt);
    }
}

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, sf::Clock &clock)
{
    const float dt = clock.restart().asSeconds();
    const sf::Vector2f deltaRotation = mousePosition - arrow.getPosition();
    float angle = toDegrees(atan2(deltaRotation.y, deltaRotation.x));

    updateArrow(mousePosition, arrow, dt, angle);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow)
{
    window.clear(sf::Color::White);
    window.draw(arrow);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Arrow follows mouse", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    }
}
