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
        int holder = jacob_generate.at(i);
        int holder_order = jacob_generate.at(i - 1);
        while (holder_order < holder)
        {
            order.push_back(holder);
            holder--;
        }
    }
    order.push_back(0);
    return order;
}

void PmergeMe::ft_splite_sort(std::vector<int> &winners)
{
    if(winners.size() == 1)
        return ;

    std::vector<int> winner;
    std::vector<int> loser;
    bool has_remain = false;

    for (size_t i = 0; i < array.size() - 1; i += 2)
    {
        int first = array.at(i);
        int second = array.at(i + 1);

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
    if (array.size() % 2 == 1)
    {
        remain_number = array[array.size() - 1];
        has_remain = true;
    }
    ft_splite_sort(winner);

    if(!loser.empty())
    {

    }

}
