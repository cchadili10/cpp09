#include "PmergeMe.hpp"


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
        pgm.ft_splite_sort_deque(pgm.array_dq);
    
        std::cout << "\n";
        for (size_t i = 0; i < pgm.array.size(); i++)
        {
            std::cout << pgm.array.at(i) << " ";
        }
        std::cout << "\n";
        for (size_t i = 0; i < pgm.array_dq.size(); i++)
        {
            std::cout << pgm.array_dq.at(i) << " ";
        }
        // bool sorted = true;
        // for (size_t i = 1; i < pgm.array.size(); i++)
        // {
        //     if (pgm.array[i] < pgm.array[i-1])
        //     {
        //         sorted = false;
        //         std::cout << "ERROR at position " << i << ": " << pgm.array[i-1] << " > " << pgm.array[i] << std::endl;
        //     }
        // }
        // if (sorted)
        //     std::cout << "\n Array is properly sorted!" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    // std::cout << std::endl;
    // std::vector<int> order = ft_set_jacobsthal_in_order(argc -  1);
    // for (size_t i = 0; i < order.size(); i++)
    // {
    //     std::cout <<  order.at(i) << " ";
    // }

    return 0;
}
