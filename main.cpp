#include <iostream>
#include <vector>
#include <set>
#include <assert.h>


#include <boost/program_options.hpp>


#include "algorithms.hpp"

// template <typename Z>
// using matrix = boost::numeric::ublas::matrix<Z>;
namespace mp = boost::multiprecision;
namespace po = boost::program_options;

// 6th root of unity

auto main(int argc, char* argv[]) -> int
{

  int m, n;

  // Parsing the arguments
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("triangulations,t", po::value<int>(&m)->default_value(6), "The number of triangulations")
    ("range,r", po::value<int>(&n)->default_value(10), "The range of numbers");

  try
    {
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if(vm.count("help"))
    {
      std::cout<<desc;
      return 0;
    }
    }
  catch(std::exception& e)
    {
      std::cerr<<"error: "<<e.what()<<"\n";
      std::cout<<desc<<"\n";
      return 1;
    }
  catch(...)
    {
      std::cerr<<"error of unknown type\n";
      std::cout<<desc<<"\n";
      return 1;
    }

  std::cout<<"Number of triangulations: "<<m<<" Range: "<<n<<"\n\n";

  auto ans = th::genPoints(m, n);

  for(auto& v: ans)
    {
      std::cout<<v;
    }
  return 0;
}

// [a b]
// [c d]
// ad - bc = M
