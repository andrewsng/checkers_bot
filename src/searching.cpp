#include "searching.hpp"
#include "movegen.hpp"
#include <optional>
using std::optional;
#include <random>


optional<Move> miniMax(Board board, int player, int depth) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    auto legalMoves = generateMoves(board, player);
    if (legalMoves.empty()) {
        return {};
    }
    std::uniform_int_distribution<std::size_t> dist(0ull, legalMoves.size() - 1);
    return legalMoves[dist(gen)];
}
