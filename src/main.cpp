#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <map>

#include <nlohmann/json.hpp>

#include "engine.hpp"
#include "internal_combustion_engine.hpp"
#include "test_engine_temperature.hpp"
#include "test_engine_power.hpp"

using namespace std;

using json = nlohmann::json;

int main()
{
  ifstream in("example/config.json");
  json j;
  in >> j;
  in.close();

  double momentInertia = j["I"];
  vector<double> torque = j["M"];
  vector<double> crankshaftSpeed = j["V"];
  double overheatingTemperature = j["T_high"];
  double H_m = j["H_m"];
  double H_v = j["H_v"];
  double C = j["C"];

  double T_out;

  cout << "Введите температуру окружающей среды: " << endl;
  cin >> T_out;

  Engine* engine = new InternalCombustionEngine(momentInertia, torque, crankshaftSpeed, overheatingTemperature, H_m, H_v, C, T_out);

  double modelTime = 1.0; // 'ускоренние' времени при симуляции, 1 реальная секунда равна 3600 секунд симуляции

  TestEngine* test1 = new TestEngineTemperature(modelTime);
  map<string, double> result1 = test1->run(engine);
  cout << "Первый тест: time = " << result1["time"] << endl;

  engine->reset();

  TestEngine* test2 = new TestEnginePower(modelTime);
  map<string, double> result2 = test2->run(engine);
  cout << "Второй тест: max_power = " << result2["power"] << ", crankshaft_speed = " << result2["crankshaftSpeed"] << endl;

  delete engine;
  delete test1;
  delete test2;

  return 0;
}
