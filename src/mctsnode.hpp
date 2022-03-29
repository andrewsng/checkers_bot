#ifndef MCTSNODE_HPP
#define MCTSNODE_HPP

#include "move.hpp"
#include <vector>
#include <memory>


class MCTSNode {

public:

    MCTSNode *selectLeaf();
    MCTSNode *expandLeaf() const;
    void propagateResult(int result) const;
    int rollout() const;

private:

    double UCTValue() const;

    std::vector<Move> _unvisited{};
    std::vector<std::shared_ptr<MCTSNode>> _children{};

};


#endif  // MCTSNODE_HPP
