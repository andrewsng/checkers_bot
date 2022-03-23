#ifndef CHECKERSDISPLAY_HPP
#define CHECKERSDISPLAY_HPP

#include "board.hpp"
#include "move.hpp"
#include <string>
#include <SFML/Graphics.hpp>


class CheckersDisplay {

public:

    CheckersDisplay(int width, int height, std::string title);
    bool isOpen() const;
    Board::Tile getPrevSelected() const;
    Board::Tile getCurrSelected() const;
    void handleInputs(Board &game);
    void drawBoard(const Board &game, int player);
    void resetSelected();
    void setPrevMove(Move prevMove);

private:

    sf::RenderWindow _window;
    Board::Tile _prevActive{32};
    Board::Tile _currActive{32};
    Move _prevMove{32, 32};

};


#endif  // CHECKERSDISPLAY_HPP
