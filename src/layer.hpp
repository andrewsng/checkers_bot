#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <vector>
#include <functional>


class DenseLayer {

public:

    using data_type = float;

    DenseLayer(std::size_t size, std::size_t prevSize, std::function<float(float)> activation)
        :_data(size, 0.0f), _weight(size, std::vector<data_type>(prevSize, 0.0f)), _bias(size, 0.0f), _activation(activation)
    {}

    std::vector<data_type> _data;
    std::vector<std::vector<data_type>> _weight;
    std::vector<data_type> _bias;
    std::function<float(float)> _activation;

private:

    void computeOutput(const std::vector<data_type> &prevLayer) {
        for (std::size_t i = 0; i < _data.size(); ++i) {
            float output = _bias[i];
            for (std::size_t j = 0; j < prevLayer.size(); ++j) {
                output += prevLayer[j] * _weight[i][j];
            }
            _data[i] = _activation(output);
        }
    }

    void print() const {
        for (const auto &val : _data) {
            std::cout << val << " ";
        }
    }

};


#endif  // LAYER_HPP
