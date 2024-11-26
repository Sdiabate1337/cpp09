#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}


bool RPN::isOperator(char token) const {
    return token == '+' || token == '-' || token == '*' || token == '/';
}

int RPN::performOperation(int a, int b, char operation) const {
    switch (operation) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': 
        if (b == 0)
            throw std::runtime_error("Error: division by zero");
        return a / b;
    default:
        throw std::invalid_argument("Error: invalid operator");
    }
}

// Helper function to convert a string to an integer (C++98 compatible)
int RPN::stringToInt(const std::string& str) const {
    std::stringstream ss(str);
    int num;
    if (!(ss >> num)) {
        throw std::invalid_argument("Error: invalid number");
    }
    return num;
}

int RPN::calculate(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        // Check if token is a number
        if (isdigit(token[0])) {
            stack.push(stringToInt(token));
        } 
        // Check if token is an operator
        else if (token.size() == 1 && isOperator(token[0])) {
            if (stack.size() < 2) {
                throw std::runtime_error("Error: invalid expression");
            }

            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            int result = performOperation(a, b, token[0]);
            stack.push(result);
        } 
        else {
            throw std::invalid_argument("Error: invalid token");
        }
    }

    // After processing, there should be exactly one element in the stack
    if (stack.size() != 1) {
        throw std::runtime_error("Error: invalid expression");
    }

    return stack.top();
}
