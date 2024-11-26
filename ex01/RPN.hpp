#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <stdexcept>

class RPN {
public:
    RPN();
    ~RPN();
    //RPN(const RPN& other);
    //RPN& operator=(const RPN& other);

    int calculate(const std::string& expression);

private:
    bool isOperator(char token) const;
    int performOperation(int a, int b, char operation) const;
    int stringToInt(const std::string& str) const;
};

#endif
