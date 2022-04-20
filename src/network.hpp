#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <iostream>
#include <cmath>


class Network {

public:
    
    std::vector<float> _input{ 0.5f, 1.0f };

    std::vector<std::vector<float>> _weights1{ { 0.25f, 0.5f },
                                               { 0.5f, 0.75f },
                                               { 0.75f, 1.0f },
                                               { 1.0f, 1.25f } };
    std::vector<float> _bias1{ 0.25f, 0.5f, 0.75f, 1.0f };
    std::vector<float> _hidden1 = std::vector<float>(4, 0.0f);

    std::vector<std::vector<float>> _weights2{ { 0.25f, 0.5f, 0.75f, 1.0f },
                                               { 0.5f, 0.75f, 1.0f, 1.25f },
                                               { 0.75f, 1.0f, 1.25f, 1.5f } };
    std::vector<float> _bias2{ 1.25f, 1.5f, 1.75f };
    std::vector<float> _hidden2 = std::vector<float>(3, 0.0f);

    std::vector<std::vector<float>> _weights3{ { 0.25f, 0.5f, 0.75f } };
    std::vector<float> _bias3{ 2.0 };
    std::vector<float> _output = std::vector<float>(1, 0.0f);

    void forwardPropagate() {
        printVector(_input);
        std::cout << "\n";
        for (std::size_t i = 0; i < _hidden1.size(); ++i) {
            float output = _bias1[i];
            for (std::size_t j = 0; j < _input.size(); ++j) {
                output += _input[j] * _weights1[i][j];
            }
            _hidden1[i] = ReLU(output);
        }
        printVector(_hidden1);
        std::cout << "\n";
        for (std::size_t i = 0; i < _hidden2.size(); ++i) {
            float output = _bias2[i];
            for (std::size_t j = 0; j < _hidden1.size(); ++j) {
                output += _hidden1[j] * _weights2[i][j];
            }
            _hidden2[i] = ReLU(output);
        }
        printVector(_hidden2);
        std::cout << "\n";
        for (std::size_t i = 0; i < _output.size(); ++i) {
            float output = _bias3[i];
            for (std::size_t j = 0; j < _hidden2.size(); ++j) {
                output += _hidden2[j] * _weights3[i][j];
            }
            _output[i] = ReLU(output);
        }
        printVector(_output);
        std::cout << "\n";
    }

private:

    void printVector(const std::vector<float> &vec) const {
        for (const auto &val : vec) {
            std::cout << val << " ";
        }
    }

    float ReLU(float x) {
        return std::max(0.0f, x);
    }

};


#endif  // NETWORK_HPP
