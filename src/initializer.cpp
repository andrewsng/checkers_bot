#include "initializer.hpp"
#include <random>


float zeros() {
    return 0.0f;
}

float ones() {
    return 1.0f;
}

std::function<float()> randomUniform(float min, float max) {
    return [=]() mutable {
        std::random_device rd{};
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    };
}
