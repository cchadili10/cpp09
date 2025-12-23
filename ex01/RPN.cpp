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
    std::stringstream ss(arg);
    std::string input;

    while (ss >> input)
    {
        if (input.size() != 1)
            throw std::runtime_error("Error : not valid operator or number");
        else if(input.at(0) >= '0' && input.at(0) <= '9')
        {
            rpn.push(atoi(input.c_str()));
        }
        else if (input.at(0) == '+' || input.at(0) == '-' || input.at(0) == '*' || input.at(0) == '/')
        {
            if(rpn.size() < 2)
                throw std::runtime_error("Error : The  operator needs two numbers, but there's only one number in the stack");
            int index;
            index = rpn.top();
            rpn.pop();
            switch (input.at(0))
            {
                case ('+'):
                    rpn.top() = rpn.top() + index;
                    break;
                case ('-'):
                    rpn.top() = rpn.top() - index;
                    break;
                case ('*'):
                    rpn.top() = rpn.top() * index;
                    break;
                case ('/'):
                    if (index == 0)
                        throw std::runtime_error("Error : division by zero");
                    rpn.top() = rpn.top() / index;
                    break;
                default:
                    break;
            }
        }
        else
            throw std::runtime_error("Error : not valid operator or number");
    }
    if (rpn.size() != 1)
        throw std::runtime_error("Error : the expression is incomplete");
    res = rpn.top();
}

int RPN::ft_get_result() const
{
    return res;
}

RPN::~RPN() {};