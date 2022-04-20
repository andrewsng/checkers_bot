#include "network.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    Network n{};
    n.initExample();
    n.forwardPropagate();
    std::cout << "Network results:\n";
    n.printOutput();
    std::cout << "\n";
}
