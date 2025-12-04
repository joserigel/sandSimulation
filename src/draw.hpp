#ifndef DRAW_HPP
#define DRAW_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <deque>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "simulation.hpp"
using namespace std;

#define DEFAULT_TICKRATE 10
#define DEFAULT_WINDOW_WIDTH 300
#define DEFAULT_WINDOW_HEIGHT 200
#define DEFAULT_TICK_RATE 50

struct AddMaterial {
    size_t x;
    size_t y;
    Material material;

    AddMaterial(size_t x, size_t y, Material material) {
        this->x = x;
        this->y = y;
        this->material = material;
    }
};

class Draw {
    private:
        void mouseButtonPressedHandler();

        thread* simThread = NULL;
        chrono::milliseconds nextUpdate;
        chrono::milliseconds tickRate;

        deque<AddMaterial> addQueue;

        sf::RenderWindow window;
        Canvas canvas;
        vector<uint8_t> pixels;

        void loop();
        void update();
    public:
        void start();
        Draw();
        ~Draw();
};

#endif