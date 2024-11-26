#include "PmergeMe.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    try {
        PmergeMe sorter;

        if (argc > 1) {
            std::vector<int> input = sorter.parseInput(argc, argv);

            std::cout << "Using std::vector:" << std::endl;
            sorter.sortAndMeasureVector(input);

            std::deque<int> inputDeque(input.begin(), input.end());
            std::cout << "\nUsing std::deque:" << std::endl;
            sorter.sortAndMeasureDeque(inputDeque);
        } else {
            std::srand(std::time(0));
            std::vector<int> randomInput(3000);
            for (size_t i = 0; i < randomInput.size(); ++i) {
                randomInput[i] = std::rand() % 100000;
            }

            std::cout << "Sorting 3000 random integers..." << std::endl;

            sorter.sortAndMeasureVector(randomInput);

            std::deque<int> randomInputDeque(randomInput.begin(), randomInput.end());
            sorter.sortAndMeasureDeque(randomInputDeque);
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
