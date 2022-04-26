#include "layer.hpp"
#include <vector>
using std::vector;
#include <algorithm>


DenseLayer::DenseLayer(size_type size, size_type prevSize, acti_func activation,
        init_func initializer)
    :_data(size, 0.0f), _weight(size, vector<data_type>(prevSize, 0.0f)),
     _bias(size, 0.0f), _activation(activation)
{
    if (prevSize > 0) {
        for (auto &w : _weight) {
            std::generate(w.begin(), w.end(), initializer);
        }
        std::generate(_bias.begin(), _bias.end(), initializer);
    }
}


void DenseLayer::printData() const {
    for (const auto &val : _data) {
        std::cout << val << " ";
    }
}

DenseLayer::size_type DenseLayer::size() const {
    return _data.size();
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

void DenseLayer::computeOutput(const DenseLayer &prevLayer) {
    for (size_type i = 0; i < _data.size(); ++i) {
        float output = _bias[i];
        for (size_type j = 0; j < prevLayer.size(); ++j) {
            output += prevLayer._data[j] * _weight[i][j];
        }
        _data[i] = _activation(output);
    }
}
