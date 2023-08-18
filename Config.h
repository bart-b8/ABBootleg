#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

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
    std::cout << "Config map contains:" << endl;
    for (std::map<std::string, double>::const_iterator it = config.begin();
         it != config.end(); ++it) {
      std::cout << it->first << "=" << it->second << endl;
    }
  }

  bool Set(const std::string &config_file) {
    std::fstream fs(config_file, std::fstream::in);
    if (!fs.is_open()) {
      return false;
    }

    config_.clear();

    std::string tag;
    while (!fs.eof()) {
      std::string line;
      // TODO(BD): improve stability and foolproofness by using getline() and
      // remove spaces (if there would be spaces in the wrong place in the ini
      // file, it would break)
      fs >> line;
      size_t pos1 = line.find('[');
      size_t pos2 = line.find(']');
      size_t pos3 = line.find('=');
      if (pos1 != std::string::npos) {
        tag = line.substr(pos1 + 1, pos2 - pos1 - 1);
      } else if (pos3 != std::string::npos) {
        std::string key = line.substr(0, pos3);
        key = tag + "." + key;
        double value = std::stod(line.substr(pos3 + 1));
        config_[key] = value;
      }
    }
    return true;
  }

  std::map<std::string, double> Map() const { return config_; }

 private:
  // Private default constructor
  Config() = default;

  std::map<std::string, double> config_;
};

#endif
