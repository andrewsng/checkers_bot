#include "checkersgame.hpp"

int main(int argc, char *argv[]) {
    CheckersGame game{};
    game.setRedPlayer(PlayerType::MCTS);
    game.setBlackPlayer(PlayerType::AlphaBeta);
    game.setTimeLimitInSec(5.0);
    game.createDisplay();
    game.threeMoveStart();
    game.runGame();
    return 0;
}
