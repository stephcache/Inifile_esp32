#include "Inifile_ESP32.h"

Inifile_ESP32::Inifile_ESP32(const String& filename) {
  if (!SD.begin(5)) {
    Serial.println("Erreur lors de la montée de la carte SD");
    return;
  }

  configFile = SD.open(filename);
  if (!configFile) {
    Serial.println("Erreur lors de l'ouverture du fichier");
    return;
  }

  loadConfigData();
}

Inifile_ESP32::~Inifile_ESP32() {
  if (configFile) {
    configFile.close();
  }
}

void Inifile_ESP32::loadConfigData() {
  if (!configFile) {
    Serial.println("Aucun fichier de configuration ouvert");
    return;
  }

  String currentSection = "";
  String line;

  while (configFile.available()) {
    line = configFile.readStringUntil('\n');
    line.trim();

    if (line.startsWith("[") && line.endsWith("]")) {
      currentSection = line.substring(1, line.length() - 1);
      configData.emplace_back(currentSection, std::vector<std::pair<String, String>>());
    }
    else if (!currentSection.isEmpty()) {
      int separatorIndex = line.indexOf('=');

      if (separatorIndex != -1) {
        String currentKey = line.substring(0, separatorIndex);
        currentKey.trim();

        String value = line.substring(separatorIndex + 1);
        value.trim();

        configData.back().second.emplace_back(currentKey, value);
      }
    }
  }
}

String Inifile_ESP32::getValue(const String& section, const String& key) {
  for (const auto& configSection : configData) {
    if (configSection.first == section) {
      for (const auto& keyValue : configSection.second) {
        if (keyValue.first == key) {
          return keyValue.second;
        }
      }
    }
  }

  return "";
}