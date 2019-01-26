#include "application.h"
#line 1 "/Users/kevinmcquown/Dropbox/WCL/wcltalkstech/TempSensorProject/TempSensor/src/TempSensor.ino"
void setup();
void loop();
#line 1 "/Users/kevinmcquown/Dropbox/WCL/wcltalkstech/TempSensorProject/TempSensor/src/TempSensor.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include "MCP9808.h"

MCP9808 mcp = MCP9808();

char buffer[100];

void setup() {

  pinMode(D4, OUTPUT);
  // Use external antenna
  digitalWrite(ANTSW1, 0);
  digitalWrite(ANTSW2, 1);

  while (! mcp.begin()) {
    delay(500);
  }

  Mesh.connect();
  Particle.connect();

}

void loop() {
  float temp = mcp.getTemperature();
  snprintf(buffer, sizeof(buffer), "%2.1f", temp);
  Particle.publish("newTemp", buffer);
  delay(5000);
  digitalWrite(D4, HIGH);
  delay(1000);
  digitalWrite(D4, LOW);

}