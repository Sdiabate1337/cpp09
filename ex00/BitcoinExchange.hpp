#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>

class BitcoinExchange {
private:
    std::map<std::string, double> priceData;

    void validateDate(const std::string& date) const;
    void validateValue(double value) const;
    std::string trim(const std::string& str) const;

public:
    BitcoinExchange();
    ~BitcoinExchange();

     // Copy Constructor
    BitcoinExchange(const BitcoinExchange& other);

    // Copy Assignment Operator
    BitcoinExchange& operator=(const BitcoinExchange& other);

    // Move Constructor
    BitcoinExchange(BitcoinExchange& other) ;

    // Move Assignment Operator
    BitcoinExchange& operator=(BitcoinExchange& other) ;
    
    void loadPrices(const std::string& filename);
    void processInput(const std::string& filename) const;
};

#endif
