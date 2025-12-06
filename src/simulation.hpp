#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Material {
    Air     = 1,
    Sand    = 2,
    Water   = 4,
    Bedrock = 8
};

class Canvas {
    private:
        std::vector<std::vector<Material>> canvas;
    public:
        Canvas(size_t width, size_t height);

        void update();
        void setPixels(vector<uint8_t>& pixels);
        void setMaterial(size_t x, size_t y, Material material);
};

#endif