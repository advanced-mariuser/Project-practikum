#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

struct Eye {
    sf::ConvexShape pupil;
    sf::ConvexShape sclera;
    sf::Vector2f position;
    float rotation = 0;
};

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidian(float radius, float angle) {
    return {
            radius * std::cos(angle),
            radius * std::sin(angle)};
}

// Переводит радианы в градусы
float toDegrees(float radians) {
    return float(double(radians) * 180.0 / M_PI);
}

// Обновляет позиции и повороты частей стрелки согласно текущему состоянию стрелки.
void updateEye(Eye &eye, sf::Vector2f mousePosition) {
    std::cout << "Eye angle: " << toDegrees(eye.rotation) << std::endl;
    double radius = sqrt((mousePosition.x - eye.position.x) * (mousePosition.x - eye.position.x) + (mousePosition.y - eye.position.y) * (mousePosition.y - eye.position.y));
    std::cout << radius << std::endl;
    sf::Vector2f pupilOffset;
    if (radius <= 50)
    {
        pupilOffset = toEuclidian(float(radius), eye.rotation);
    }
    else
    {
        pupilOffset = toEuclidian(50, eye.rotation);
    }
    std::cout << "Offset: " << pupilOffset.x << " " << pupilOffset.y << std::endl;
    eye.pupil.setPosition(eye.position + pupilOffset);
    eye.pupil.setRotation(toDegrees(eye.rotation));
}

// Инициализирует фигуру-глаза
void initEye(Eye &eye, float x, float y, sf::Vector2f radius, int pointCount, sf::Vector2f scleraRadius) {
    eye.pupil.setPosition({x, y});
    eye.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    eye.pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo) {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
                radius.x * std::sin(angle),
                radius.y * std::cos(angle)};
        eye.pupil.setPoint(pointNo, point);
    }

    eye.position = {x, y};

    eye.sclera.setPosition({x, y});
    eye.sclera.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye.sclera.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo) {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
                scleraRadius.x * std::sin(angle),
                scleraRadius.y * std::cos(angle)};
        eye.sclera.setPoint(pointNo, point);
    }
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition) {
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
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

// Обновляет фигуры, указывающие на мышь
void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye) {
    const sf::Vector2f leftDelta = mousePosition - leftEye.position;
    leftEye.rotation = atan2(leftDelta.y, leftDelta.x);
    updateEye(leftEye, mousePosition);

    const sf::Vector2f rightDelta = mousePosition - rightEye.position;
    rightEye.rotation = atan2(rightDelta.y, rightDelta.x);
    updateEye(rightEye, mousePosition);
}


// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye) {
    window.clear();
    window.draw(leftEye.sclera);
    window.draw(rightEye.sclera);
    window.draw(leftEye.pupil, sf::RenderStates(sf::BlendAlpha));
    window.draw(rightEye.pupil, sf::RenderStates(sf::BlendAlpha));
    window.display();
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

    sf::Vector2f eyeRadius = {20.f, 20.f};

    Eye leftEye;
    float leftEyeX = 200;
    float leftEyeY = 200;

    Eye rightEye;
    float rightEyeX = 400;
    float rightEyeY = 200;
    sf::Vector2f mousePosition;

    initEye(leftEye, leftEyeX, leftEyeY, eyeRadius, pointCount, scleraRadius);
    initEye(rightEye, rightEyeX, rightEyeY, eyeRadius, pointCount, scleraRadius);

    while (window.isOpen()) {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}
