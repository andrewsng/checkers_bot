#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>


class Move;

class Board {

public:

    using Tile = std::string::size_type;
    Board() = default;
    int getPlayer() const;
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
    bool isLegalMove(const Move &move, int player) const;
    void makeMove(const Move &move, int player);
    void changeTurn();
    void makeBotMove(int player);

private:

    std::string _data{"bbbbbbbbbbbb        rrrrrrrrrrrr"};
    // std::string _data{"Rbbb   r       r   rb         r "};
    // std::string _data{"     bb     b b R   bb          "};
    // std::string _data{"          rr     r rb    rr     "};
    // std::string _data{"bbbb bbbr bbb    rr   rr brrrrrr"};
    // std::string _data{"      bbb rRbbb     rrr      rrr"};
    int _player{0};

};


#endif  // BOARD_HPP
