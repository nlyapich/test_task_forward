#ifndef TEST_ENGINE_TEMPERATURE_HPP
#define TEST_ENGINE_TEMPERATURE_HPP

#include "test_engine.hpp"

class TestEngineTemperature: public TestEngine
{
public:
  TestEngineTemperature(int modelTime);
  virtual ~TestEngineTemperature();

  map<string, double> run(Engine*) override;

private:
  int _modelTime;
};

#endif // TEST_ENGINE_TEMPERATURE_HPP
