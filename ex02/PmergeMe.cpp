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
    if(value > INT_MAX || value == 0)
        throw std::runtime_error("Error");
    array.push_back(static_cast<int>(value));
    array_dq.push_back(static_cast<int>(value));
    values_before.push_back(static_cast<int>(value));
    
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
        int holder = std::min(jacob_generate[i], size);
        int holder_order = jacob_generate.at(i - 1);
        while (holder > holder_order)
        {
            order.push_back(holder);
            holder--;
        }
    }
    return order;
}


void PmergeMe::ft_splite_sort(std::vector<int> &arr)
{
    if(arr.size() == 1)
        return ;
    
    std::vector<int> winner;
    std::vector<std::pair<int ,int> > pairs; // hold pair (2 . 4)

    int remain_number;
    bool has_remain = false;
    

    for (size_t i = 0; i < arr.size() - 1; i += 2) 
    {
        int first = arr.at(i);
        int second = arr.at(i + 1);

        if (first >= second)
            pairs.push_back(std::make_pair(first,second));
        else
            pairs.push_back(std::make_pair(second, first));
    }
    if (arr.size() % 2 == 1)
    {
        remain_number = arr[arr.size() - 1];
        has_remain = true;
    }

    for (size_t i = 0; i < pairs.size(); i++)
    {
        winner.push_back(pairs[i].first);
    }
    
    ft_splite_sort(winner);

    std::vector<std::pair<int ,int> > sorted_pair;

    for (size_t i = 0; i < winner.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if(pairs[j].first == winner[i])
            {
                sorted_pair.push_back(pairs[j]);
                pairs[j].first = -1;
                break ;
            }
        }
    }

    std::vector<int> main_ch;
    for (size_t i = 0; i < sorted_pair.size(); i++)
        main_ch.push_back(sorted_pair.at(i).first);
    
    main_ch.insert(main_ch.begin(), sorted_pair[0].second);
    if (sorted_pair.size() > 1)
    {
        std::vector<int> order = ft_set_jacobsthal_in_order(sorted_pair.size() - 1);
        for (size_t i = 0; i < order.size(); i++)
        {
            size_t index = order[i];
            int value = sorted_pair[index].second;
            std::vector<int>::iterator limet_search = main_ch.begin() + std::min(index + i + 1 , main_ch.size());
            std::vector<int>::iterator it = std::lower_bound(main_ch.begin(), limet_search, value);
            main_ch.insert(it, value);
        }
    }
    if (has_remain)
    {
        std::vector<int>::iterator it = std::lower_bound(main_ch.begin(), main_ch.end(), remain_number);
        main_ch.insert(it, remain_number);
    }
   arr = main_ch;
}



std::deque<int> PmergeMe::ft_set_jacobsthal_in_order_deque(int size)
{
    std::deque<int> order;
    std::deque<int> jacob_generate;
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
        int holder = std::min(jacob_generate[i], size);
        int holder_order = jacob_generate.at(i - 1);
        while (holder > holder_order)
        {
            order.push_back(holder);
            holder--;
        }
    } 
    return order;
}

void PmergeMe::ft_splite_sort_deque(std::deque<int> &arr)
{
    if(arr.size() == 1)
        return ;
    
    std::deque<int> winner;
    std::deque<std::pair<int, int> > pairs; // hold pair (2 . 4)

    int remain_number;
    bool has_remain = false;

    for (size_t i = 0; i < arr.size() - 1; i += 2)
    {
        int first = arr.at(i);
        int second = arr.at(i + 1);

        if (first >= second)
            pairs.push_back(std::make_pair(first, second));
        else
            pairs.push_back(std::make_pair(second, first));
    }
    if (arr.size() % 2 == 1)
    {
        remain_number = arr[arr.size() - 1];
        has_remain = true;
    }

    for (size_t i = 0; i < pairs.size(); i++)
    {
        winner.push_back(pairs[i].first);
    }

    ft_splite_sort_deque(winner);

    std::deque<std::pair<int, int> > sorted_pair;

    for (size_t i = 0; i < winner.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (pairs[j].first == winner[i])
            {
                sorted_pair.push_back(pairs[j]);
                pairs[j].first = -1;
                break;
            }
        }
    }

    std::deque<int> main_ch;
    for (size_t i = 0; i < sorted_pair.size(); i++)
        main_ch.push_back(sorted_pair.at(i).first);

    main_ch.insert(main_ch.begin(), sorted_pair[0].second);
    if (sorted_pair.size() > 1)
    {
        std::deque<int> order = ft_set_jacobsthal_in_order_deque(sorted_pair.size() - 1);
        for (size_t i = 0; i < order.size(); i++)
        {
            size_t index = order[i];
            int value = sorted_pair[index].second;
            std::deque<int>::iterator limet_search = main_ch.begin() + std::min(index + i + 1, main_ch.size());
            std::deque<int>::iterator it = std::lower_bound(main_ch.begin(), limet_search, value);
            main_ch.insert(it, value);
        }
    }
    if (has_remain)
    {
        std::deque<int>::iterator it = std::lower_bound(main_ch.begin(), main_ch.end(), remain_number);
        main_ch.insert(it, remain_number);
    }

    arr = main_ch;
}
// 77 302 622 983 930 588 19 91 72 734 536 275 680 927 713 
// 861 558 112 930 769 992 564 185 238 820 755 398 194 157
// 978 314 337 383 472 857 665 561 486 363 176 50 768 993 
// 69 855 452 101 494 213 713 464 892 995 509 749 268 460 
// 119 924 216 543 174 787 88 661 614 290 922 347 296 160 
// 312 710 961 188 147 969 973 120 5 434 962 633 227 502 43 
// 340 338 576 268 928 985 725 699 135 438 526 917 834 567