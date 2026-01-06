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

    std::string input;
    for (size_t i = 0; i < arg.size(); i++)
    {
        if(!isspace(arg[i]))
            input+=arg[i];
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        if ((input[i] >= '0' && input[i] <= '9'))
        {
            int value = input[i] - '0';
            rpn.push(value);
        }
        else if ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'))
        {
            if (rpn.size() < 2)
                 throw std::runtime_error("Error : The  operator needs two numbers, but there's only one number in the stack");
            double index;
            index = rpn.top();
            rpn.pop();
            switch (input[i])
            {
                case ('+'):
                    rpn.top() = rpn.top() + index;
                    break ;
                case ('-'):
                    rpn.top() = rpn.top() - index;
                    break ;
                case ('*'):
                    rpn.top() = rpn.top() * index;
                    break;
                case ('/') :
                    if (index == 0)
                        throw std::runtime_error("Error : division by zero");
                    rpn.top() = rpn.top() / index;
                    break ;
                default:
                    break ;
            }
        }
        else
            throw std::runtime_error("Error : not valid operator or number");
    }
    if (rpn.size() != 1)
        throw std::runtime_error("Error : the expression is incomplete");
    res = rpn.top();
}

double RPN::ft_get_result() const
{
    return res;
}

RPN::~RPN() {};