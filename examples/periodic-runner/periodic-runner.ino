#include <periodic-runner.h>

PeriodicRunner runner;

void PrintTime() {
  Serial.println(millis());
}

void setup() {
  Serial.begin(115200);

  // This will run PrintTime every 1 second. Works on all platforms.
  runner.Add(1000, PrintTime);

  // This will only work on platforms that support lambdas (most non-AVR platforms).
#ifndef __AVR__
  runner.Add(2000, []() {
    Serial.println("lambda");
  });
#endif // __AVR__
}

void loop() {
  runner.Run();
}
