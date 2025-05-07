#include "config.h"
#include <fstream>
#include <sstream>

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

void Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        auto delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            m_settings[key] = value;
        }
    }
}

std::string Config::get(const std::string& key, const std::string& defaultValue) const {
    auto it = m_settings.find(key);
    return it != m_settings.end() ? it->second : defaultValue;
}

int Config::getInt(const std::string& key, int defaultValue) const {
    try {
        return std::stoi(get(key, std::to_string(defaultValue)));
    } catch (...) {
        return defaultValue;
    }
}

float Config::getFloat(const std::string& key, float defaultValue) const {
    try {
        return std::stof(get(key, std::to_string(defaultValue)));
    } catch (...) {
        return defaultValue;
    }
}