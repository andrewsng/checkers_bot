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
    using acti_func = std::function<data_type(data_type)>;
    using init_func = std::function<data_type()>;

    DenseLayer(size_type size, size_type prevSize, acti_func activation,
            init_func initializer);
    void printData() const;
    void printWeights() const;
    size_type size() const;
    void setData(const std::vector<data_type> &newData);
    void setWeights(const std::vector<std::vector<data_type>> &newWeights);
    void setBias(const std::vector<data_type> &newBias);
    void computeOutput(const DenseLayer &prevLayer);

private:

    std::vector<data_type> _data;
    std::vector<std::vector<data_type>> _weight;
    std::vector<data_type> _bias;
    acti_func _activation;

};


#endif  // LAYER_HPP
