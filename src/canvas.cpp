#include "canvas.hpp"

Canvas::Canvas(unsigned short width, unsigned short height) {
    this->data = new unsigned char[width * height];
}

Canvas::~Canvas(void) {
    delete[] this->data;
}