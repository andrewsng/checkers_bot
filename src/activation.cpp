#include "activation.hpp"
#include <algorithm>
#include <cmath>


float ReLU(float x) {
    return std::max(0.0f, x);
}

float hyperbolicTangent(float x) {
    return std::tanh(x);
}
