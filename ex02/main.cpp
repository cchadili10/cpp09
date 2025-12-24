#include "PmergeMe.hpp"
std::vector<int> ft_set_jacobsthal_in_order(int size)
{
    std::vector<int> order;
    std::vector<int> jacob_generate;
    jacob_generate.push_back(1);
    jacob_generate.push_back(3);
    while (jacob_generate.back() < size)
    {
        int holder = jacob_generate.back() + 2 * jacob_generate.at(jacob_generate.size() - 2);
        jacob_generate.push_back(holder);
    }
    order.push_back(1);
    for (size_t i = 1; i < jacob_generate.size(); i++)
    {
        // int holder = jacob_generate.at(i);
        int holder = std::min(jacob_generate[i], size - 1);
        int holder_order = jacob_generate.at(i - 1);
        while (holder_order < holder)
        {
            order.push_back(holder);
            holder--;
        }
    }
    // order.push_back(0);
    return order;
}

int main(int argc, char const *argv[])
{
    PmergeMe pgm;

    if (argc == 0)
        return 1;
    try
    {
        for (int i = 1; i < argc; i++)
        {
            pgm.ft_pars(argv[i]);
        }
        pgm.ft_splite_sort(pgm.array);
        for (size_t i = 0; i < pgm.array.size(); i++)
        {
            std::cout << pgm.array.at(i) << " ";
        }
        // for (size_t i = 0; i < pgm.winner.size(); i++)
        // {
        //     std::cout << "winner  = " << pgm.winner.at(i) << std::endl;
        // }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << std::endl;
    std::vector<int> order = ft_set_jacobsthal_in_order(argc -  1);
    for (size_t i = 0; i < order.size(); i++)
    {
        std::cout <<  order.at(i) << " ";
    }

    return 0;
}
