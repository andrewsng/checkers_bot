#ifndef MOVE_HPP
#define MOVE_HPP

#include "board.hpp"
#include <utility>


class Move {

public:

    using Tile = Board::Tile;
    Move(Tile start, Tile end)
        :_start(start), _end(end)
    {}
    Move(Tile start, Tile jump, Tile captured)
        :_start(start), _end(jump), _captured(captured)
    {}
    Tile getStart() const { return _start; }
    Tile getEnd() const { return _end; }
    Tile getCaptured() const { return _captured; }
    bool isAJump() const { return _captured != 32; }

private:

    Tile _start;
    Tile _end;
    Tile _captured{32};

};


#endif  // MOVE_HPP
