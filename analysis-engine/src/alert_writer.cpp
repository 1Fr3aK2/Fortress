#include <alert_writer.hpp>
#include <detection_engine.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

Alert::Alert(time_t Timestamp, const std::string& Ip, size_t Total) : timestamp(Timestamp), ip(Ip), count(Total) {
}

alertWriter::alertWriter(const std::string& Path) : filePath(Path) {
}

static std::string formatTimestamp(time_t Timestamp)
{
    struct tm* TimeInfo = gmtime(&Timestamp);
    if (TimeInfo == NULL)
        return "";
    char buffer[21];
    if (strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", TimeInfo) == 0)
        return "";
    return std::string(buffer);
}

bool alertWriter::writeAlert(const Alert& Alert)
{
    std::ofstream File(filePath.c_str(), std::ios::app);
    if (!File.is_open())
        return false;
    nlohmann::json Json;
    Json["timestamp"] = formatTimestamp(Alert.timestamp);
    Json["ip"] = Alert.ip;
    Json["type"] = Alert.type;
    Json["severity"] = Alert.severity;
    Json["message"] = Alert.message;
    Json["count"] = Alert.count;
    File << Json.dump() << '\n';
    return File.good();
}

Alert buildAlert(time_t Timestamp, const std::string& Ip, time_t Windowsize, size_t Total)
{
    Alert Alert(Timestamp, Ip, Total);
    Alert.type = "brute_force";
    Alert.severity = "Warning";
    if (Total >= BRUTE_FORCE_CRITICAL_THRESHOLD)
        Alert.severity = "Critical";
    Alert.message = std::to_string(Total) + " attempts in " + std::to_string(Windowsize) + " seconds";
    return Alert;    
}