#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <stdexcept>

class ConfigError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class Config {
    public:
        static Config& getInstance();
        void loadFromFile(const std::string& filename);
        std::string get(const std::string& key, const std::string& defaultValue = "") const;
        int getInt(const std::string& key, int defaultValue = 0) const;
        float getFloat(const std::string& key, float defaultValue = 0.0f) const;

    private:
        Config() = default;
        std::unordered_map<std::string, std::string> m_settings;
};

#endif