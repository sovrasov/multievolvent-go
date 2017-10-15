#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <memory>

#include <gkls_function.hpp>
#include <grishagin_function.hpp>
#include <cmdline.h>

#include "multievolventSolver.hpp"

void saveStatistics(const std::vector<std::vector<int>>& stat, const std::string fileName);

int main(int argc, char** argv)
{
  cmdline::parser parser;
  parser.add<int>("evolventTightness", 'm', "", false, 12,
    cmdline::range(9, 16));
  parser.add<std::string>("evolventType", 't', "Type of the used evolvent",
    false, "rotated", cmdline::oneof<std::string>("rotated", "shifted"));
  parser.add<int>("evolventsNum", 'l', "number of active evolvents (actually depends"
        "on evolvent type, tightness and dimenstion)", false, 1, cmdline::range(1, 20));
  parser.add<double>("reliability", 'r', "reliability parameter for the method",
    false, 3, cmdline::range(1., 1000.));
  parser.add<double>("accuracy", 'e', "accuracy of the method", false, 0.01);
  parser.add<double>("reserves", 'E', "eps-reserves for all constraints", false, 0);
  parser.add<int>("itersLimit", 'i', "limit of iterations for the method", false, 2000);
  parser.add<int>("dim", 'd', "test problem dimension (will be set if supported)", false, 2);
  parser.add<int>("localMix", 'q', "local mix parameter", false, 0, cmdline::range(-20, 20));
  parser.add<std::string>("problemsClass", 'c', "Name of the used problems class", false,
    "gklsS", cmdline::oneof<std::string>("gklsS", "gklsH", "grish"));
  parser.add("accuracyStop", 'a', "Use native stop criterion instead of checking known optimum");
  parser.parse_check(argc, argv);

  MultiEvloventType evolventType;
  if(parser.get<std::string>("evolventType") == "rotated")
  evolventType = MultiEvloventType::Rotated;
  else if(parser.get<std::string>("evolventType") == "shifted")
  evolventType = MultiEvloventType::Shifted;

  auto parameters = SolverParameters(parser.get<double>("accuracy"),
  parser.get<double>("reserves"),
  parser.get<double>("reliability"),
  parser.get<int>("evolventsNum"),
  evolventType,
  parser.get<int>("itersLimit"),
  parser.get<int>("localMix"));
  parameters.evolventTightness = parser.get<int>("evolventTightness");
  parameters.stopType = parser.exist("accuracyStop") ? SolverStopCriterion::Accuracy : SolverStopCriterion::OptimumVicinity;

  std::string problemClass = parser.get<std::string>("problemsClass");

  auto start = std::chrono::system_clock::now();
  std::vector<std::vector<int>> allStatistics;

#pragma omp parallel for num_threads(4), schedule(dynamic)
  for (int i = 0; i < 100; i++)
  {
    std::shared_ptr<IGOProblem<double>> problem;
    MultievolventSolver solver;
    solver.SetParameters(parameters);
    if (problemClass == "gklsS" || problemClass == "gklsH")
    {
      auto *func = new gkls::GKLSFunction();
      if (problemClass == "gklsS")
        func->SetFunctionClass(gkls::Simple, parser.get<int>("dim"));
      else
        func->SetFunctionClass(gkls::Hard, parser.get<int>("dim"));

      func->SetType(gkls::TD);
      func->SetFunctionNumber(i + 1);
      problem = std::shared_ptr<IGOProblem<double>>(func);
    }
    else if (problemClass == "grish")
    {
      auto *func = new vagrish::GrishaginFunction();
      func->SetFunctionNumber(i + 1);
      problem = std::shared_ptr<IGOProblem<double>>(func);
    }

    solver.SetProblem(problem);
    Trial optimalPoint = solver.Solve();
#pragma omp critical
    {
      allStatistics.push_back(solver.GetCalculationsStatistics());

      double optPoint[solverMaxDim];
      problem->GetOptimumPoint(optPoint);
      bool isSolved = !solver_utils::checkVectorsDiff(
        optPoint, optimalPoint.y, problem->GetDimension(), parameters.eps);
      std::cout << "Problem # " << i + 1;
      if (isSolved)
      {
        std::cout << " solved.";
        allStatistics.back().push_back(1);
      }
      else
      {
        std::cout << " not solved.";
        allStatistics.back().push_back(0);
      }
      std::cout << " Iterations performed: " << allStatistics.back()[0] << "\n";
    }
  }
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Time elapsed: " << elapsed_seconds.count() << "s\n";

  saveStatistics(allStatistics, "stat.csv");

  return 0;
}

void saveStatistics(const std::vector<std::vector<int>>& stat, const std::string fileName)
{
  size_t numFuncs = stat.back().size() - 1;
  std::vector<double> avgCalcs(numFuncs, 0.);
  int solvedCounter = 0;

  for(const auto& elem : stat)
  {
    for(size_t j = 0; j < numFuncs; j++)
      avgCalcs[j] += elem[j];
    solvedCounter += elem.back();
  }
  for(size_t j = 0; j < numFuncs; j++)
  {
    avgCalcs[j] /= stat.size();
    std::cout << "Average calculations of function #: " << j << " = " << avgCalcs[j] << "\n";
  }
  std::cout << "Problems solved: " << solvedCounter << "\n";
}
