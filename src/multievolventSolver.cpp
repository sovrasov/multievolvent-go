#include "multievolventSolver.hpp"
#include <limits>
#include <cmath>
#include <algorithm>
#include <exception>

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

  mPreimages.resize(mParameters.numEvolvents);

  mMaxV = 0;
  mDimExponent = 1. / mProblem->GetDimension();
  mBestPoint.v = -1;
}

void MultievolventSolver::FirstIteration()
{
  for(unsigned i = 0; i <= mParameters.numEvolvents; i++)
  {
    mSearchData.emplace_back(static_cast<double>(i));
    mSearchData.back().v = -1;
  }

  if(mParameters.evolventType == MultiEvloventType::Rotated)
  {
    mNextPoint.x = 0.5;
  }
  else
  {
    ;//TODO
  }

  MakeTrial(mNextPoint);
  mEvolvent->GetAllPreimages(mNextPoint.y, mPreimages.data());

  for(unsigned i = 0; i < mParameters.numEvolvents; i++)
  {
    Trial newPoint = mNextPoint;
    newPoint.x = mPreimages[i];
    size_t insert_idx = insert_sorted(mSearchData, newPoint);
    CalculateHEstimationsAfterInsert(insert_idx);
  }

  mIterationsCounter = 1;
}

void MultievolventSolver::MakeTrial(Trial& trial)
{
  mEvolvent->GetImage(trial.x, trial.y);

  trial.v = 0;
  while(trial.v < mProblem->GetConstraintsNumber())
  {
    trial.g[trial.v] = mProblem->Calculate(trial.y, trial.v);
    if(trial.g[trial.v] > 0)
      break;
    else
      trial.v++;
  }

  if(trial.v > mMaxV)
  {
    mMaxV = trial.v;
    for(int i = 0; i < mMaxV; i++)
      mZEstimations[i] = -mParameters.rEps;
  }

  if(trial.v == mProblem->GetConstraintsNumber())
    trial.g[trial.v] = mProblem->Calculate(trial.y, trial.v);

  if(trial.v == mMaxV)
    mZEstimations[trial.v] = fmin(mZEstimations[trial.v], trial.g[trial.v]);
}

void MultievolventSolver::CalculateHEstimationsAfterInsert(size_t idx)
{
  Trial& currentPoint = mSearchData[idx];
  int left_idx = idx - 1;
  while(left_idx > 0 && mSearchData[left_idx].v != currentPoint.v)
    left_idx--;
  if(left_idx != (int)idx && mSearchData[left_idx].v == mSearchData[idx].v && left_idx != -1)
    UpdateMu(mSearchData[left_idx], mSearchData[idx]);

  size_t right_idx = idx + 1;
  while(right_idx < mSearchData.size() - 1 && mSearchData[right_idx].v != currentPoint.v)
    right_idx++;
  if(right_idx != (int)idx && mSearchData[right_idx].v == mSearchData[idx].v && left_idx != -1)
    UpdateMu(mSearchData[idx], mSearchData[right_idx]);
}

void MultievolventSolver::UpdateMu(const Trial& left, const Trial& right)
{
  double oldMu = mHEstimations[left.v];
  double newMu = fabs(right.g[right.v] - left.g[left.v]) /
    pow(right.x - left.x, mDimExponent);
  if (newMu > oldMu || (oldMu == 1.0 && newMu > zeroHLevel))
    mHEstimations[left.v] = newMu;
}

void MultievolventSolver::RecalcR()
{
  double maxR = std::numeric_limits<double>::min();
  const size_t numIntervals = mSearchData.size() - 1;

  for(size_t i = 0; i < numIntervals; i++)
  {
    Interval currentInt(mSearchData[i], mSearchData[i + 1]);
    currentInt.delta = pow(currentInt.pr.x - currentInt.pl.x, mDimExponent);
    currentInt.R = CalculateR(currentInt);

    if(currentInt.R > maxR)
    {
      maxR = currentInt.R;
      mBestInterval = currentInt;
    }
  }
}

void MultievolventSolver::CalculateNextPoints()
{
  if(mBestInterval.pr.v == mBestInterval.pl.v)
  {
    const int v = mBestInterval.pr.v;
    double dg = mBestInterval.pr.g[v] - mBestInterval.pl.g[v];
    mNextPoint.x = 0.5 * (mBestInterval.pr.x + mBestInterval.pl.x) -
      0.5*((dg > 0.) ? 1. : -1.) * pow(fabs(dg) / mHEstimations[v], mProblem->GetDimension()) / (2*mParameters.r);
  }
  else
    mNextPoint.x = 0.5 * (mBestInterval.pr.x + mBestInterval.pl.x);

  if (mNextPoint.x >= mBestInterval.pr.x || mNextPoint.x <= mBestInterval.pl.x)
    throw std::runtime_error("Point is outside of interval\n");

  MakeTrial(mNextPoint);
}

void MultievolventSolver::InsertNextPoints()
{
  mEvolvent->GetAllPreimages(mNextPoint.y, mPreimages.data());
  for(unsigned i = 0; i < mParameters.numEvolvents; i++)
  {
    Trial newPoint = mNextPoint;
    newPoint.x = mPreimages[i];
    size_t insert_idx = insert_sorted(mSearchData, newPoint);
    CalculateHEstimationsAfterInsert(insert_idx);
  }
}

bool MultievolventSolver::CheckStopCondition() const
{
  return mBestInterval.delta < mParameters.eps;
}

void MultievolventSolver::EstimateOptimum()
{
  if(mNextPoint.v > mBestPoint.v ||
      (mNextPoint.v == mBestPoint.v && mNextPoint.g[mNextPoint.v] < mBestPoint.g[mBestPoint.v]))
    mBestPoint = mNextPoint;
}

Trial MultievolventSolver::Solve()
{
  bool needStop = false;

  InitDataStructures();
  FirstIteration();
  RecalcR();

  do {
    CalculateNextPoints();
    EstimateOptimum();
    InsertNextPoints();
    RecalcR();
    needStop = CheckStopCondition();
    mIterationsCounter++;
  } while(mIterationsCounter < mParameters.iterationsLimit && !needStop);

  return mBestPoint;
}

std::vector<int> MultievolventSolver::GetCalculationsStatistics() const
{
  return std::vector<int>();
}

double MultievolventSolver::CalculateR(const Interval& i) const
{
  if(i.pl.v == i.pr.v)
  {
    const int v = i.pr.v;
    return i.delta + pow((i.pr.g[v] - i.pl.g[v]) / (mParameters.r * mHEstimations[v]), 2) / i.delta -
      2.*(i.pr.g[v] + i.pl.g[v] - 2*mZEstimations[v]);
  }
  else if(i.pl.v < i.pr.v)
    return 2*i.delta - 4*(i.pr.g[i.pr.v] - mZEstimations[i.pr.v]) / (mParameters.r * mHEstimations[i.pr.v]);
  else
    return 2*i.delta - 4*(i.pl.g[i.pl.v] - mZEstimations[i.pl.v]) / (mParameters.r * mHEstimations[i.pl.v]);
}
