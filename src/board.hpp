#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include <array>
#include <optional>
#include <stack>
#include <utility>
#include <cstddef>


class Move;

class Board {

public:

    using Tile = std::size_t;
    Board() = default;
    std::vector<Tile> getRedPositions() const;
    std::vector<Tile> getBlackPositions() const;
    static bool onEvenRow(Tile tile);
    static bool onLeftSide(Tile tile);
    static bool onRightSide(Tile tile);
    bool isRed(Tile tile) const;
    bool isBlack(Tile tile) const;
    bool isKing(Tile tile) const;
    bool isOccupied(Tile tile) const;
    bool isOutOfBounds(Tile tile) const;
    bool isOpponent(Tile tile, int player) const;
    bool isPromotionRow(Tile tile, int player) const;
    bool isPromotion(const Move &move, int player) const;
    char symbolOn(Tile tile) const;
    std::optional<Move> getBotMove(int player) const;
    void makeMove(const Move &move, int player);

private:

    static const Tile _numTiles = 32;
    std::array<char, _numTiles+1> _data{"bbbbbbbbbbbb        rrrrrrrrrrrr"};
    // std::array<char, _numTiles+1> _data{"Rbbb   r       r   rb         r "};
    // std::array<char, _numTiles+1> _data{"     bb     b b R   bb          "};
    // std::array<char, _numTiles+1> _data{"          rr     r rB    rr     "};
    // std::array<char, _numTiles+1> _data{"bbbb bbbr bbb    rr   rr brrrrrr"};
    // std::array<char, _numTiles+1> _data{"      bbb rRbbb     rrr      rrr"};
    // std::array<char, _numTiles+1> _data{"bbbbb bb br     rr    r    rrrrr"};
    // std::array<char, _numTiles+1> _data{"     bb      bb   r             "};

};


#endif  // BOARD_HPP
