#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return 1;
    }

    try {
        RPN rpnCalculator;
        int result = rpnCalculator.calculate(argv[1]);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
