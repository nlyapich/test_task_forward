#ifndef SIMULATION_TIMER_HPP
#define SIMULATION_TIMER_HPP

#include <chrono>

class SimulationTimer
{
public:
  SimulationTimer();
  virtual ~SimulationTimer();

  void reset();
  double deltaTime();
  void timeScale(double t = 1.0);
  double timeScale();
  void tick();

private:
  std::chrono::system_clock::time_point mStartTime;
  std::chrono::duration<double> mDeltaTime;
  double mTimeScale;
};

#endif // SIMULATION_TIMER_HPP
