#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "layer.hpp"
#include <vector>
#include <iostream>
#include <cmath>


class Network {

public:

    Network()
        :_layers(3, DenseLayer(0, 0, ReLU)) {
        _layers[0] = DenseLayer(4, 2, ReLU);
        _layers[0]._weight = { { 0.25f, 0.5f },
                               { 0.5f, 0.75f },
                               { 0.75f, 1.0f },
                               { 1.0f, 1.25f } };
        _layers[0]._bias = { 0.25f, 0.5f, 0.75f, 1.0f };

        _layers[1] = DenseLayer(3, 4, ReLU);
        _layers[1]._weight = { { 0.25f, 0.5f, 0.75f, 1.0f },
                               { 0.5f, 0.75f, 1.0f, 1.25f },
                               { 0.75f, 1.0f, 1.25f, 1.5f } };
        _layers[1]._bias = { 1.25f, 1.5f, 1.75f };

        _layers[2] = DenseLayer(1, 3, ReLU);
        _layers[2]._weight = { { 0.25f, 0.5f, 0.75f } };
        _layers[2]._bias =  { 2.0 };
    }
    
    std::vector<float> _input{ 0.5f, 1.0f };
    std::vector<DenseLayer> _layers{};

    void forwardPropagate() {
        printVector(_input);
        std::cout << "\n";

        _layers[0].computeOutput(_input);
        _layers[0].print();
        std::cout << "\n";

        _layers[1].computeOutput(_layers[0]._data);
        _layers[1].print();
        std::cout << "\n";

        _layers[2].computeOutput(_layers[1]._data);
        _layers[2].print();
        std::cout << "\n";
    }

private:

    void printVector(const std::vector<float> &vec) const {
        for (const auto &val : vec) {
            std::cout << val << " ";
        }
    }

    static float ReLU(float x) {
        return std::max(0.0f, x);
    }

};


#endif  // NETWORK_HPP
