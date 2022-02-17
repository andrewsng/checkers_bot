#ifndef CHECKERSDISPLAY_HPP
#define CHECKERSDISPLAY_HPP

#include "board.hpp"
#include <string>
#include <SFML/Graphics.hpp>


class CheckersDisplay {

public:

    CheckersDisplay(int width, int height, std::string title);
    bool isOpen() const;
    void handleInputs(Board &game);
    void drawBoard(const Board &game);

private:

    sf::RenderWindow _window;
    Board::Tile _prevActive{32};
    Board::Tile _currActive{32};

};


#endif  // CHECKERSDISPLAY_HPP
