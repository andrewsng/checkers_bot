#ifndef MOVE_HPP
#define MOVE_HPP

#include "board.hpp"
#include <utility>


class Move {

public:

    using Tile = Board::Tile;
    Move(Tile start, Tile end)
        :_startEnd(start, end)
    {}
    Tile getStart() const { return _startEnd.first; }
    Tile getEnd() const { return _startEnd.second; }

private:

    std::pair<Tile, Tile> _startEnd;

};


#endif  // MOVE_HPP
