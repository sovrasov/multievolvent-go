#pragma once

#include "evolvents.hpp"

class SmoothEvolvent
{
public:
  SmoothEvolvent( int, int, double );

  int n,m;
  double h;
  mutable int smoothPointCount;
  bool continuously;

  void operator ()(double, std::vector<double>&,std::vector<double>&) const;
  void minmax( double &a, double & b ) const;
};
