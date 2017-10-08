#pragma once
#include <problem_interface.hpp>
#include <vector>
#include <memory>

#include "dataTypes.hpp"
#include "evolvents.hpp"

struct SolverParameters
{
  double eps;
  double rEps;
  double r;
  unsigned numEvolvents;
  unsigned evloventTightness = 12;
  MultiEvloventType evolventType;
  unsigned iterationsLimit;
  int localMix;

  SolverParameters() {}
  SolverParameters(double _eps, double _rEps, double _r, unsigned _numEvolvents,
    MultiEvloventType _evolventType, unsigned _itersLimit, int _localMix) :
        eps(_eps), rEps(_rEps), r(_r),  numEvolvents(_numEvolvents), evolventType(_evolventType),
        iterationsLimit(_itersLimit), localMix(_localMix)
  {}
};

class MultievolventSolver
{
protected:
  SolverParameters mParameters;
  std::shared_ptr<IGOProblem<double>> mProblem;
  std::shared_ptr<Evolvent> mEvolvent;

  void InitDataStructures();
public:
  MultievolventSolver();

  void SetParameters(const SolverParameters& params);
  void SetProblem(std::shared_ptr<IGOProblem<double>> problem);

  Trial Solve();
  std::vector<int> GetCalculationsStatistics() const;
};
