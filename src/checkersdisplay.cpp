#include "checkersdisplay.hpp"
#include <string>
using std::string;
#include <SFML/Graphics.hpp>


CheckersDisplay::CheckersDisplay(int width, int height, string title)
    :_window(sf::VideoMode(width, height), title)
{}

bool CheckersDisplay::isOpen() const {
    return _window.isOpen();
}
