#ifndef PERIODIC_RUNNER_H
#define PERIODIC_RUNNER_H

#include <functional>
#include <vector>

class PeriodicRunner {
#ifdef __AVR__
  // avr-gcc doesn't have std::function - fortunately, std::function is
  // "backwards-compatible" with raw function pointers.
  typedef void (*const FunctionType)();
#else
  // On modern platforms that have std::function, this allows callers to e.g.
  // use `bind` here. It's backwards compatible with old-style function
  // pointers.
  typedef std::function<void()> FunctionType;
#endif

 public:
  PeriodicRunner();

  // Adds a function to run at the specified interval, in milliseconds. The
  // initial delay is also run_every.
  void Add(uint32_t run_every, FunctionType function);

  // Adds a function to run at the specified interval, in milliseconds, with the
  // specified initial delay.
  void Add(uint32_t run_every, uint32_t initial_delay, FunctionType function);

  void Run();

 private:
  struct FunctionData {
    const uint32_t run_every;
    uint32_t run_at;
    FunctionType function;
  };

  std::vector<FunctionData> functions_;
};

#endif  // DASHBOARD
