#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <limits.h>

class PmergeMe
{
private:
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
   
    
    public:
    
    std::vector<int> array;
    PmergeMe();
    ~PmergeMe();
    void ft_pars(std::string arg);
    void ft_splite_sort(std::vector<int> &winners);
    std::vector<int> ft_set_jacobsthal_in_order(int size);
};
