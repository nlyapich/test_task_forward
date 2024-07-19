#include "internal_combustion_engine.hpp"

#include "simulation_timer.hpp"

InternalCombustionEngine::InternalCombustionEngine(double momentInertia, vector<double> torque, vector<double> crankshaftSpeed,
                                                   double overheatingTemperature, double H_m, double H_v, double C, double T_out)
: _momentInertia{momentInertia}, _torque{torque}, _crankshaftSpeed{crankshaftSpeed},
  _overheatingTemperature{overheatingTemperature}, _H_m{H_m}, _H_v{H_v}, _C{C}, _T_out{T_out}
{
  reset();
}

InternalCombustionEngine::~InternalCombustionEngine() {}

void InternalCombustionEngine::updateTorque()
{
  int pos;
  for (pos = 0; pos < _crankshaftSpeed.size(); ++pos)
  {
    if (_curCrankshaftSpeed >= _crankshaftSpeed[pos])
    {
      break;
    }
  }
  double x1 = _crankshaftSpeed[pos - 1];
  double x2 = _crankshaftSpeed[pos];
  double y1 = _torque[pos - 1];
  double y2 = _torque[pos];
  _curTorque = (y1 - x1*((y2-y1)/(x2-x1))) + (y2-y1)/(x2-x1)*_curCrankshaftSpeed;
}

void InternalCombustionEngine::updateEngine()
{
  double acceleration = _curTorque / _momentInertia;
  _curCrankshaftSpeed = _curCrankshaftSpeed + acceleration;
  updateTorque();
  double V_h = _curTorque*_H_m + _curCrankshaftSpeed*_curCrankshaftSpeed*_H_v;
  double V_c = _C*(_T_out - _curTemperature);
  _curTemperature = _curTemperature + V_h - V_c;
}

void InternalCombustionEngine::run(int modelTime)
{
  _isRunning = true;
  _t1 = move(thread([&]()
  {
    SimulationTimer* timer = new SimulationTimer();

    while (_isRunning)
    {
      timer->tick();
      if (timer->deltaTime() >= 1 / 1.0 /* modelTime */)
      {
        timer->reset();
        updateEngine();
      }
    }

    delete timer;
  }));
  _t1.detach();
}

void InternalCombustionEngine::stop()
{
  _isRunning = false;
}

void InternalCombustionEngine::reset()
{
  _curTorque = _torque[0];
  _curCrankshaftSpeed = _crankshaftSpeed[0];
  _curTemperature = _T_out;
  _isRunning = false;
}

double InternalCombustionEngine::getTemperature() const
{
  return _curTemperature;
}

double InternalCombustionEngine::getPower() const
{
  return _curTorque * _curCrankshaftSpeed / 1000.0;
}

double InternalCombustionEngine::getCrankshaftSpeed() const
{
  return _curCrankshaftSpeed;
}

double InternalCombustionEngine::getOverheatingTemperature() const
{
  return _overheatingTemperature;
}

double InternalCombustionEngine::getTorque() const
{
  return _curTorque;
}
