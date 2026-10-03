#include <event.hpp>
#include <fstream>
#include <iostream>
#include <sstream>


int main()
{
    std::ifstream file("tests/sample_events.json");
    if (!file.is_open())
    {
        std::cerr << "Error: error opening the file\n";
        return 1;
    }

    std::string line;
    size_t n = 1;
    while (std::getline(file, line))
        std::cout << n++ << ": [" << line << "]" << std::endl;
    return 0;   
}