#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>


class Network {

public:
    
    std::vector<float> _input{ 1.0f, 1.0f, 1.0f };
    std::vector<std::vector<float>> _weights{{ 0.25f, 0.5f, 0.75f },
                                             { 0.5f, 0.75f, 1.0f },
                                             { 0.75f, 1.0f, 1.25f }};
    std::vector<float> _bias{ 3.0f, 4.0f, 5.0f };
    std::vector<float> _output{ 0.0f, 0.0f, 0.0f };

    void forwardPropagate() {
        for (int i = 0; i < 3; ++i) {
            float output = _bias[i];
            for (int j = 0; j < 3; ++j) {
                output += _input[j] * _weights[i][j];
            }
            _output[i] = output;
        }
    }

private:

};


#endif  // NETWORK_HPP
