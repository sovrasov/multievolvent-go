#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <memory>
#include <cassert>
#include <cmath>

#include <cmdline.h>

#include "evolvents.hpp"

void initParser(cmdline::parser& parser);

int main(int argc, char** argv)
{
  cmdline::parser parser;
  initParser(parser);
  parser.parse_check(argc, argv);

  double t_start = 0., t_end = 1.;
  std::vector<double> lb(10, -0.5);
  std::vector<double> ub(10,  0.5);

  int l = parser.get<int>("evolventsNum");
  int dim = parser.get<int>("dim");
  int m = parser.get<int>("evolventTightness");

  std::shared_ptr<Evolvent> evolvent;

  if(parser.get<std::string>("evolventType") == "rotated")
    evolvent = std::shared_ptr<Evolvent>(new RotatedEvolvent(dim, m, l, lb.data(), ub.data()));
  else if(parser.get<std::string>("evolventType") == "shifted")
    evolvent = std::shared_ptr<Evolvent>(new ShiftedEvolvent(dim, m, l, lb.data(), ub.data()));
  else if(parser.get<std::string>("evolventType") == "noninjective")
  {
    assert(parser.get<int>("evolventsNum") == 1);
    evolvent = std::shared_ptr<Evolvent>(new Evolvent(dim, m, lb.data(), ub.data(), MapType::Noninjective));
  }
  else if(parser.get<std::string>("evolventType") == "multilevel")
  {
    assert(parser.get<int>("evolventsNum") == 1);
    assert(parser.get<int>("dim") % 2 == 0);
    evolvent = std::shared_ptr<Evolvent>(new MultiLevelEvolvent(dim, m, lb.data(), ub.data()));
  }
  else if(parser.get<std::string>("evolventType") == "smooth")
  {
    assert(parser.get<int>("evolventsNum") == 1);
    evolvent = std::shared_ptr<Evolvent>(new SmoothEvolvent(dim, m, lb.data(), ub.data()));
    t_end = 1. - pow(2, -m*dim);
  }

  int nPoints = parser.get<int>("pointsNum");
  assert(nPoints > 2);
  double dt = (t_end - t_start) / nPoints;

  auto fileName = parser.get<std::string>("outFile");
  const std::string sep = "_";
  std::string generatedName = parser.get<std::string>("evolventType") + sep +
    "l_" + std::to_string(parser.get<int>("evolventsNum")) + sep +
    "n_" + std::to_string(parser.get<int>("dim")) + sep +
    "m_" + std::to_string(parser.get<int>("evolventTightness"));
  if(fileName.empty())
    fileName = generatedName + ".csv";

  std::ofstream fout;
  fout.open(fileName, std::ios_base::out);
  fout << generatedName << std::endl;

  std::vector<double> y(dim);

  auto start = std::chrono::system_clock::now();
  for(int i = 0; i <= nPoints; i++)
  {
    double t = dt*i + (l - 1);
    evolvent->GetImage(t, y.data());
    for(int j = 0; j < dim - 1; j++)
      fout << y[j] << ", ";
    fout << y.back() << std::endl;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Time elapsed: " << elapsed_seconds.count() << "s\n";
  std::cout << "Generated file name: " << fileName << std::endl;

  return 0;
}

void initParser(cmdline::parser& parser)
{
  parser.add<int>("evolventTightness", 'm', "", false, 12, cmdline::range(3, 20));
  parser.add<int>("pointsNum", 'n', "", false, 500);
  parser.add<std::string>("evolventType", 't', "Type of the used evolvent",
    false, "rotated", cmdline::oneof<std::string>("rotated", "shifted", "noninjective", "multilevel", "smooth"));
  parser.add<int>("evolventsNum", 'l', "number of active evolvents (actually depends"
        "on evolvent type, tightness and dimenstion)", false, 1, cmdline::range(1, 20));
  parser.add<int>("dim", 'd', "test problem dimension (will be set if supported)", false, 2);
  parser.add<std::string>("outFile", 'f', "Name of the output .csv file with points", false, "");
}
