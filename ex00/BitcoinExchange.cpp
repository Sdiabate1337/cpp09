#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}


BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    priceData = other.priceData;  
}


BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {  
        priceData = other.priceData; 
    }
    return *this;
}


std::string BitcoinExchange::trim(const std::string& str) const {

    std::string::size_type start = str.find_first_not_of(" \t\f\v\n\r");
    std::string::size_type end = str.find_last_not_of(" \t\f\v\n\r");

    if (start == std::string::npos || end == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}


void BitcoinExchange::validateDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        throw std::invalid_argument("Error: invalid date format: " + date);
    }

    int year, month, day;
    char dash1, dash2;
    std::istringstream dateStream(date);
    if (!(dateStream >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-' ||
        year < 2000 || month < 1 || month > 12 || day < 1 || day > 31) {
        throw std::invalid_argument("Error: invalid date values: " + date);
    }
}

void BitcoinExchange::validateValue(double value) const {
    if (value < 0) {
        throw std::out_of_range("Error: not a positive number.");
    }
    if (value > 1000) {
        throw std::out_of_range("Error: too large a number.");
    }
}


void BitcoinExchange::loadPrices(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string date;
        double price;

        if (std::getline(lineStream, date, ',') && lineStream >> price) {
            validateDate(date);
            if (price < 0) {
                throw std::runtime_error("Error: negative price in file.");
            }
            priceData[date] = price;
        }
    }
}


void BitcoinExchange::processInput(const std::string& filename) const {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        try {
            std::istringstream lineStream(line);
            std::string date;
            double value;

            if (std::getline(lineStream, date, '|') && lineStream >> value) {
                date = trim(date); // Remove leading/trailing whitespace
                validateDate(date);
                validateValue(value);

                // Find the closest matching price
                std::map<std::string, double>::const_iterator it = priceData.lower_bound(date);
                if (it == priceData.end() || it->first != date) {
                    if (it != priceData.begin()) {
                        --it; // Get the closest earlier date if no exact match
                    } else {
                        std::cerr << "Error: no data for date: " << date << std::endl;
                        continue;
                    }
                }

                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
            } else {
                throw std::invalid_argument("Error: bad input => " + line);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
