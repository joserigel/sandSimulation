#include "draw.hpp"

sf::RenderWindow window;
sf::Font font("assets/JetBrainsMonoNL-Regular.ttf");
sf::Text debugText(font);

void onKeyPressed(const sf::Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
        window.close();
    } 
}

void onMousePressed(const sf::Event::MouseButtonPressed& mousePressed) {
    if (mousePressed.button == sf::Mouse::Button::Left) {
        debugText.setString(std::to_string(mousePressed.position.x) + ", " + std::to_string(mousePressed.position.y));
    }
}

void onMouseReleased(const sf::Event::MouseButtonReleased& mouseReleased) {
    debugText.setString("");
}

void loop() {
    window.draw(debugText);
}

void handleEvents() {
    window.handleEvents(
        onKeyPressed,
        onMousePressed,
        onMouseReleased
    );
}

void init(unsigned int width, unsigned int height) {
    window = sf::RenderWindow(sf::VideoMode({width, height}), "Sand Simulation");
    window.setPosition(sf::Vector2i(0, 0));
}

void destroy() {
}


void Draw::run() {
    init(800, 800);
    while (window.isOpen()) {
        window.clear();
        handleEvents();
        loop();
        window.display();
    }
    destroy();
}
