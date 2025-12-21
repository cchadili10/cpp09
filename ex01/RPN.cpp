#include "RPN.hpp"

RPN::RPN() {};
RPN::RPN(const RPN &other) { *this = other; };
RPN &RPN::operator=(const RPN &other) 
{
    if (this != &other)
        rpn = other.rpn;
    return *this;
};

void RPN::check_input(std::string &arg)
{
    if (arg.at(0) < '0' || arg.at(0) > '9')
        throw std::exception();
    std::stringstream ss(arg);
    std::string input;

    while (ss >> input)
    {
        if (input.size() != 1)
            throw std::exception();
        else if(input.at(0) >= '0' && input.at(0) <= '9')
        {
            rpn.push(atoi(input.c_str()));
        }
        else if (input.at(0) == '+' || input.at(0) == '-' || input.at(0) == '*' || input.at(0) == '/')
        {
    
        }
        else
            throw std::exception();
    }
}

RPN::~RPN() {};