#include "simulation.hpp"

#include <iostream>

Canvas::Canvas(size_t width, size_t height) : 
    canvas(width, vector<Material>(height, Material::Air)) {

    srand(time(NULL));

}

void Canvas::update() {
    size_t width = canvas.size();
    size_t height = canvas[0].size();

    // Sand Gravity
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 1; j < height; j++) {
            if (canvas[i][j] == Material::Air) {
                continue;
            }

            Material bottomLeft = i > 0 ? canvas[i - 1][j - 1] : Material::Bedrock;
            Material bottomMid = canvas[i][j - 1];
            Material bottomRight = i < width - 1 ? canvas[i + 1][j - 1] : Material::Bedrock;

            if (bottomMid & (Material::Air | Material::Water)) {
                swap(canvas[i][j - 1], canvas[i][j]);
            } else if (bottomLeft == Material::Air && 
                bottomRight & (Material::Air | Material::Water)) {
                if (rand() % 100 < 50) {
                    swap(canvas[i - 1][j - 1], canvas[i][j]);
                } else {
                    swap(canvas[i + 1][j - 1], canvas[i][j]);
                }
            } else if (bottomRight & (Material::Air | Material::Water)) {
                swap(canvas[i + 1][j - 1], canvas[i][j]);
            } else if (bottomLeft & (Material::Air | Material::Water)) {
                swap(canvas[i - 1][j - 1], canvas[i][j]);
            }

            if (canvas[i][j] == Material::Sand && bottomMid == Material::Water) {
                swap(canvas[i][j - 1], canvas[i][j]);
            } else if (canvas[i][j] == Material::Water) {
                Material left = i > 0 ? canvas[i - 1][j] : Material::Bedrock;
                Material right = i < width - 1 ? canvas[i + 1][j] : Material::Bedrock;

                if (left == Material::Air && right == Material::Air) {
                    if (rand() % 100 < 50) {
                        swap(canvas[i - 1][j], canvas[i][j]);
                    } else {
                        swap(canvas[i + 1][j], canvas[i][j]);
                    }
                } else if (left == Material::Air && rand() % 100 < 50) {
                    swap(canvas[i - 1][j], canvas[i][j]);
                } else if (right == Material::Air && rand() % 100 < 50) {
                    swap(canvas[i + 1][j], canvas[i][j]);
                }
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
                case Material::Water:
                    pixels[coords + 0] = 3;
                    pixels[coords + 1] = 171;
                    pixels[coords + 2] = 240;
                    pixels[coords + 3] = 255;
                    break;
            }
        }
    }
    
}

void Canvas::setMaterial(size_t x, size_t y, Material material) {
    size_t width = canvas.size();
    size_t height = canvas[0].size();
    if (x < width && y < height) {
        y = height - 1 - y;
        canvas[x][y] = material;
    }
    
}