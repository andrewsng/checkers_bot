#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "layer.hpp"
#include <vector>
#include <iostream>
#include <cmath>


class Network {

public:

    using size_type = DenseLayer::size_type;

    Network() = default;
    void printOutput() const;
    void addInput(size_type size);
    void addLayer(size_type size, DenseLayer::func_type activation);
    void initExample();
    void forwardPropagate();

private:

    static float ReLU(float x) {
        return std::max(0.0f, x);
    }

    std::vector<DenseLayer> _layers{};

};


#endif  // NETWORK_HPP
