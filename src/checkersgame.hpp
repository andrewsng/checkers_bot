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
    void setActiveTile(int tile);
    void changeTurn();
    std::optional<bool> makeMove(Move move);

private:

    Board _board{};
    int _player{0};
    int _active{-1};
    std::vector<Move> _legalMoves{};
    bool _legalMovesCached{false};

};


#endif  // CHECKERSGAME_HPP
