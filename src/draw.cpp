#include "draw.hpp"

Draw::~Draw() {
    if (simThread) {
        delete simThread;
    }
}

Draw::Draw() : 
    tickRate(SIM_TICKRATE), 
    nextUpdate(0), 
    window(
        sf::VideoMode({
            WINDOW_WIDTH * WINDOW_SCALING, 
            WINDOW_HEIGHT * WINDOW_SCALING}), 
        "Sand",
        sf::Style::Titlebar | sf::Style::Close
    ),
    pixels(WINDOW_WIDTH*WINDOW_HEIGHT*4, 255),
    canvas(WINDOW_WIDTH, WINDOW_HEIGHT) {}

void Draw::update() {
    if (!addQueue.empty()) {
        AddMaterial action = addQueue[0];
        canvas.setMaterial(
            action.x / WINDOW_SCALING, 
            action.y / WINDOW_SCALING, 
            action.material
        );
        addQueue.pop_front();
    }
    canvas.update();
    canvas.setPixels(pixels);
}

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

void Draw::start() {
    window.setPosition(sf::Vector2i(0, 0));
    simThread = new thread(&Draw::loop, this);

    sf::Texture texture(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::Sprite sprite(texture);
    sprite.setPosition(sf::Vector2f(0,0));
    sprite.scale({ WINDOW_SCALING, WINDOW_SCALING });
    
    
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                keyPressedHandler();
            }
        }

        texture.update(pixels.data());

        window.draw(sprite);
        window.display();
    }
    simThread->join();
}

void Draw::mouseButtonPressedHandler() {
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        addQueue.emplace_back(position.x, position.y, currentMaterial);
    }
}

void Draw::keyPressedHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        currentMaterial = currentMaterial == Material::Sand ?
            Material::Water : Material::Sand;
    }
}