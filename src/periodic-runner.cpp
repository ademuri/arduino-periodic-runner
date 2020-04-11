#include "periodic-runner.h"

#include <Arduino.h>

PeriodicRunner::PeriodicRunner() {}

void PeriodicRunner::Add(uint32_t run_every, FunctionType function) {
  Add(run_every, run_every, function);
}

void PeriodicRunner::Add(uint32_t run_every, uint32_t initial_delay,
                         FunctionType function) {
  functions_.push_back({run_every, initial_delay, function});
}

void PeriodicRunner::Run() {
  for (auto iter = functions_.begin(); iter != functions_.end(); iter++) {
    if (millis() > iter->run_at) {
      iter->function();
      iter->run_at = millis() + iter->run_every;
    }
  }
}
