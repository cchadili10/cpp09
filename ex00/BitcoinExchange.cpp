#include "BitcoinExchange.hpp"
#include <cctype>
#include <sstream>
#include <exception>

BitcoinExchange::BitcoinExchange()
{
    std::string m[12] =
        {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};

    std::string d[12] =
        {"31", "28", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};

    for (int i = 0; i < 12; i++)
    {
        months[i] = m[i];
        days[i] = d[i];
    }
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){*this = other;}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if(this != &other)
        bitcoin = other.bitcoin;
    return *this;
}

bool ft_isNum(std::string &line)
{
    for (size_t i = 0; i < line.size(); i++)
    {
        if(!isalnum(line.at(i)))
            return false;
    }
    return true;
}
void ft_remove_spece(std::string &line)
{
    bool first = true;
    for (size_t i = 0; i < line.size();)
    {
        if ((line.at(i) ==  9 || line.at(i) == 32) && first )
            line.erase(0, 1);
        else
        {
            first = false;
            i++;
        }
    }
    first = true;
    for (size_t i = line.size(); i > 0; )
    {
        i--;
        if ((line.at(i) == 9 || line.at(i) == 32) && first)
            line.erase(line.begin()+i);
        else
            first = false;
    }
}

void ft_is_valid_number(std::string line)
{
    bool has_dot = false;
    bool has_pos = false;
    bool has_neg = false;
    for (size_t i = 0; i < line.size(); i++)
    {
        if(line.at(i) == '.')
        {
            if(has_dot)
                throw std::runtime_error("Error: not a valid number.");
            has_dot = true;
        }
        else if (line.at(i) == '-' || line.at(i) == '+')
        {
            if(i != 0)
                throw std::runtime_error("Error: not a valid number.");
            else if( has_neg || has_pos)
                throw std::runtime_error("Error: not a valid number.");
            else if (line.at(i) == '-')
                has_neg = true;
            else
                has_pos = true;
        }
        else if(line.at(i) < '0' || line.at(i) > '9')
            throw std::runtime_error("Error: not a valid number.");
    }
    
}

std::string BitcoinExchange::is_ValidDate(std::string line)
{
    std::string input, year_, month, day, output;
    ft_remove_spece(line);
    if (std::count(line.begin(), line.end(), '-') != 2)
        return "";
    else
    {
        std::string split_date = line;
        std::istringstream iss(split_date);
        bool is_leap = false;
        for (size_t i = 0; i < 3; i++)
        {
            std::getline(iss, input, '-');
            if (i == 0)
            {
                if (!ft_isNum(input))
                    return "";
                int year = atoi(input.c_str());
                if (year < 1900 || year > 9999)
                    return "";
                if(year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
                    is_leap = true;
                year_ = input;
            }
            else if (i == 1)
            {
                if (!ft_isNum(input))
                    return "";
                if (input.size() <= 2)
                {
                    if (input.size() == 1)
                        input.insert(input.begin(), '0');
                    if (std::find(months, months + 12, input) == months + 12)
                        return "";
                }
                else  return"";
                month = input;
            }

            else
            {
                if (!ft_isNum(input))
                    return "";
                if (input.size() <= 2)
                {
                    if (input.size() == 1)
                        input.insert(input.begin(), '0');
                    if(input == months[1] && is_leap)
                    {
                        if (input < "01" && input > "29")
                            return "";
                    }
                    else if (input < "01" || input > days[atoi(month.c_str()) - 1])
                        return "";
                }
                else return"";
                day = input;
            }
        }
        
    }
    return year_+ "-" + month + "-" + day;
}
double BitcoinExchange::is_ValidPrice(std::string line, bool check)
{
    ft_remove_spece(line);
    ft_is_valid_number(line);
    double value = atof(line.c_str());
    if (value < 0 || (value > 1000 && check))
    {
        (value < 0) ? throw std::runtime_error("Error: not a positive number.") : throw std::runtime_error("Error: too large a number.");
    }
    return value;
}

void BitcoinExchange::ft_checkInput(std::string line)
{
    if (line.find('|') == std::string::npos || std::count(line.begin(),line.end(),'|') != 1)
        return ;
    bool has_error = false;
    std::string input , date;
    double value = 0;
    (void) value;
    std::istringstream iss(line);
    for (size_t i = 0; i < 2; i++)
    {
        std::getline(iss, input, '|');
        if(i % 2 == 0)
        {
            date = is_ValidDate(input);
            if(date.empty())
            {
                date = "Error: bad input => " + input;
                has_error = true;
            }
        }
        else if( i  == 1)
        {
            try
            {
                value = is_ValidPrice(input, true);
            }
            catch(const std::exception& e)
            {
                date = e.what();
                has_error = true;
                value = -1;
            }
        }
    }
    if(has_error)
        std::cout << date << std::endl;
    else
    {
        std::map<std::string, double>::iterator it = bitcoin.lower_bound(date);
        if(it != bitcoin.end() && it->first == date)
        {
            double val =  bitcoin[date] * value;
            std::cout << date << " => " << val << " = " << bitcoin[date] << std::endl;
        }
        else if(it == bitcoin.begin())
            std::cout << "Error: No earlier date available";
        else
        {
            it--;
            double val = it->second * value;
            std::cout << date << " => " << val << " = " << it->second << std::endl;
        }
    }
}

void BitcoinExchange::ft_checkInput_data(std::string line)
{
    std::string input, date, day;
    double value = 0;
    if (line.find(',') == std::string::npos || std::count(line.begin(), line.end(), ',') != 1)
        return;

    std::istringstream iss(line);
    
    for (size_t i = 0; i < 2; i++)
    {
        std::getline(iss, input, ',');
        if (i % 2 == 0)
        {
            date = is_ValidDate(input);
            if (date.empty())
                return ;
        }
        else if (i == 1)
        {
            try
            {
                value = is_ValidPrice(input, false);
            }
            catch (const std::exception &e)
            {
                return ;
            }
        }
    }
    bitcoin.insert(std::make_pair(date, value));
   
}

BitcoinExchange::~BitcoinExchange(){};