#include "test_engine_power.hpp"

#include <chrono>
#include <cmath>
#include <thread>

TestEnginePower::TestEnginePower(int modelTime) : _modelTime{modelTime} {}
TestEnginePower::~TestEnginePower() {}

map<string, double> TestEnginePower::run(Engine* engine)
{
  double maxCrankshaftSpeed = engine->getCrankshaftSpeed();
  double maxPower = engine->getPower();
  double prevCrankshaftSpeed = -1;
  double curCrankshaftSpeed = engine->getCrankshaftSpeed();

  engine->run(_modelTime);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  while (abs(curCrankshaftSpeed - prevCrankshaftSpeed) > 0.1)
  {
    prevCrankshaftSpeed = curCrankshaftSpeed;

    double curPower = engine->getPower();
    curCrankshaftSpeed = engine->getCrankshaftSpeed();

    if (curPower > maxPower)
    {
      maxPower = curPower;
      maxCrankshaftSpeed = curCrankshaftSpeed;
    }
  }

  engine->stop();

  return {{"power", maxPower}, {"crankshaftSpeed", maxCrankshaftSpeed}};
}
