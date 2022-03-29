#ifndef MCTSNODE_HPP
#define MCTSNODE_HPP

#include "board.hpp"
#include "move.hpp"
#include "checkersgame.hpp"
#include "movegen.hpp"
#include <vector>
#include <memory>
#include <optional>
#include <utility>


class MCTSNode {

public:

    MCTSNode(Board board, int player, std::optional<Move> move = {});
    std::pair<MCTSNode *, bool> selectLeaf();
    MCTSNode *expandLeaf();
    void propagateResult(GameResult result);
    GameResult rollout() const;
    Move moveWithMostRollouts() const;
    int countNodes() const;

private:

    double UCTValue(int player) const;

    Board _board{};
    int _player{};
    Move _prevMove{};
    double _winPoints{0.0};
    int _numRollouts{0};
    std::vector<Move> _unvisited{generateMoves(_board, _player)};
    std::vector<std::shared_ptr<MCTSNode>> _children{};
    MCTSNode *_parent{nullptr};

};


#endif  // MCTSNODE_HPP
