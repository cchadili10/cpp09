#include "BitcoinExchange.hpp"
#include <fstream>

int main(int argc, char const *argv[])
{
    try
    {
        BitcoinExchange btc;
        std::string line, line_data;
        if (argc != 2)
        {
            std::cerr << "Error: wrong number of arguments, btc takes the name of the file only." << std::endl;
            return 1;
        }
        std::ifstream file(argv[1]);
        std::ifstream file_data("data.csv");
        if (!file.is_open() || !file_data.is_open())
        {
            std::cerr << "Error: could not open file";
            return 1;
        }

        while (std::getline(file_data, line_data))
            btc.ft_checkInput_data(line_data);

        while (std::getline(file, line))
            btc.ft_checkInput(line);
        file.close();
        file_data.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    

    return 0;
}
