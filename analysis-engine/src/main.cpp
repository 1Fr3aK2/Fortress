#include <event.hpp>
#include <log_parser.hpp>
#include <attacker_profile.hpp>
#include <detection_engine.hpp>
#include <alert_writer.hpp>
#include <unordered_map>
#include <iostream>
#include <csignal>
#include <unistd.h>

static volatile sig_atomic_t g_stop = 0;

static void onSignal(int)
{
    g_stop = 1;
}

int main()
{
    std::signal(SIGTERM, onSignal);
    std::signal(SIGINT, onSignal);

    std::unordered_map<std::string, attacker> Profile;
    detectionEngine Engine;
    alertWriter Writer("/var/log/fortress/alerts/alerts.json");

    logParser parser("/var/log/fortress/events/events.json");
    Event e;

    const time_t windowSize = 60;
    while (!g_stop)
    {
        parseResult result = NO_EVENT;
        while (!g_stop && (result = parser.nextEvent(e)) == EVENT_READ)
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
        for (int i = 0; i < 60 && !g_stop; i++)
            sleep(1);
    }
    return 0;
}