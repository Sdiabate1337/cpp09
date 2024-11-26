#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <utility>
#include <sstream>
#include <algorithm>
#include <climits>

class PmergeMe {
public:
    PmergeMe();
    ~PmergeMe();

    std::vector<int> parseInput(int argc, char* argv[]);
    void sortAndMeasureVector(const std::vector<int>& input);
    void sortAndMeasureDeque(const std::deque<int>& input);

private:
    static bool compareBySecond(const std::pair<int, int>& a, const std::pair<int, int>& b);

    std::vector<std::pair<int, int> > createPairsFromVector(const std::vector<int>& v);
    std::deque<std::pair<int, int> > createPairsFromDeque(const std::deque<int>& v);

    std::vector<int> mergeAndSortVector(const std::vector<int>& small, const std::vector<int>& large);
    std::deque<int> mergeAndSortDeque(const std::deque<int>& small, const std::deque<int>& large);

    std::vector<int> recursiveMergeInsertVector(const std::vector<int>& v);
    std::deque<int> recursiveMergeInsertDeque(const std::deque<int>& v);

    void displayVector(const std::string& message, const std::vector<int>& sequence);
    void displayDeque(const std::string& message, const std::deque<int>& sequence);
};

#endif // PMERGEME_HPP
