#include "multievolventSolver.hpp"
#include <limits>
#include <cmath>
#include <algorithm>

namespace
{
  class ShiftedEvolventGOProblem : public IGOProblem<double>
  {
  protected:
    std::shared_ptr<IGOProblem<double>> mOriginalProblem;

    double CalculateZeroConstraint(const double* y) const
    {
      double value = std::numeric_limits<double>::min();

      //for (int i = 0; i < mOriginalProblem->GetDimension(); i++)
      //  value = fmax(value, (fabs(y[i] - spaceShift[i])
      //    - (rightBnd[i] - leftBnd[i])*0.5) / rho);

      return value;
    }
  public:
    ShiftedEvolventGOProblem(std::shared_ptr<IGOProblem<double>> problem) :
      mOriginalProblem(problem)
    {}
    double Calculate(const double* y, int fNumber) const
    {
      if(fNumber == 0)
        return CalculateZeroConstraint(y);
      else
        return mOriginalProblem->Calculate(y, fNumber - 1);
    }
    int GetConstraintsNumber() const
    {
      return mOriginalProblem->GetConstraintsNumber() + 1;
    }

    int GetDimension() const
    { return mOriginalProblem->GetDimension(); }
    void GetBounds(double* left, double* right) const
    {
      mOriginalProblem->GetBounds(left, right);
    }
    int GetOptimumPoint(double* y) const
    {
      mOriginalProblem->GetOptimumPoint(y);
    }
    double GetOptimumValue() const
    {
      return mOriginalProblem->GetOptimumValue();
    }
  };

  const double zeroHLevel = 1e-12;

  template<typename T>
  size_t insert_sorted(std::vector<T> & vec, T const& item)
  {
    return std::distance(vec.begin(), vec.insert
    (std::upper_bound(vec.begin(), vec.end(), item), item));
  }
}

MultievolventSolver::MultievolventSolver() : mLocalOffset(pow(1.5, -15)) {}

void MultievolventSolver::SetParameters(const SolverParameters& params)
{
  mParameters = params;
}

void MultievolventSolver::SetProblem(std::shared_ptr<IGOProblem<double>> problem)
{
  mProblem = problem;
}

void MultievolventSolver::InitDataStructures()
{
  double leftBound[solverMaxDim], rightBound[solverMaxDim];
  mProblem->GetBounds(leftBound, rightBound);

  if(mParameters.evolventType == MultiEvloventType::Rotated)
    mEvolvent = std::shared_ptr<Evolvent>(new RotatedEvolvent(mProblem->GetDimension(), mParameters.evolventTightness,
      mParameters.numEvolvents, leftBound, rightBound));
  else
  {
    mEvolvent = std::shared_ptr<Evolvent>(new ShiftedEvolvent(mProblem->GetDimension(), mParameters.evolventTightness,
    mParameters.numEvolvents, leftBound, rightBound));
    mProblem = std::shared_ptr<IGOProblem<double>>(new ShiftedEvolventGOProblem(mProblem));
  }

  mSearchData.clear();
  mSearchData.reserve(mParameters.iterationsLimit*mParameters.numEvolvents);

  mHEstimations.resize(mProblem->GetConstraintsNumber() + 1);
  std::fill(mHEstimations.begin(), mHEstimations.end(), 1.0);

  mZEstimations.resize(mProblem->GetConstraintsNumber() + 1);
  std::fill(mZEstimations.begin(), mZEstimations.end(), std::numeric_limits<double>::max());

  mMaxV = 0;
  mDimExponent = 1. / mProblem->GetDimension();
}

void MultievolventSolver::FirstIteration()
{
  for(unsigned i = 0; i <= mParameters.numEvolvents; i++)
  {
    mSearchData.emplace_back(static_cast<double>(0));
    mSearchData.back().v = 0;
    mSearchData.emplace_back(static_cast<double>(i));
    mSearchData.back().v = 0;
  }

  mIterationsCounter = 1;
}

Trial MultievolventSolver::Solve()
{
  InitDataStructures();
  FirstIteration();
  return Trial();
}

std::vector<int> MultievolventSolver::GetCalculationsStatistics() const
{
  return std::vector<int>();
}
