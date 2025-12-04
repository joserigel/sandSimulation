#include "draw.hpp"

void Draw::update() {
    if (!addQueue.empty()) {
        AddMaterial action = addQueue[0];
        canvas.setMaterial(action.x, action.y, action.material);
        addQueue.pop_front();
    }
    canvas.update();
    canvas.setPixels(pixels);
}

Draw::~Draw() {
    if (simThread) {
        delete simThread;
    }
}

Draw::Draw() : 
    tickRate(DEFAULT_TICKRATE), 
    nextUpdate(0), 
    window(
        sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), 
        "Sand",
        sf::Style::Titlebar | sf::Style::Close
    ),
    pixels(DEFAULT_WINDOW_WIDTH*DEFAULT_WINDOW_HEIGHT*4),
    canvas(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT) {}

void Draw::loop() {
    while (window.isOpen()) {
        chrono::milliseconds cur = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
        );
        if (cur >= nextUpdate) {
            nextUpdate = cur + this->tickRate;

            mouseButtonPressedHandler();

            update();
        }
    }
}

void Draw::mouseButtonPressedHandler() {
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        addQueue.emplace_back(position.x, position.y, Material::Sand);
    }
}

void Draw::start() {
    window.setPosition(sf::Vector2i(0, 0));
    simThread = new thread(&Draw::loop, this);

    sf::Texture texture(sf::Vector2u(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_WIDTH));
    sf::Sprite sprite(texture);
    sprite.setPosition(sf::Vector2f(0,0));
    
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        texture.update(pixels.data());

        window.draw(sprite);
        window.display();
    }
    simThread->join();
}