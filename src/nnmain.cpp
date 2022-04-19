#include "network.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    Network n{};
    n.forwardPropagate();
    std::cout << "Network results:\n";
    for (const auto &o : n._output) {
        std::cout << o << " ";
    }
    std::cout << "\n";
}
