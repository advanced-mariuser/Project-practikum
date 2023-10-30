#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 1000;
constexpr unsigned WINDOW_HEIGHT = 800;
constexpr float RADIUS = 200.f;

int main()
{
    sf::Vector2f speed = {50.f, 15.f};
    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {200.f, 80.f};
    sf::Clock clock;

    // Создаем окно с параметрами сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar Rose",
        sf::Style::Default, settings);

    // Объявляем фигуру, которая будет выглядеть как эллипс
    sf::ConvexShape ellipse;
    ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    // Инициализируем вершины псевдо-эллипса
    ellipse.setPointCount(pointCount);

    // Выполняем основной цикл программы
    while (window.isOpen())
    {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Расчет и установка вершин псевдо-эллипса
        sf::Vector2f center = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f};
        float angleStep = 2.f * M_PI / pointCount;
        const float deltaTime = clock.restart().asSeconds();
        static float angle = 0.f;
        float rotationSpeed = 0.5f;
        angle += rotationSpeed * deltaTime;

        float offsetX = std::cos(angle) * RADIUS;
        float offsetY = std::sin(angle) * RADIUS;

        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float currentAngle = angleStep * pointNo;
            float radius = 200.f * std::sin(6.f * currentAngle);
            sf::Vector2f point = {
                center.x + offsetX + radius * std::cos(currentAngle),
                center.y + offsetY + radius * std::sin(currentAngle)};
            ellipse.setPoint(pointNo, point);
        }

        // Рисование текущего состояния
        window.clear();
        window.draw(ellipse);
        window.display();
    }
}