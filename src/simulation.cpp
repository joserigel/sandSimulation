#include "simulation.hpp"

#include <iostream>

Canvas::Canvas(size_t width, size_t height) : 
    canvas(width, vector<Material>(height, Material::Air)) {

    srand(time(NULL));
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height - 1; j++) {
            canvas[i][j] = rand() % 100 < 10 ? Material::Sand : Material::Air;
        }
    }

}

void Canvas::update() {
    size_t width = canvas.size();
    size_t height = canvas[0].size();

    // Sand Gravity
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 1; j < height - 1; j++) {
            Material bottomLeft = i > 0 ? canvas[i - 1][j - 1] : Material::Bedrock;
            Material bottomMid = canvas[i][j - 1];
            Material bottomRight = i < width - 1 ? canvas[i + 1][j - 1] : Material::Bedrock;

            if (bottomMid == Material::Air) {
                swap(canvas[i][j - 1], canvas[i][j]);
            } else if (bottomLeft == Material::Air && bottomRight == Material::Air) {
                if (rand() % 100 < 50) {
                    swap(canvas[i - 1][j - 1], canvas[i][j]);
                } else {
                    swap(canvas[i + 1][j - 1], canvas[i][j]);
                }
            } else if (bottomRight == Material::Air) {
                swap(canvas[i + 1][j - 1], canvas[i][j]);
            } else if (bottomLeft == Material::Air) {
                swap(canvas[i - 1][j - 1], canvas[i][j]);
            }
        }
    }


}

void Canvas::setPixels(vector<uint8_t>& pixels) {
    size_t width = canvas.size();
    size_t height = canvas[0].size();

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            int x = i;
            int y = height - 1 - j;
            size_t coords = ((y * width) + x) * 4;
            switch (canvas[i][j]) {
                case Material::Air:
                    pixels[coords + 0] = 0;
                    pixels[coords + 1] = 0;
                    pixels[coords + 2] = 0;
                    pixels[coords + 3] = 255;
                    break;
                case Material::Sand:
                    pixels[coords + 0] = 255;
                    pixels[coords + 1] = 204;
                    pixels[coords + 2] = 85;
                    pixels[coords + 3] = 255;
                    break;
            }
        }
    }
    
}

void Canvas::setMaterial(size_t x, size_t y, Material material) {
    size_t height = canvas[0].size();
    y = height - 1 - y;
    canvas[x][y] = material;
}