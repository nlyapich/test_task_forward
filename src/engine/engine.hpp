#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine
{
public:
  virtual ~Engine() {};

  virtual void run(int modelTime) = 0;
  virtual void stop() = 0;

  virtual void reset() = 0;

  virtual double getTemperature() const = 0;
  virtual double getPower() const = 0;
  virtual double getCrankshaftSpeed() const = 0;
  virtual double getOverheatingTemperature() const = 0;
  virtual double getTorque() const = 0;
};

#endif // ENGINE_HPP
