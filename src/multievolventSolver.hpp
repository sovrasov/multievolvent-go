#pragma once
#include <problem_interface.hpp>
#include <vector>
#include "dataTypes.hpp"

struct SolverParameters
{
  double eps;
  double rEps;
  double r;
  unsigned iterationsLimit;
  unsigned evloventTightness = 12;
  unsigned numEvolvents;

  SolverParameters() {}
  SolverParameters(double _eps, double _rEps, double _r, unsigned _itersLimit,
          unsigned _numEvolvents) :
        eps(_eps), rEps(_rEps), r(_r), iterationsLimit(_itersLimit), numEvolvents(_numEvolvents)
  {}
};

class MultievolventSolver
{
protected:
public:
  MultievolventSolver();

  void SetParameters(const SolverParameters& params);
  void SetProblem(const IGOProblem<double> *);

  Trial Solve();

  std::vector<int> GetStatistics() const;
};
