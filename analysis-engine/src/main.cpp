#include <event.hpp>
#include <log_parser.hpp>
#include <attacker_profile.hpp>
#include <detection_engine.hpp>
#include <alert_writer.hpp>
#include <unordered_map>
#include <iostream>
#include <unistd.h>

int main()
{
    std::unordered_map<std::string, attacker> Profile;
    detectionEngine Engine;
    alertWriter Writer("/var/log/fortress/alerts/alerts.json");
    
    logParser parser("/var/log/fortress/events/events.json");
    Event e;
    
    const time_t windowSize = 60;
    while(true)
    {
        parseResult result;
        while ((result = parser.nextEvent(e)) == EVENT_READ)
        {
            Alert alert(0, "", 0);
            if (!processEvents(e, Profile, windowSize, Engine, alert))
            {
                std::cerr << "Error processing Events\n";
                return -1;
            }
            if (alert.count > 0)
            {
                if (!Writer.writeAlert(alert))
                {
                    std::cerr << "Error writing alert\n";
                    return 1;
                }
            }
        }
        if (result == PARSE_ERROR)
        {
            std::cerr << "Error reading events\n";
            return 1;
        }
        sleep(60);
    }
    return 0;
}
