SYSTEM_MODE(MANUAL);

#include "MCP9808.h"

MCP9808 mcp = MCP9808();

const long interval = 10 * 1000;
unsigned long previousTime = 0;

char buffer[100];

void setup() {

  pinMode(D4, OUTPUT);
  // Use external antenna
  digitalWrite(ANTSW1, 0);
  digitalWrite(ANTSW2, 1);

  while (! mcp.begin()) {
    delay(500);
  }

}

void loop() {
  unsigned long currentTime = millis();

  if ( currentTime - previousTime >= interval) {
    previousTime = currentTime;
    Mesh.on();
    Mesh.connect();
    while (Mesh.connecting()) {
      // Wait until connected
    }
    if (Mesh.ready()) {
      float temp = mcp.getTemperature();
      snprintf(buffer, sizeof(buffer), "%2.1f", temp);
      Particle.publish("newTemp", buffer);
      Mesh.off();
      digitalWrite(D4, HIGH);
      delay(1000);
      digitalWrite(D4, LOW);
    }
  }
}