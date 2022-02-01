#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>


class Move;

class Board {

public:

    using Tile = std::string::size_type;
    Board() = default;
    std::vector<Tile> getRedPositions() const;
    std::vector<Tile> getBlackPositions() const;
    static bool onEvenRow(Tile tile);
    static bool onLeftSide(Tile tile);
    static bool onRightSide(Tile tile);
    bool isKing(Tile tile) const;
    bool isOccupied(Tile tile) const;
    bool isOutOfBounds(Tile tile) const;
    bool isOpponent(Tile tile, int player) const;
    bool isPromotionRow(Tile tile, int player) const;
    bool isPromotion(const Move &move);
    char symbolOn(Tile tile) const;
    void updateBoard(const Move &move);

private:

    std::string _data{"bbbbbbbbbbbb        rrrrrrrrrrrr"};
    // std::string _data{"Rbbb   r       r   rb         r "};

};


#endif  // BOARD_HPP
