#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP

#include <functional>


float zeros();
float ones();
std::function<float()> randomUniform(float min, float max);


#endif  // INITIALIZER_HPP
