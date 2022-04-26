#include "network.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    Network n{};
    // n.initExample();
    n.addInput(3);
    n.addLayer(4, Network::ReLU);
    n.addLayer(1, Network::ReLU);
    n.forwardPropagate();
    std::cout << "Network results:\n";
    n.printOutput();
    std::cout << "\n";
    n.setInput({1.0, 1.0, 1.0});
    n.setInput({0.25, 0.5});
    n.forwardPropagate();
    std::cout << "Network results:\n";
    n.printOutput();
    std::cout << "\n";
}
