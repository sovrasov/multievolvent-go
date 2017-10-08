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
  unsigned evolventTightness = 12;
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

  std::vector<Trial> mSearchData;
  std::vector<double> mHEstimations;
  std::vector<double> mZEstimations;

  std::vector<int> mTrialsNumber;
  unsigned mIterationsCounter;
  int mMaxV;
  const double mLocalOffset;
  double mDimExponent;

  Trial mNextPoint;

  void InitDataStructures();
  void FirstIteration();
public:
  MultievolventSolver();

  void SetParameters(const SolverParameters& params);
  void SetProblem(std::shared_ptr<IGOProblem<double>> problem);

  Trial Solve();
  std::vector<int> GetCalculationsStatistics() const;
};
