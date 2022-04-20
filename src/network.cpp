#include "network.hpp"


void Network::printOutput() const {
    for (const auto &val : _layers.back()._data) {
        std::cout << val << " ";
    }
}
void Network::addInput(size_type size) {
    _layers.emplace(_layers.begin(), size, 0, ReLU);
}

void Network::addLayer(size_type size, DenseLayer::func_type activation) {
    _layers.emplace(_layers.end(), size, _layers.back().size(), ReLU);
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
    _layers[0].printData();
    std::cout << "\n";

    _layers[1].computeOutput(_layers[0]._data);
    _layers[1].printData();
    std::cout << "\n";

    _layers[2].computeOutput(_layers[1]._data);
    _layers[2].printData();
    std::cout << "\n";

    _layers[3].computeOutput(_layers[2]._data);
    _layers[3].printData();
    std::cout << "\n";
}
