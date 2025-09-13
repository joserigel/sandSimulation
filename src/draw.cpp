#include "draw.hpp"


sf::RenderWindow window;
sf::Font font("assets/JetBrainsMonoNL-Regular.ttf");
sf::Text debugText(font);

sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));
std::vector<std::uint8_t> pixels(WIDTH * HEIGHT * 4);

sf::Sprite sprite(texture);

void onKeyPressed(const sf::Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
        window.close();
    } 
}

void onMousePressed(const sf::Event::MouseButtonPressed& mousePressed) {
    const int x = mousePressed.position.x;
    const int y = mousePressed.position.y;
    
    if (mousePressed.button == sf::Mouse::Button::Left) {
        debugText.setString(std::to_string(x) + ", " + std::to_string(y));

        pixels.data();
    }
    
    texture.update(pixels.data());
    texture.update(window);
}

void onMouseReleased(const sf::Event::MouseButtonReleased& mouseReleased) {
    debugText.setString("");
}

void loop() {
    window.draw(debugText);
    window.draw(sprite);

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

    
    for (int i = 0; i < width * height * 4; i+=4) {
        pixels[i] = 255;
    }
    texture.update(pixels.data());
    sprite.setTexture(texture);

}

void destroy() {
}


void Draw::run() {
    init(WIDTH, HEIGHT);
    while (window.isOpen()) {
        window.clear();
        handleEvents();
        loop();
        window.display();
    }
    destroy();
}
