#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "move.hpp"
#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>


class CheckersGame {

public:

    int getTurn() const { return _player; }
    void printBoard() const;
    void printRedMoves() const;
    void printBlackMoves() const;
    void drawBoard(sf::RenderWindow *window) const;
    std::vector<Move> getLegalMoves() const;
    void setActiveTile(Board::Tile tile);
    void changeTurn();
    bool makeMove(Move move);
    void makeBotMove();

private:

    Board _board{};
    int _player{0};
    Board::Tile _active{32};
    std::vector<Move> _legalMoves{};
    bool _legalMovesCached{false};

};


#endif  // CHECKERSGAME_HPP
