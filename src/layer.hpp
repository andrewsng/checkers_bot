#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <vector>
#include <functional>


class DenseLayer {

public:

    using data_type = float;

    DenseLayer(std::size_t size, std::size_t prevSize, std::function<float(float)> activation);
    void printData() const;
    void setData(const std::vector<data_type> &newData);
    void setWeights(const std::vector<std::vector<data_type>> &newWeights);
    void setBias(const std::vector<data_type> &newBias);
    void computeOutput(const std::vector<data_type> &prevLayer);
    std::vector<data_type> _data;

private:

    std::vector<std::vector<data_type>> _weight;
    std::vector<data_type> _bias;
    std::function<float(float)> _activation;

};


#endif  // LAYER_HPP
