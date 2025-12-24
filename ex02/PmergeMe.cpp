#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other) 
{
    (void)other;
    return *this; 
}
PmergeMe::~PmergeMe() {}



void PmergeMe::ft_pars(std::string arg)
{
    for (size_t i = 0; i < arg.size(); i++)
    {
        if (!isalnum(arg.at(i)))
        {
            if ((arg.at(i) == '+' && i != 0) || arg.at(i) != '+' )
                throw std::runtime_error("Error");
            
        }
    
    }
    double value = atof(arg.c_str());
    if(value > INT_MAX)
        throw std::runtime_error("Error");
    array.push_back(static_cast<int>(value));
    
}

std::vector<int> PmergeMe::ft_set_jacobsthal_in_order(int size)
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
#include <algorithm>
void PmergeMe::ft_splite_sort(std::vector<int> &arr)
{
    if(arr.size() == 1)
        return ;

    std::vector<int> winner;
    std::vector<int> loser;
    int remain_number;
    bool has_remain = false;

    for (size_t i = 0; i < arr.size() - 1; i += 2)
    {
        int first = arr.at(i);
        int second = arr.at(i + 1);

        if (first >= second)
        {
            winner.push_back(first);
            loser.push_back(second);
        }
        else
        {
            winner.push_back(second);
            loser.push_back(first);
        }
    }
    if (arr.size() % 2 == 1)
    {
        remain_number = arr[arr.size() - 1];
        has_remain = true;
    }
    ft_splite_sort(winner);

    if(!loser.empty())
    {
        winner.insert(winner.begin(), loser[0]);
        if(loser.size() > 1)
        {
            std::vector<int> order = ft_set_jacobsthal_in_order(loser.size()-1);
            for (size_t i = 0; i < order.size() ; i++)
            {
                size_t index = order[i];
                std::vector<int>::iterator it = std::lower_bound(winner.begin(),winner.end(),loser[index]);
                winner.insert(it,loser[index]);
            }
        }
        
    }
    if (has_remain)
    {
        std::vector<int>::iterator it = std::lower_bound(winner.begin(), winner.end(), remain_number);
        winner.insert(it, remain_number);
    }
    arr = winner;
}
