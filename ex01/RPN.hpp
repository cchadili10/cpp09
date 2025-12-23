#pragma once

#include <iostream>
#include <exception>
#include <algorithm>
#include <stack>
#include <sstream>

class RPN
{
    private:
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        std::stack<int> rpn;
        int res;
    public:
        RPN();
        int ft_get_result()const;
        void check_input(std::string &arg);
        ~RPN();
};
