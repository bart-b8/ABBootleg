#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

class Config {
  public:
    // No copy constructor
    Config(const Config &) = delete;
    // No copy assignment operator
    Config &operator=(const Config &) = delete;

    static Config &Get() {
        // static function variables are created only when used
        static Config instance;
        return instance;
    }

    void Print(const std::map<std::string, double> &config) {
        // TODO
    }

    bool Set(const std::string &config_file) {
        // TODO
        return false;
    }

    std::map<std::string, double> Map() const {
        return config_;
    }

  private:
    // Private default constructor
    Config() = default;

    std::map<std::string, double> config_;
};

#endif