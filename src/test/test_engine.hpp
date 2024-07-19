#ifndef TEST_ENGINE_HPP
#define TEST_ENGINE_HPP

#include <map>
#include <string>

#include "engine.hpp"

using namespace std;

class TestEngine
{
public:
  virtual ~TestEngine() {};

  virtual map<string, double> run(Engine*) = 0;
};

#endif // TEST_ENGINE_HPP
