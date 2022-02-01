#ifndef MOVE_HPP
#define MOVE_HPP

#include "board.hpp"
#include <utility>
#include <optional>


class Move {

public:

    using Tile = Board::Tile;
    using Diff = Tile;
    Move(Tile start, Tile end, int player);
    Tile getStart() const { return _start; }
    Tile getEnd() const { return _end; }
    int getPlayer() const { return _player; }
    bool isAJump() const;
    bool isAPromotion() const;
    std::optional<Move::Tile> getCaptured() const;

private:

    Diff tileDiff() const; 

    Tile _start;
    Tile _end;
    int _player;

};

bool operator==(const Move &lhs, const Move &rhs);


#endif  // MOVE_HPP
