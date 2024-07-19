#include "simulation_timer.hpp"

SimulationTimer::SimulationTimer()
{
  reset();
  mTimeScale = 1.0;
  mDeltaTime = std::chrono::duration<double>(0.0);
}

SimulationTimer::~SimulationTimer() {}

void SimulationTimer::reset()
{
  mStartTime = std::chrono::system_clock::now();
}

double SimulationTimer::deltaTime()
{
  return mDeltaTime.count();
}

void SimulationTimer::timeScale(double t)
{
  mTimeScale = t;
}

double SimulationTimer::timeScale()
{
  return mTimeScale;
}

void SimulationTimer::tick()
{
  mDeltaTime = std::chrono::system_clock::now() - mStartTime;
}
