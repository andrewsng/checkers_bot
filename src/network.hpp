#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "layer.hpp"
#include <vector>
#include <iostream>
#include <cmath>


class Network {

public:

    Network()
        :_layers(4, DenseLayer(0, 0, ReLU)) {
        _layers[0] = DenseLayer(2, 0, ReLU);
        _layers[0].setData({ 0.5f, 1.0f });

        _layers[1] = DenseLayer(4, 2, ReLU);
        _layers[1].setWeights({ { 0.25f, 0.5f },
                               { 0.5f, 0.75f },
                               { 0.75f, 1.0f },
                               { 1.0f, 1.25f } });
        _layers[1].setBias({ 0.25f, 0.5f, 0.75f, 1.0f });

        _layers[2] = DenseLayer(3, 4, ReLU);
        _layers[2].setWeights({ { 0.25f, 0.5f, 0.75f, 1.0f },
                               { 0.5f, 0.75f, 1.0f, 1.25f },
                               { 0.75f, 1.0f, 1.25f, 1.5f } });
        _layers[2].setBias({ 1.25f, 1.5f, 1.75f });

        _layers[3] = DenseLayer(1, 3, ReLU);
        _layers[3].setWeights({ { 0.25f, 0.5f, 0.75f } });
        _layers[3].setBias({ 2.0 });
    }
    
    std::vector<DenseLayer> _layers{};

    void forwardPropagate() {
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

private:

    static float ReLU(float x) {
        return std::max(0.0f, x);
    }

};


#endif  // NETWORK_HPP
