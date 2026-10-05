#include <event.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <log_parser.hpp>
#include <attacker_profile.hpp>


int main()
{
    Event e;
    logParser parser("tests/sample_events.json");
    std::unordered_map<std::string, attackerProfile> Profile;
    while (parser.nextEvent(e))
    {
        if (!processEvents(e, Profile))
        {
            std::cerr << "Error processing Events\n";
            return -1;
        }
    }
    std::unordered_map<std::string, attackerProfile>::iterator it;
    for (it = Profile.begin(); it != Profile.end(); ++it)
    {
        std::cout << "IP: " << it->first << std::endl;
        std::cout << "Total attempts: " << it->second.total << std::endl;
        std::cout << "-----------------------------" << std::endl;
        for (size_t i = 0; i < it->second.total; i++)
        {
            std::cout << "Timestamp: " << it->second.timestamps[i] << std::endl;
            std::cout << "Port: " << it->second.port[i] << std::endl;
            std::cout << "User: " << it->second.user[i] << std::endl;
            std::cout << "Password: " << it->second.password[i] << std::endl;
            std::cout << "Client Version: " << it->second.clientVersion[i] << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }
    return 0;
}
