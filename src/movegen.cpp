#include "movegen.hpp"
using std::vector;


vector<Move> generateMoves(Board board, int player) {
    vector<Move> moves;
    if (player == 1) {
        auto blackPositions = board.getBlackPositions();
        for (const auto &tile : blackPositions) {
            if (board.onEvenRow(tile)) {
                if (!board.onLeftSide(tile)) {
                    moves.push_back({tile, tile + 3});
                }
                moves.push_back({tile, tile + 4});
            }
            else {
                if (!board.onRightSide(tile)) {
                    moves.push_back({tile, tile + 5});
                }
                moves.push_back({tile, tile + 4});
            }
        }
    }
    return moves;
}
