#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "layer.hpp"
#include "activation.hpp"
#include "initializer.hpp"
#include <vector>


class Network {

public:

    using data_type = DenseLayer::data_type;
    using size_type = DenseLayer::size_type;

    Network() = default;
    void printOutput() const;
    const std::vector<data_type> &getOutput() const;
    void addInput(size_type size);
    void addLayer(size_type size, DenseLayer::acti_func activation,
            DenseLayer::init_func initializer = zeros);
    void setInput(const std::vector<data_type> &input);
    void initExample();
    void forwardPropagate();

private:

    std::vector<DenseLayer> _layers{};

};


#endif  // NETWORK_HPP
