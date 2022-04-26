#include "network.hpp"
#include <iostream>


void Network::printOutput() const {
    _layers.back().printData();
}

const std::vector<Network::data_type> &Network::getOutput() const {
    return _layers.back().getData();
}

void Network::addInput(size_type size) {
    _layers.emplace(_layers.begin(), size, 0, ReLU, zeros);
}

void Network::addLayer(size_type size, DenseLayer::acti_func activation,
        DenseLayer::init_func initializer) {
    _layers.emplace(_layers.end(), size, _layers.back().size(), activation, initializer);
}

void Network::setInput(const std::vector<data_type> &input) {
    if (_layers.front().size() != input.size()) {
        std::cerr << "ERROR - Network::setInput - Incorrect input size" << std::endl;
        return;
    }
    _layers.front().setData(input);
}

void Network::initExample() {
    addInput(2);
    _layers.back().setData({ 0.5f, 1.0f });

    addLayer(4, ReLU);
    _layers.back().setWeights({ { 0.25f, 0.5f },
                           { 0.5f, 0.75f },
                           { 0.75f, 1.0f },
                           { 1.0f, 1.25f } });
    _layers.back().setBias({ 0.25f, 0.5f, 0.75f, 1.0f });

    addLayer(3, ReLU);
    _layers.back().setWeights({ { 0.25f, 0.5f, 0.75f, 1.0f },
                           { 0.5f, 0.75f, 1.0f, 1.25f },
                           { 0.75f, 1.0f, 1.25f, 1.5f } });
    _layers.back().setBias({ 1.25f, 1.5f, 1.75f });

    addLayer(1, ReLU);
    _layers.back().setWeights({ { 0.25f, 0.5f, 0.75f } });
    _layers.back().setBias({ 2.0 });
}

void Network::forwardPropagate() {
    for (auto it =  _layers.begin() + 1; it != _layers.end(); ++it) {
        it->computeOutput(*(it - 1));
    }
}
