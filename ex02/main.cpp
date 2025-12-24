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
        // for (size_t i = 0; i < pgm.loser.size(); i++)
        // {
        //     std::cout << "loser = " << pgm.loser.at(i) << std::endl;
        // }
        // for (size_t i = 0; i < pgm.winner.size(); i++)
        // {
        //     std::cout << "winner  = " << pgm.winner.at(i) << std::endl;
        // }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    return 0;
}
