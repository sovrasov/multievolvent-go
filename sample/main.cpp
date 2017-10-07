#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <memory>

#include <gkls_function.hpp>
#include <grishagin_function.hpp>
#include <cmdline.h>

#include "multievolventSolver.hpp"

int main(int argc, char** argv)
{
  cmdline::parser parser;
  parser.add<int>("evolventTightness", 'm', "", false, 12,
        cmdline::range(9, 16));
  parser.add<int>("evolventsNum", 'l', "number of active evolvents (actually depends"
        "on evolvent type, tightness and dimenstion)", false, 1, cmdline::oneof(1, 20));
  parser.add<std::string>("evolventType", 't', "Type of the used evolvent",
          false, "rotated", cmdline::oneof<std::string>("rotated", "shifted"));
  parser.add<double>("reliability", 'r', "reliability parameter for the method",
    false, 4.5, cmdline::range(1., 1000.));
  parser.add<double>("accuracy", 'e', "accuracy of the method", false, 0.01);
  parser.add<double>("reserves", 'E', "eps-reserves for all constraints", false, 0);
  parser.add<int>("itersLimit", 'l', "limit of iterations for the method", false, 2000);
  parser.add<int>("dim", 'd', "test problem dimension (will be set if supported)", false, 2);
  parser.add<int>("localMix", 'm', "local mix parameter", false, 0);
  parser.add<std::string>("problemsClass", 'c', "Name of the used problems class", false,
    "gklsS", cmdline::oneof<std::string>("gklsS", "gklsH", "grish"));
  parser.parse_check(argc, argv);

  EvolventType evolventType;
  if(parser.get<std::string>("evolventType") == "rotated")
  evolventType = EvolventType::Rotated;
  else if(parser.get<std::string>("evolventType") == "shifted")
  evolventType = EvolventType::Shifted;

  auto parameters = SolverParameters(parser.get<double>("accuracy"),
  parser.get<double>("reserves"),
  parser.get<double>("reliability"),
  parser.get<int>("evolventsNum"),
  evolventType,
  parser.get<int>("itersLimit"),
  parser.get<int>("localMix"));
  parameters.evloventTightness = parser.get<int>("evolventTightness");

  std::shared_ptr<IGOProblem<double>> problem;
  std::string problemClass = parser.get<std::string>("problemsClass");
  if(problemClass == "gklsS" || problemClass == "gklsH")
  {
    auto *func = new gkls::GKLSFunction();
    if(problemClass == "gklsS")
      func->SetFunctionClass(gkls::Hard, parser.get<int>("dim"));
    else
      func->SetFunctionClass(gkls::Hard, parser.get<int>("dim"));

    func->SetType(gkls::TD);
    func->SetFunctionNumber(1);
    problem = std::shared_ptr<IGOProblem<double>>(func);
  }
  else if(problemClass == "grish")
  {
    auto *func = new vagrish::GrishaginFunction();
    func->SetFunctionNumber(1);
    problem = std::shared_ptr<IGOProblem<double>>(func);
  }

  MultievolventSolver solver;
  solver.SetParameters(parameters);
  solver.SetProblem(problem);
  Trial optimalPoint = solver.Solve();
  std::vector<int> stats = solver.GetCalculationsStatistics();

  return 0;
}
