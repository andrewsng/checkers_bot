#include "catch.hpp"

#include "board.hpp"
#include "movegen.hpp"
#include <vector>
using std::vector;
#include <algorithm>


void testMoveGen(const Board &board, const vector<Move> &correctRedMoves,
        const vector<Move> &correctBlackMoves) {
    auto redMoves = generateMoves(board, 0);
    CHECK_THAT(redMoves, Catch::Matchers::UnorderedEquals(correctRedMoves));
    auto blackMoves = generateMoves(board, 1);
    CHECK_THAT(blackMoves, Catch::Matchers::UnorderedEquals(correctBlackMoves));
}


TEST_CASE("Move Generation - Simple Moves") {
    Board b;
    vector<Move> red = {
        Move{ 20, 16, 0 }, Move{ 20, 17, 0 }, Move{ 21, 17, 0 }, Move{ 21, 18, 0 },
        Move{ 22, 18, 0 }, Move{ 22, 19, 0 }, Move{ 23, 19, 0 }
    };
    vector<Move> black = {
        Move{  8, 12, 1 }, Move{  9, 12, 1 }, Move{  9, 13, 1 },
        Move{ 10, 13, 1 }, Move{ 10, 14, 1 }, Move{ 11, 14, 1 }, Move{ 11, 15, 1 }
    };
    testMoveGen(b, red, black);
}
