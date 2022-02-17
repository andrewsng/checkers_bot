#ifndef MOVE_HPP
#define MOVE_HPP

#include "board.hpp"
#include <vector>
#include <utility>
#include <optional>
#include <initializer_list>


class Move {

public:

    using Tile = Board::Tile;
    using Diff = Tile;
    Move(std::initializer_list<Tile> tileList);
    Tile getStart() const;
    Tile getEnd() const;
    bool isAJump() const;
    std::vector<Tile> getCaptured() const;

    std::vector<Tile> tiles;

private:

    Diff tileDiff(Tile t0, Tile t1) const; 

};

bool operator==(const Move &lhs, const Move &rhs);


#endif  // MOVE_HPP
