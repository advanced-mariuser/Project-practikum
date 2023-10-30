#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition) {
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, bool &isMousePressed) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                onMouseClick(event.mouseButton, mousePosition);
                isMousePressed = !isMousePressed;
                break;
            default:
                break;
        }
    }
}

void setCatScale(sf::Sprite &cat, float widthMultiplier, float heightMultiplier) {
    sf::Vector2f targetSize(sf::VideoMode::getDesktopMode().height / 16, sf::VideoMode::getDesktopMode().height / 16);
    cat.setScale(
            targetSize.x / cat.getLocalBounds().width * widthMultiplier,
            targetSize.y / cat.getLocalBounds().height * heightMultiplier
    );
}

void updateCatPosition(const sf::Vector2f &mousePosition, sf::Sprite &cat, float dt, bool isMousePressed) {
    sf::Vector2f delta = mousePosition - cat.getPosition();
    float deltaLength;
    if (isMousePressed) {
        deltaLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    } else {
        deltaLength = 0;
    }

    const sf::Vector2f direction = {delta.x / deltaLength, delta.y / deltaLength};
    const float speed = 20.0f;
    if (deltaLength != 0) {
        cat.move(direction * speed * dt);
        if (delta.x >= 0) {
            setCatScale(cat, 1, 1);
        } else {
            setCatScale(cat, -1, 1);
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::Sprite &cat, sf::Sprite &pointer, sf::Clock &clock, bool isMousePressed) {
    const float dt = clock.restart().asSeconds();
    if (isMousePressed) {
        pointer.setPosition(mousePosition);
    }
    updateCatPosition(mousePosition, cat, dt, isMousePressed);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer, bool isMousePressed) {
    window.clear(sf::Color::White);
    window.draw(cat);
    if (isMousePressed) {
        window.draw(pointer);
    }
    window.display();
}

int main() {
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    bool isMousePressed = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
            "Cat", sf::Style::Default, settings);

    sf::Vector2f mousePosition;
    sf::Texture catTexture;
    if (!catTexture.loadFromFile("cat.png")) {
        std::wcerr << L"Failed to load cat image" << std::endl;
        exit(1);
    }

    sf::Texture pointerTexture;
    if (!pointerTexture.loadFromFile("red_pointer.png")) {
        std::wcerr << L"Failed to load pointer image" << std::endl;
        exit(1);
    }

    sf::Sprite pointer(pointerTexture);
    pointer.setOrigin(pointer.getLocalBounds().width / 2, pointer.getLocalBounds().height / 2);
    setCatScale(pointer, 1, 1);


    sf::Sprite cat(catTexture);
    cat.setOrigin(cat.getLocalBounds().width / 2, cat.getLocalBounds().height / 2);
    setCatScale(cat, 1, 1);


    cat.setPosition(
            WINDOW_WIDTH / 2,
            WINDOW_HEIGHT / 2
    );

    sf::Clock clock;

    while (window.isOpen()) {
        pollEvents(window, mousePosition, isMousePressed);
        update(mousePosition, cat, pointer, clock, isMousePressed);
        redrawFrame(window, cat, pointer, isMousePressed);
    }
}