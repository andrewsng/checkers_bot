#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "move.hpp"
#include <optional>
#include <SFML/Graphics.hpp>


class CheckersGame {

public:

    int getTurn() const { return _player; }
    void printBoard() const;
    void printRedMoves() const;
    void printBlackMoves() const;
    void drawBoard(sf::RenderWindow *window) const;
    void setActiveTile(int tile);
    void changeTurn();
    std::optional<bool> makeMove(Move move);

private:

    Board _board{};
    int _player{0};
    int _active{-1};

};


#endif  // CHECKERSGAME_HPP
