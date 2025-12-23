#include "RPN.hpp"


int main(int argc, char const *argv[])
{
    RPN rpn_cal;
    std::string arg;
    if(argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    arg = argv[1];
    try
    {
        rpn_cal.check_input(arg);
        std::cout << rpn_cal.ft_get_result() << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
