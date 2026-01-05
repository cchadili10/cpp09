#pragma once

#include <algorithm>
#include <iostream>
#include <exception>
#include <map>
#include <list>

class BitcoinExchange
{
    private:
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        std::map<std::string, double> bitcoin;
        std::string months[12];
        std::string days[12];
        int check_value;
        int check_data;
        
        public:
        ~BitcoinExchange();
        BitcoinExchange();

        bool ft_find(std::string str);
        void ft_checkInput_data(std::string line);
        void ft_checkInput(std::string line);
        void is_ValidDate(std::string &line, bool check);
        double is_ValidPrice(std::string line, bool check, bool check_data);
        std::string ft_check_date(std::string &date, int i);
};
