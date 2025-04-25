#include "map.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    map<int, std::string> hobbits;
    std::ifstream name("names.txt");
    for (int i = 0; !name.eof(); i++)
    {
        std::string in;
        std::getline(name >> std::ws, in);
        hobbits.insert(i, in);
    }
    for (auto it = hobbits.begin(); it.hasNext(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
    }
    std::cout << std::endl
              << std::endl;

    std::cout << hobbits[6] << std::endl;
    hobbits[0] = "Tasha Oakbottom";
    std::cout << hobbits[0] << std::endl;
    hobbits[15] = "Brianna Button";
    std::cout << hobbits[15] << std::endl;

    std::cout << std::endl
              << std::endl;
    for (auto it = hobbits.begin(); it.hasNext(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << (*it).getValue() << std::endl;
    }
    std::cout << hobbits.at(7) << std::endl;

    return 0;
}