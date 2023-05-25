#ifndef INIFILE_ESP32_H
#define INIFILE_ESP32_H

#include <SD.h>
#include <vector>

class Inifile_ESP32 {
public:
  Inifile_ESP32(const String& filename);
  ~Inifile_ESP32();
  
  String getValue(const String& section, const String& key);
  
private:
  File configFile;
  std::vector<std::pair<String, std::vector<std::pair<String, String>>>> configData;

  void loadConfigData();
};

#endif