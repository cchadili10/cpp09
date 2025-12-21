#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <list>

class BitcoinExchange
{
    private:
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        std::map<std::string, double>bitcoin;
        std::string months[12];
        std::string days[12];

    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void ft_checkInput_data(std::string line);
        void ft_checkInput(std::string line);
        std::string is_ValidDate(std::string line);
        double is_ValidPrice(std::string line, bool check);
        std::string ft_check_date(std::string &date, int i);
};
