#include <Inifile_esp32.h>

void setup()
{
  Serial.begin(115200);

  Inifile_ESP32 iniConfig("/config.ini");

  String login = iniConfig.getValue("wifi", "login");
  Serial.println("Login: " + login);
  
  String smtpPort = iniConfig.getValue("mail", "smtp_port");
  Serial.println("SMTP Port: " + smtpPort);
}

void loop() {}
