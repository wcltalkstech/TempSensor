SYSTEM_THREAD(ENABLED);
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

uint8_t count = 0;

float temp;

void loop() {
  unsigned long currentTime = millis();

  if ( currentTime - previousTime >= interval) {
    previousTime = currentTime;
    Mesh.on();
    Mesh.connect();
    waitUntil(Mesh.connecting);
    waitUntil(Mesh.ready);
    temp = mcp.getTemperature();
    delay(50);
    snprintf(buffer, sizeof(buffer), "%2.1f", temp);
    Mesh.publish("newTemp", buffer);
    Mesh.off();
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);

  }
}