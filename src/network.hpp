#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "layer.hpp"
#include "initializer.hpp"
#include <vector>
#include <iostream>
#include <cmath>


class Network {

public:

    using data_type = DenseLayer::data_type;
    using size_type = DenseLayer::size_type;

    Network() = default;
    void printOutput() const;
    void addInput(size_type size);
    void addLayer(size_type size, DenseLayer::acti_func activation,
            DenseLayer::init_func initializer = zeros);
    void setInput(const std::vector<data_type> &input);
    void initExample();
    void forwardPropagate();

    static float ReLU(float x) {
        return std::max(0.0f, x);
    }

private:

    std::vector<DenseLayer> _layers{};

};


#endif  // NETWORK_HPP
