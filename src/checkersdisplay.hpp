#ifndef CHECKERSDISPLAY_HPP
#define CHECKERSDISPLAY_HPP

#include <string>
#include <SFML/Graphics.hpp>


class CheckersDisplay {

public:

    CheckersDisplay(int width, int height, std::string title);
    bool isOpen() const;

private:

    sf::RenderWindow _window;

};


#endif  // CHECKERSDISPLAY_HPP
