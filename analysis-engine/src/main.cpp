#include <event.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <log_parser.hpp>


int main()
{
    Event e;
    logParser parser("tests/sample_events.json");

    while (parser.nextEvent(e))
    {
        std::cout << "Timestamp: " << e.timestamp << std::endl;
        std::cout << "IP: " << e.srcIp << std::endl;
        std::cout << "Port: " << e.port << std::endl;
        std::cout << "User: " << e.user << std::endl;
        std::cout << "Password: " << e.password << std::endl;
        std::cout << "Client Version: " << e.clientVersion << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    return 0;
}