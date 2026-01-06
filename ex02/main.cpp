#include "PmergeMe.hpp"
#include <iomanip>

// template<typename Container>
// bool is_sorted(const Container& container) {
//     // Empty or single-element containers are always sorted
//     if (container.size() <= 1) {
//         return true;
//     }
    
//     // Check if each element is <= the next element
//     for (size_t i = 0; i < container.size() - 1; ++i) {
//         if (container[i] > container[i + 1]) {
//             return false;
//         }
//     }
    
//     return true;
// }

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
        clock_t start = clock();
        pgm.ft_splite_sort(pgm.array);
        clock_t end = clock();
        double res_vec = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC;

        start = clock();
        pgm.ft_splite_sort_deque(pgm.array_dq);
        end = clock();
        double res_dq = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC;
        std::cout << "Before:  ";
        for (size_t i = 0; i < pgm.values_before.size(); i++)
            std::cout << pgm.values_before[i] << " ";
        std::cout <<std::endl << "After:   ";
        for (size_t i = 0; i < pgm.array.size(); i++)
            std::cout << pgm.array[i] << " ";
        std::cout << std::fixed << std::setprecision(5);
        std::cout <<std::endl << "Time to process a range of " << argc - 1 << " elements with std::vector : "<< res_vec << " us";
        std::cout <<std::endl << "Time to process a range of "<<  argc - 1 << " elements with std::deque  : "<< res_dq << " us" << std::endl;
        // if ( !is_sorted(pgm.array))
        //     std::cout << "Array was not sorted !!!!" << std::endl;
        // if ( !is_sorted(pgm.array_dq))
        //     std::cout << "Deque was not sorted !!!!" << std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
