#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <set>
#include <fstream>

int main()
{
    // lecture activity create a regular expression to divide up a tab-separated string
    // change the loop to parse a tab-separated string.
    
    std::regex commaStr{R"(((?:\w+\s*)+(?=,|$)))"};
    std::regex tabStr{R"([^\t]+)"};
    std::ifstream in("test.txt");
    while (!in.eof() && in.is_open())
    {
        std::string line;
        std::getline(in, line);
        const std::sregex_iterator end;
        for (std::sregex_iterator iter{std::cbegin(line), std::cend(line), tabStr}; iter != end; ++iter)
        {
            std::cout << (*iter)[0].str() << std::endl;
        }
    }
    return 0;
}
