#include "movegen.hpp"
#include <optional>
#include <functional>
using std::optional;
using std::vector;


// Forward declarations
vector<Move> generateLeftRight(const Board &, Board::Tile, int, bool, bool);
optional<Board::Tile> getLeft(const Board &, Board::Tile, bool);
optional<Board::Tile> getRight(const Board &, Board::Tile, bool);
vector<Move> generateNextMove(const Board &, Board::Tile, int,
                              bool, bool, decltype(getLeft) *);
void appendMoves(vector<Move> &&source, vector<Move> &dest);


vector<Move> generateMoves(const Board &board, int player) {
    vector<Move> moves{};
    bool isRed = (player == 0);
    auto positions = isRed ? board.getRedPositions() : board.getBlackPositions();
    for (const auto &tile : positions) {
        appendMoves(generateLeftRight(board, tile, player, !isRed, false), moves);
        if (board.isKing(tile)) {
            appendMoves(generateLeftRight(board, tile, player, isRed, false), moves);
        }
    }
    auto isJump = [](const Move &move) { return move.isAJump(); };
    if (std::find_if(moves.begin(), moves.end(), isJump) != moves.end()) {
        moves.erase(std::remove_if(moves.begin(), moves.end(), std::not_fn(isJump)), moves.end());
    }
    return moves;
}

vector<Move> generateLeftRight(const Board &board, Board::Tile tile,
                               int player, bool isUpward, bool mustBeJump) {
    auto moves = generateNextMove(board, tile, player, isUpward, mustBeJump, getLeft);
    appendMoves(generateNextMove(board, tile, player, isUpward, mustBeJump, getRight), moves);
    return moves;
}

void appendMoves(vector<Move> &&source, vector<Move> &dest) {
    dest.insert(dest.end(), std::make_move_iterator(source.begin()),
                            std::make_move_iterator(source.end()));
}

vector<Move> generateNextMove(const Board &board, Board::Tile tile, int player,
        bool isUpward, bool mustBeJump, decltype(getLeft) *getNextTile) {
    vector<Move> moves{};
    auto nextTile = getNextTile(board, tile, isUpward);
    if (!nextTile) {
        return moves;
    }
    if (!board.isOccupied(*nextTile) && !mustBeJump) {
        moves.push_back(Move{ tile, *nextTile });
        return moves;
    }
    auto nextJump = getNextTile(board, *nextTile, isUpward);
    if (!nextJump) {
        return moves;
    }
    if (board.isOpponent(*nextTile, player) && !board.isOccupied(*nextJump)) {
        Move firstJump{ tile, *nextJump };
        if (board.isPromotion(firstJump, player)) {
            moves.push_back(firstJump);
        }
        else {
            Board jumpTaken{board};
            jumpTaken.makeMove(firstJump, jumpTaken.getPlayer());
            auto multiJumps = generateLeftRight(jumpTaken, *nextJump, player, isUpward, true);
            if (jumpTaken.isKing(*nextJump)) {
                appendMoves(generateLeftRight(jumpTaken, *nextJump, player, !isUpward, true), multiJumps);
            }
            if (multiJumps.empty()) {
                moves.push_back(firstJump);
            }
            for (const auto &restOfJump : multiJumps) {
                Move fullJump{firstJump};
                fullJump.tiles.insert(fullJump.tiles.end(),
                                      std::make_move_iterator(restOfJump.tiles.begin()+1),
                                      std::make_move_iterator(restOfJump.tiles.end()));
                moves.push_back(fullJump);
            }
        }
    }
    return moves;
}

optional<Board::Tile> getLeft(const Board &board, Board::Tile tile, bool up) {
    Board::Tile ret{};
    if (board.onEvenRow(tile)) {
        if (board.onLeftSide(tile)) {
            return {};
        } else if (up) {
            ret = tile + 3;
        } else {
            ret = tile - 5;
        }
    } else if (up) {
        ret = tile + 4;
    } else {
        ret = tile - 4;
    }
    return board.isOutOfBounds(ret) ? optional<Board::Tile>{} : ret;
}

optional<Board::Tile> getRight(const Board &board, Board::Tile tile, bool up) {
    Board::Tile ret{};
    if (!board.onEvenRow(tile)) {
        if (board.onRightSide(tile)) {
            return {};
        } else if (up) {
            ret = tile + 5;
        } else {
            ret = tile - 3;
        }
    } else if (up) {
        ret = tile + 4;
    } else {
        ret = tile - 4;
    }
    return board.isOutOfBounds(ret) ? optional<Board::Tile>{} : ret;
}
