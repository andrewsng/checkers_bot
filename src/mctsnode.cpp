#include "mctsnode.hpp"
#include <algorithm>
using std::max_element;
#include <memory>
using std::make_shared;


MCTSNode::MCTSNode(Board board, int player)
    :_board(board), _player(player)
{}

MCTSNode *MCTSNode::selectLeaf() {
    if (!_unvisited.empty()) {
        return this;
    }
    auto maxChildIter = max_element(_children.begin(), _children.end(),
            [](
            const std::shared_ptr<MCTSNode> &nodeA,
            const std::shared_ptr<MCTSNode> &nodeB
            ) {
                return nodeA->UCTValue() < nodeB->UCTValue();
            });
    return (*maxChildIter)->selectLeaf();
}

MCTSNode *MCTSNode::expandLeaf() {
    auto move = _unvisited.back();
    _unvisited.pop_back();
    Board nextBoard = _board;
    nextBoard.makeMove(move, _player);
    _children.push_back(make_shared<MCTSNode>(nextBoard, 1 - _player));
    return _children.back().get();
}

int MCTSNode::rollout() const {
    return 0;
}

void MCTSNode::propagateResult(int result) const {
}

double MCTSNode::UCTValue() const {
    return 0.0;
}
