#ifndef MCTSNODE_HPP
#define MCTSNODE_HPP

#include "board.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include <vector>
#include <memory>


class MCTSNode {

public:

    MCTSNode(Board board, int player);
    MCTSNode *selectLeaf();
    MCTSNode *expandLeaf();
    void propagateResult(int result) const;
    int rollout() const;

private:

    double UCTValue() const;

    Board _board{};
    int _player{};
    std::vector<Move> _unvisited{generateMoves(_board, _player)};
    std::vector<std::shared_ptr<MCTSNode>> _children{};

};


#endif  // MCTSNODE_HPP
