#ifndef INTERNAL_COMBUSTION_ENGINE_HPP
#define INTERNAL_COMBUSTION_ENGINE_HPP

#include <vector>
#include <thread>

#include "engine.hpp"

using namespace std;

class InternalCombustionEngine : public Engine
{
public:
  InternalCombustionEngine(double momentInertia, vector<double> torque, vector<double> crankshaftSpeed,
                           double overheatingTemperature, double H_m, double H_v, double C, double T_out);
  virtual ~InternalCombustionEngine();

  void run(int modelTime) override;
  void stop() override;

  void reset() override;

  double getTemperature() const override;
  double getPower() const override;
  double getCrankshaftSpeed() const override;
  double getOverheatingTemperature() const override;
  double getTorque() const override;

private:
  double _momentInertia;
  vector<double> _torque;
  vector<double> _crankshaftSpeed;
  double _overheatingTemperature;
  double _H_m;
  double _H_v;
  double _C;
  double _T_out;

  double _curTorque;
  double _curCrankshaftSpeed;
  double _curTemperature;

  bool _isRunning;

  thread _t1;

  void updateTorque();
  void updateEngine();
};

#endif // INTERNAL_COMBUSTION_ENGINE_HPP
