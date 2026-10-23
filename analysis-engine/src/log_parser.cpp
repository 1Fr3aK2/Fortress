#include <event.hpp>
#include <log_parser.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

logParser::logParser(const std::string& Path)
    : path(Path), file(Path.c_str()), current(), inEvent(false), bad(false)
{
}

logParser::~logParser()
{
    if (file.is_open())
        file.close();
}

// Aceita só linhas na forma   \t"chave": "valor"   (com vírgula opcional).
static bool splitField(const std::string& line, std::string& key, std::string& value)
{
    size_t kend;
    size_t start;
    size_t i;

    if (line.size() < 2 || line[0] != '\t' || line[1] != '"')
        return false;
    kend = line.find('"', 2);
    if (kend == std::string::npos || line.compare(kend + 1, 3, ": \"") != 0)
        return false;
    key = line.substr(2, kend - 2);
    start = kend + 4;
    i = start;
    while (i < line.size() && line[i] != '"')
    {
        if (line[i] == '\\')
            i++;                    // barra + caractere seguinte = uma unidade
        i++;
    }
    if (i >= line.size())
        return false;               // sem aspa de fecho
    value = line.substr(start, i - start);
    std::string tail = line.substr(i + 1);
    return tail.empty() || tail == ",";
}

bool logParser::parse(const std::string& Line, Event& ev)
{
    std::string key;
    std::string value;

    if (!splitField(Line, key, value))
        return false;
    if (key == "ip")
        ev.srcIp = value;
    else if (key == "timestamp")
    {
        std::tm tm = {};
        const char *end = strptime(value.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm);
        if (end == NULL || *end != '\0')
            return false;
        ev.timestamp = timegm(&tm);
    }
    else if (key == "port")
    {
        char *end;
        long port = strtol(value.c_str(), &end, 10);
        if (value.empty() || *end != '\0' || port < 0 || port > 65535)
            return false;
        ev.port = static_cast<uint16_t>(port);
    }
    else if (key == "client_version")
        ev.clientVersion = value;
    else if (key == "user")
        ev.user = value;
    else if (key == "password")
        ev.password = value;
    // chaves desconhecidas (como received_at) são ignoradas
    return true;
}

parseResult logParser::nextEvent(Event &event)
{
    std::string line;
    std::streampos pos;

    if (!file.is_open())
    {
        // o ficheiro pode ainda não existir (o logger cria-o): tenta outra vez
        file.clear();
        file.open(path.c_str());
        if (!file.is_open())
            return NO_EVENT;
    }
    while (true)
    {
        pos = file.tellg();
        if (!std::getline(file, line))
            break ;
        if (file.eof())
        {
            // última linha sem '\n': ainda está a ser escrita, volta ao início dela
            file.clear();
            file.seekg(pos);
            return NO_EVENT;
        }
        if (line == "{")
        {
            current = Event();
            inEvent = true;
            bad = false;
        }
        else if (line == "}")
        {
            bool ok = inEvent && !bad && !current.srcIp.empty();
            inEvent = false;
            if (ok)
            {
                event = current;
                return EVENT_READ;
            }
            std::cerr << "Skipping malformed event\n";
        }
        else if (inEvent && !bad && !parse(line, current))
            bad = true;
    }
    if (file.eof())
    {
        file.clear();
        return NO_EVENT;
    }
    return PARSE_ERROR;             // só para erros reais de leitura
}