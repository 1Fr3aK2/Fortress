#include <event.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <log_parser.hpp>
#include <attacker_profile.hpp>
#include <sliding_window.hpp>


int main()
{
    Event e;
    logParser parser("tests/sample_events.json");
    const size_t windowSize = 60;
    std::unordered_map<std::string, attacker> Profile;
    while (parser.nextEvent(e))
    {
        if (!processEvents(e, Profile, windowSize))
        {
            std::cerr << "Error processing Events\n";
            return -1;
        }
        
    }
    std::unordered_map<std::string, attacker>::iterator it;
    for (it = Profile.begin(); it != Profile.end(); ++it)
    {
        std::cout << "IP: " << it->first << std::endl;
        std::cout << "Total attempts: " << it->second.profile.total << std::endl;
        std::cout << "-----------------------------" << std::endl;
        for (size_t i = 0; i < it->second.profile.total; i++)
        {
            std::cout << "Timestamp: " << it->second.profile.timestamps[i] << std::endl;
            std::cout << "Port: " << it->second.profile.port[i] << std::endl;
            std::cout << "User: " << it->second.profile.user[i] << std::endl;
            std::cout << "Password: " << it->second.profile.password[i] << std::endl;
            std::cout << "Client Version: " << it->second.profile.clientVersion[i] << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }
    return 0;
}
