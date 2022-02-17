#include "checkersdisplay.hpp"
#include "movegen.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>

void botMove(Board &game) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    auto legalMoves = generateMoves(game, game.getPlayer());
    if (legalMoves.empty()) {
        game.changeTurn();
        return;
    }
    std::uniform_int_distribution<std::size_t> dist(0ull, legalMoves.size() - 1);
    auto randomMove = legalMoves[dist(gen)];
    if (game.isLegalMove(randomMove, game.getPlayer())) {
        game.makeMove(randomMove, game.getPlayer());
        game.changeTurn();
    }
}

int main(int argc, char *argv[]) {
    CheckersDisplay display(1000, 1000, "Checkers");
    Board game{};
    display.drawBoard(game);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    if (dist(gen)) {
        // botMove(game);
    }
    while (display.isOpen()) {
        display.handleInputs(game);
        game.makeBotMove(game.getPlayer());
        display.drawBoard(game);
        game.makeBotMove(game.getPlayer());
        display.drawBoard(game);
    }
    return 0;
}
