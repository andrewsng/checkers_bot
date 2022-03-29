#include "mctsnode.hpp"
#include "checkersgame.hpp"
#include <algorithm>
using std::max_element;
#include <memory>
using std::make_shared;
#include <cmath>


MCTSNode::MCTSNode(Board board, int player, std::optional<Move> move)
    :_board(board), _player(player) {
    if (move) {
        _prevMove = *move;
    }
}

std::pair<MCTSNode *, bool> MCTSNode::selectLeaf() {
    if (!_unvisited.empty()) {
        return {this, false};
    }
    if (_children.empty()) {
        return {this, true};
    }
    const int player = _player;
    auto maxChildIter = max_element(_children.begin(), _children.end(),
            [player](
            const std::shared_ptr<MCTSNode> &nodeA,
            const std::shared_ptr<MCTSNode> &nodeB
            ) {
                return nodeA->UCTValue(player) < nodeB->UCTValue(player);
            });
    return (*maxChildIter)->selectLeaf();
}

MCTSNode *MCTSNode::expandLeaf() {
    auto move = _unvisited.back();
    _unvisited.pop_back();
    Board nextBoard = _board;
    nextBoard.makeMove(move, _player);
    _children.push_back(make_shared<MCTSNode>(nextBoard, 1 - _player, move));
    _children.back()->_parent = this;
    return _children.back().get();
}

GameResult MCTSNode::rollout() const {
    CheckersGame simulation(_board, _player);
    simulation.setRedPlayer(PlayerType::Random);
    simulation.setBlackPlayer(PlayerType::Random);
    simulation.runGame();
    return simulation.result();
}

void MCTSNode::propagateResult(GameResult result) {
    switch (result) {
        case GameResult::RedWin:
            _winPoints += (_player == 0) ? 1.0 : 0.0;
            break;
        case GameResult::BlackWin:
            _winPoints += (_player == 1) ? 1.0 : 0.0;
            break;
        case GameResult::Draw:
            _winPoints += 0.5;
            break;
    }
    ++_numRollouts;
    if (_parent) {
        _parent->propagateResult(result);
    }
}

double MCTSNode::UCTValue(int player) const {
    double numRollouts = static_cast<double>(_numRollouts);
    double winRate = _winPoints / numRollouts;
    if (player != _player) {
        winRate = 1.0 - winRate;
    }
    double explorationTerm = 1.5 * std::sqrt(log(static_cast<double>(_parent->_numRollouts)) / numRollouts);
    return winRate + explorationTerm;
}

Move MCTSNode::moveWithMostRollouts() const {
    auto maxChildIter = max_element(_children.begin(), _children.end(),
            [](
            const std::shared_ptr<MCTSNode> &nodeA,
            const std::shared_ptr<MCTSNode> &nodeB
            ) {
                return nodeA->_numRollouts < nodeB->_numRollouts;
            });
    return (*maxChildIter)->_prevMove;
}

int MCTSNode::countNodes() const {
    if (_children.empty()) {
        return 1;
    }
    int count = 0;
    for (const auto &child : _children) {
        count += child->countNodes();
    }
    return count;
}
