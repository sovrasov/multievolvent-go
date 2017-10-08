#include "multievolventSolver.hpp"

MultievolventSolver::MultievolventSolver() {}

void MultievolventSolver::SetParameters(const SolverParameters& params)
{
  mParameters = params;
}

void MultievolventSolver::SetProblem(std::shared_ptr<IGOProblem<double>> problem)
{
  mProblem = problem;
}

Trial MultievolventSolver::Solve()
{
  return Trial();
}

std::vector<int> MultievolventSolver::GetCalculationsStatistics() const
{
  return std::vector<int>();
}
