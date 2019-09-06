#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <string>


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
  bool writeFile = false;

  // Parsing the arguments
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("triangulations,t", po::value<int>(&m)->default_value(6), "The number of triangulations")
    ("range,r", po::value<int>(&n)->default_value(10), "The range of numbers")
    ("writefile,w", "Writes to file n.txt, where n is the number of triangulations");

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
      if(vm.count("writefile"))
        {
          writeFile = true;
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

  std::cout<<"Number of triangulations: "<<m<<"\n";

  // This was the old algorithm.
  // auto ans = th::genPoints(m, n);

  if(m % 2 != 0)
    {
      std::cout<<"The number of triangulations must be even"<<std::endl;
      return 0;
    }


  auto ans = th::genSpace(m/2);

  std::cout<<"After transformation, there are "<<ans.size()<<" elements \n";
  for(auto& v: ans)
    {
      std::cout<<v;
    }

  auto outs = th::removeDuplicates(ans);
  std::cout<<"\nAfter removing duplicates, there are "<<outs.size()<<" elements \n";
  for(const auto& v: outs)
    {
      std::cout<<v;
    }

  if(writeFile)
    {
      // I just need to write the complex numbers
      std::string fName(std::to_string(m) + ".txt");
      th::writeFile(outs, fName);
    }

  // temporary code for generating the latex version of P(n; 3, 3, 3, 3)
  if(false)
    {
      std::ofstream fout("latextable.tex");
      fout<<"\\begin{tabular}{c c}\n";
      for(auto i = 2; i <= 200; i += 2)
        {
          auto ans = th::genSpace(i/2);
          auto outs = th::removeDuplicates(ans);


          fout<<i<<" & ";
          for(const auto& v: outs)
            {
              fout<<"\\begin{bmatrix} "<<v(0, 0)<<" & "<<v(0, 1)<<" \\\\"<<v(1, 0)<<" & "<<v(1, 1)<<"\n\\end{bmatrix}\n";
            }

          // end for the table
          fout<<"\\\\";
        }
      fout<<"\\end{tabular}\n";
    }
  return 0;
}

// [a b]
// [c d]
// ad - bc = M
