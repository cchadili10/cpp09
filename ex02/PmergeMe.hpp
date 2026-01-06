#ifndef PMERGEME
#define PMERGEME


#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <limits.h>
#include <algorithm>
#include <deque>
#include <ctime>

class PmergeMe
{
    private:
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        public:
        std::vector<int> values_before;
        std::vector<int> array;
        std::deque<int> array_dq;

        PmergeMe();
        ~PmergeMe();
        void ft_pars(std::string arg);
        void ft_splite_sort(std::vector<int> &winners);
        std::vector<int> ft_set_jacobsthal_in_order(int size);

        void ft_splite_sort_deque(std::deque<int> &winners);
        std::deque <int> ft_set_jacobsthal_in_order_deque(int size);
};

#endif