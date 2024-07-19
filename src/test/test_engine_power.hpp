#ifndef TEST_ENGINE_POWER_HPP
#define TEST_ENGINE_POWER_HPP

#include "test_engine.hpp"

class TestEnginePower: public TestEngine
{
public:
  TestEnginePower(int modelTime);
  virtual ~TestEnginePower();

  map<string, double> run(Engine*) override;

private:
  int _modelTime;
};

#endif // TEST_ENGINE_POWER_HPP
