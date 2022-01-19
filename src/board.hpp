#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>


class Board {

public:

    using Tile = std::string::size_type;
    Board() = default;
    std::vector<Tile> getBlackPositions() const;
    bool onEvenRow(Tile tile) const;
    bool onLeftSide(Tile tile) const;
    bool onRightSide(Tile tile) const;

private:

    std::string _data{"bbbbbbbbbbbb        rrrrrrrrrrrr"};

};


#endif  // BOARD_HPP
