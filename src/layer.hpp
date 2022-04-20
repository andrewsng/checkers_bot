#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <cstddef>


class DenseLayer {

public:

    using data_type = float;
    using size_type = std::size_t;
    using func_type = std::function<float(float)>;

    DenseLayer(size_type size, size_type prevSize, func_type activation);
    void printData() const;
    void setData(const std::vector<data_type> &newData);
    void setWeights(const std::vector<std::vector<data_type>> &newWeights);
    void setBias(const std::vector<data_type> &newBias);
    void computeOutput(const std::vector<data_type> &prevLayer);
    std::vector<data_type> _data;

private:

    std::vector<std::vector<data_type>> _weight;
    std::vector<data_type> _bias;
    func_type _activation;

};


#endif  // LAYER_HPP
