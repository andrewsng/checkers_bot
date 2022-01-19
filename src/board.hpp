#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>


class Board {

public:

    using Tile = std::string::size_type;
    Board() = default;

private:

    std::string _data{"bbbbbbbbbbbb        rrrrrrrrrrrr"};

};


#endif  // BOARD_HPP
