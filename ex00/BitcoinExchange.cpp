#include "BitcoinExchange.hpp"
#include <cctype>
#include <sstream>
#include <exception>

BitcoinExchange::BitcoinExchange()
{
    std::string m[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};

    std::string d[12] = {"31", "28", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};

    check_data = false;
    check_value = false;

    for (int i = 0; i < 12; i++)
    {
        months[i] = m[i];
        days[i] = d[i];
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { *this = other; }

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        bitcoin = other.bitcoin;
    return *this;
}

bool BitcoinExchange::ft_find(std::string arr)
{
    for (size_t i = 0; i < 12; i++)
    {
        if (months[i] == arr)
            return true;
    }
    return false;
}

void ft_remove_spece(std::string &line, bool check)
{
    std::string err = "Error: bad input => ";
    if(check)
    {
        if (line[0] == 32 || line[0] == 9)
            throw std::runtime_error(err);
        if (line[line.size() - 1] != 32)
            throw std::runtime_error(err);
    
        line.erase(line.size() - 1);
        for (size_t i = 0; i < line.size(); i++)
        {
            if (line.at(i) != '-' && (line.at(i) < '0' || line.at(i) > '9'))
                throw std::runtime_error(err);
        }
    }
    else
    {
        if (line[0] != 32)
            throw std::runtime_error(err);
        line.erase(0, 1);
    }
}

void ft_is_valid_number(std::string line)
{
    bool has_dot = false;
    bool has_pos = false;
    bool has_neg = false;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line.at(i) == '.')
        {
            if (has_dot)
                throw std::runtime_error("Error: bad input =>");
            has_dot = true;
        }
        else if (line.at(i) == '-' || line.at(i) == '+')
        {
            if (i != 0)
                throw std::runtime_error("Error: bad input =>");
            else if (has_neg || has_pos)
                throw std::runtime_error("Error: bad input =>");
            else if (line.at(i) == '-')
                throw std::range_error("Error: not a positive number.");
            else
                has_pos = true;
        }
        else if (line.at(i) < '0' || line.at(i) > '9')
            throw std::runtime_error("Error: bad input =>");
    }
}

void BitcoinExchange::is_ValidDate(std::string &line, bool check)
{
    std::string input, year_, month, day, output;
    if(check)
        ft_remove_spece(line, true);
    
    if (std::count(line.begin(), line.end(), '-') != 2)
        throw std::runtime_error("Error: bad input => ");

    size_t index = line.find("-");
    year_ = line.substr(0, index);
    input = line.substr(index + 1, line.size() - index);
    index = input.find("-");
    month = input.substr(0, index);
    day = input.substr(index + 1, input.size() - index);
    if (year_.empty() || month.empty() || day.empty())
        throw std::runtime_error("Error: bad input => ");
    
    if (year_.size() != 4)
        throw std::runtime_error("Error: bad input => ");

    bool is_leap = false;

    int year = atoi(year_.c_str());
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        is_leap = true;
    if (day.size() > 2 || month.size() > 2)
        throw std::runtime_error("Error: bad input => ");
    else
    {
        if (day.size() == 1)
            day.insert(day.begin(), '0');
        if (month.size() == 1)
            month.insert(month.begin(), '0');
    }

    if (!ft_find(month))
        throw std::runtime_error("Error: bad input => ");
    else if (month == months[1] && is_leap)
    {
        if (day < "01" || day > "29")
            throw std::runtime_error("Error: bad input => ");
    }
    else if(day < "01" ||  day > days[atoi(month.c_str()) - 1])
        throw std::runtime_error("Error: bad input => ");

    line =  year_ + "-" + month + "-" + day;
}
double BitcoinExchange::is_ValidPrice(std::string line, bool check, bool check_data)
{
    if(check_data)
        ft_remove_spece(line, false);
    ft_is_valid_number(line);
    double value = atof(line.c_str());
    if (value < 0 || (value > 1000 && check))
    {
        (value < 0) ? throw std::range_error("Error: not a positive number.") : throw std::range_error("Error: too large a number.");
    }
    return value;
}

void BitcoinExchange::ft_checkInput(std::string line)
{
    if (line == "date | value" || line.empty())
    {
        if (line == "date | value" && check_data)
            std::cout << "Error: bad input => " << line << std::endl;
        if (line == "date | value")
            check_data = true;
        return;
    }
    check_data = true;
    size_t index = line.find('|');
    if (index == std::string::npos || std::count(line.begin(), line.end(), '|') != 1)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }
    
    std::string value_st, date;
    date = line.substr(0, index);
    value_st = line.substr(index + 1, line.size() - index);
    double value = 0;
    try
    {
        is_ValidDate(date, true);
        value = is_ValidPrice(value_st, true, true);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << " " << line << '\n';
        return ;
    }
    std::map<std::string, double>::iterator it = bitcoin.lower_bound(date);
    if (it == bitcoin.begin() && it->first != date)
        std::cout << "Error: No earlier date available" << std::endl;
    else if (it != bitcoin.end())
    {
        if(it->first == date)
        {
            double val = bitcoin[it->first] * value;
            std::cout << date << " => " << value << " = " << val << std::endl;
        }
        else
        {
            it--;
            double val = it->second * value;
            std::cout << date << " => " << value << " = " << val << std::endl;
        }
    }
}

void BitcoinExchange::ft_checkInput_data(std::string line)
{
    (void)line;
    double value = 0;
    size_t index = line.find(',');

    if (line == "date,exchange_rate" || line.empty())
    {
        if (line == "date,exchange_rate" && check_value)
            throw std::runtime_error("database corrupted");
        if (line == "date,exchange_rate")
            check_value = true;
        return ;
    }
    check_value = true;
    if (index == std::string::npos || std::count(line.begin(), line.end(), ',') != 1)
        throw std::runtime_error("database corrupted");
    std::string value_st, date;
    date = line.substr(0, index);
    value_st = line.substr(index + 1, line.size() - index);
    try
    {
        is_ValidDate(date, false);
        value = is_ValidPrice(value_st, false, false);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << " " << line << '\n';
        throw std::runtime_error("database corrupted");
    }
    bitcoin.insert(std::make_pair(date, value));
}

BitcoinExchange::~BitcoinExchange() {};