#include "mctsnode.hpp"
#include <algorithm>
using std::max_element;


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

MCTSNode *MCTSNode::expandLeaf() const {
    return nullptr;
}

int MCTSNode::rollout() const {
    return 0;
}

void MCTSNode::propagateResult(int result) const {
}

double MCTSNode::UCTValue() const {
    return 0.0;
}
