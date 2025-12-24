#include "PmergeMe.hpp"
#include <iomanip>


int main(int argc, char const *argv[])
{
    PmergeMe pgm;

    if (argc == 1)
        return 1;
    try
    {
        for (int i = 1; i < argc; i++)
        {
            pgm.ft_pars(argv[i]);
        }
        double start = getTimeInMicroseconds();
        pgm.ft_splite_sort(pgm.array);
        double end = getTimeInMicroseconds();
        double res = end - start;

        start = getTimeInMicroseconds();
        pgm.ft_splite_sort_deque(pgm.array_dq);
        end = getTimeInMicroseconds();
        double res_dq = end - start;
        std::cout << "Before:  ";
        for (size_t i = 0; i < pgm.values_before.size(); i++)
            std::cout << pgm.values_before[i] << " ";
        std::cout <<std::endl << "After:   ";
        for (size_t i = 0; i < pgm.array.size(); i++)
            std::cout << pgm.array[i] << " ";
        std::cout << std::fixed << std::setprecision(5);
        std::cout <<std::endl << "Time to process a range of " << argc-1 << " elements with std::vector : "<< res << " us";
        std::cout <<std::endl << "Time to process a range of "<<  argc-1 << " elements with std::vector : "<< res_dq << " us" << std::endl;
    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
