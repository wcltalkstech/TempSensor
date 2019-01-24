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

  digitalWrite(D4, HIGH);
  Mesh.connect();
  Particle.connect();
  digitalWrite(D4, LOW);

}

void loop() {
  float temp = mcp.getTemperature();
  snprintf(buffer, sizeof(buffer), "%2.1f", temp);
  Particle.publish("tempUpdate", buffer);
  delay(5000);
}