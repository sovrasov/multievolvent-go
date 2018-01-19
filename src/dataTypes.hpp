#pragma once
#include <stdexcept>

#define GO_ASSERT(x, y) if(!(x)) throw std::runtime_error(y + std::string("\n"));

const unsigned solverMaxDim = 5;
const unsigned solverMaxConstraints = 5;

struct Trial
{
  double x;
  double y[solverMaxDim];
  double g[solverMaxConstraints + 1];
  int v;
  Trial() {}
  Trial(double _x) : x(_x){}
};

inline bool operator<(const Trial& t1, const Trial& t2)
{
  return t1.x < t2.x;
}

struct Interval
{
  Trial pl;
  Trial pr;
  double delta;
  double R;
  Interval() {}
  Interval(const Trial& _xl, const Trial& _xr) : pl(_xl), pr(_xr) {}
};

inline bool operator<(const Interval& i1, const Interval& i2)
{
  return i1.R < i2.R;
}
