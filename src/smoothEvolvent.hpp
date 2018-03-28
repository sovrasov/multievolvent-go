#pragma once

#include "evolvents.hpp"

class SmoothEvolvent : public Evolvent
{
protected:
  int n,m;
  double h;
  mutable int smoothPointCount;
  bool continuously;

  void operator ()(double, std::vector<double>&,std::vector<double>&) const;
  void minmax( double &a, double & b ) const;

public:
  SmoothEvolvent(int dimension, int tightness, const double* lb, const double* ub, double smoothness = 0.25);

  virtual void GetImage(double x, double y[]);
  virtual int GetAllPreimages(const double* p, double xp[]);
};
