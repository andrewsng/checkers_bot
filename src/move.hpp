#ifndef MOVE_HPP
#define MOVE_HPP

#include "board.hpp"
#include <utility>
#include <optional>


class Move {

public:

    using Tile = Board::Tile;
    using Diff = Tile;
    Move(Tile start, Tile end);
    Tile getStart() const;
    Tile getEnd() const;
    bool isAJump() const;
    std::optional<Move::Tile> getCaptured() const;

private:

    Diff tileDiff() const; 

    Tile _start;
    Tile _end;

};

bool operator==(const Move &lhs, const Move &rhs);


#endif  // MOVE_HPP
