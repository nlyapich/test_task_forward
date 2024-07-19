#include "test_engine_temperature.hpp"

#include <chrono>
#include <cmath>
#include <thread>

TestEngineTemperature::TestEngineTemperature(int modelTime) : _modelTime{modelTime} {}
TestEngineTemperature::~TestEngineTemperature() {}

map<string, double> TestEngineTemperature::run(Engine* engine)
{
  double overheatingTemperature = engine->getOverheatingTemperature();
  double curTemperature = engine->getTemperature();

  auto start = std::chrono::steady_clock::now();

  engine->run(_modelTime);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  while (abs(overheatingTemperature - curTemperature) > 0.1)
  {
    curTemperature = engine->getTemperature();
  }

  auto stop = std::chrono::steady_clock::now();
  engine->stop();

  auto time = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

  return {{"time", time.count()*_modelTime}};
}
