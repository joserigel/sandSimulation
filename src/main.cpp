#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Window test");
    window.setPosition(sf::Vector2i(0, 0));



    while (window.isOpen()) {
        window.display();
    }
}