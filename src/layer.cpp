#include "layer.hpp"
#include <vector>
using std::vector;


DenseLayer::DenseLayer(size_type size, size_type prevSize, func_type activation)
    :_data(size, 0.0f), _weight(size, vector<data_type>(prevSize, 0.0f)),
     _bias(size, 0.0f), _activation(activation)
{}


void DenseLayer::printData() const {
    for (const auto &val : _data) {
        std::cout << val << " ";
    }
}

void DenseLayer::setData(const vector<data_type> &newData) {
    for (size_type i = 0; i < _data.size(); ++i) {
        _data[i] = newData[i];
    }
}

void DenseLayer::setWeights(const vector<vector<data_type>> &newWeights) {
    _weight = newWeights;
}

void DenseLayer::setBias(const vector<data_type> &newBias) {
    for (size_type i = 0; i < _bias.size(); ++i) {
        _bias[i] = newBias[i];
    }
}

void DenseLayer::computeOutput(const vector<data_type> &prevLayer) {
    for (size_type i = 0; i < _data.size(); ++i) {
        float output = _bias[i];
        for (size_type j = 0; j < prevLayer.size(); ++j) {
            output += prevLayer[j] * _weight[i][j];
        }
        _data[i] = _activation(output);
    }
}
