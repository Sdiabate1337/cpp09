#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

bool PmergeMe::compareBySecond(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second < b.second;
}

std::vector<int> PmergeMe::parseInput(int argc, char* argv[]) {

    clock_t start_time = clock();

    std::vector<int> result;
    for (int i = 1; i < argc; ++i) {
        int value;
        std::istringstream iss(argv[i]);
        if (!(iss >> value) || value <= 0) {
            std::cerr << "Error: Only positive integers are allowed." << std::endl;
            exit(1);
        }

        result.push_back(value);
    }

    clock_t end_time = clock();
    double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Data management time (input parsing): " << duration * 1000000 << " µs" << std::endl;

    return result;
}

std::vector<std::pair<int, int> > PmergeMe::createPairsFromVector(const std::vector<int>& v) {

    std::vector<std::pair<int, int> > result;

    for (size_t i = 0; i < v.size(); ++i) {
        if (i + 1 < v.size()) {
            result.push_back(std::make_pair(v[i], v[i + 1]));
            ++i;
        } else {
            result.push_back(std::make_pair(v[i], -1));
        }
    }
    return result;
}

std::deque<std::pair<int, int> > PmergeMe::createPairsFromDeque(const std::deque<int>& v) {

    std::deque<std::pair<int, int> > result;

    for (size_t i = 0; i < v.size(); ++i) {
        if (i + 1 < v.size()) {
            result.push_back(std::make_pair(v[i], v[i + 1]));
            ++i;
        } else {
            result.push_back(std::make_pair(v[i], -1));
        }
    }
    return result;
}

std::vector<int> PmergeMe::mergeAndSortVector(const std::vector<int>& small, const std::vector<int>& large) {

    std::vector<int> result = small;

    for (size_t i = 0; i < large.size(); ++i) {
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), large[i]);
        result.insert(pos, large[i]);
    }
    return result;
}

std::deque<int> PmergeMe::mergeAndSortDeque(const std::deque<int>& small, const std::deque<int>& large) {
    std::deque<int> result = small;
    for (size_t i = 0; i < large.size(); ++i) {
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), large[i]);
        result.insert(pos, large[i]);
    }
    return result;
}

std::vector<int> PmergeMe::recursiveMergeInsertVector(const std::vector<int>& v) {

    if (v.size() <= 1) return v;

    std::vector<std::pair<int, int> > pairs = createPairsFromVector(v);
    std::sort(pairs.begin(), pairs.end(), compareBySecond);

    std::vector<int> small, large;
    for (size_t i = 0; i < pairs.size(); ++i) {
        small.push_back(pairs[i].first);
        if (pairs[i].second != -1) large.push_back(pairs[i].second);
    }

    std::sort(small.begin(), small.end());
    if (large.size() >= 2) large = recursiveMergeInsertVector(large);

    return mergeAndSortVector(small, large);
}

std::deque<int> PmergeMe::recursiveMergeInsertDeque(const std::deque<int>& v) {
    if (v.size() <= 1) return v;


    std::deque<std::pair<int, int> > pairs = createPairsFromDeque(v);
    std::sort(pairs.begin(), pairs.end(), compareBySecond);

    std::deque<int> small, large;
    for (size_t i = 0; i < pairs.size(); ++i) {
        small.push_back(pairs[i].first);
        if (pairs[i].second != -1) large.push_back(pairs[i].second);
    }

    std::sort(small.begin(), small.end());
    if (large.size() >= 2) large = recursiveMergeInsertDeque(large);

    return mergeAndSortDeque(small, large);
}

void PmergeMe::sortAndMeasureVector(const std::vector<int>& input) {

    clock_t start_time = clock();
    std::vector<int> sorted = recursiveMergeInsertVector(input);
    clock_t end_time = clock();

    double sorting_duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Sorting time (std::vector): " << sorting_duration * 1000000 << " µs" << std::endl;

    displayVector("Before sorting: ", input);
    displayVector("After sorting:  ", sorted);
}

void PmergeMe::sortAndMeasureDeque(const std::deque<int>& input) {
    clock_t start_time = clock();
    std::deque<int> sorted = recursiveMergeInsertDeque(input);
    clock_t end_time = clock();

    double sorting_duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Sorting time (std::deque): " << sorting_duration * 1000000 << " µs" << std::endl;

    displayDeque("Before sorting: ", input);
    displayDeque("After sorting:  ", sorted);
}

void PmergeMe::displayVector(const std::string& message, const std::vector<int>& sequence) {

    std::cout << message;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << (i + 1 != sequence.size() ? " " : "");
    }
    std::cout << std::endl;
}

void PmergeMe::displayDeque(const std::string& message, const std::deque<int>& sequence) {

    std::cout << message;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << (i + 1 != sequence.size() ? " " : "");
    }
    std::cout << std::endl;
}
