#include <assert.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "algorithms.hpp"
#include <boost/program_options.hpp>

namespace mp = boost::multiprecision;
namespace po = boost::program_options;

auto main(int argc, char* argv[]) -> int
{

  int m;
  bool writeFile = false;

  // Parsing the arguments
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("triangles,t", po::value<int>(&m)->default_value(6), "The number of triangles/2")
    ("writefile,w", po::value<bool>(&writeFile)->default_value(false), "Writes to file n.txt inside the out folder, where 2*n is the number of triangles");

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

  std::cout<<"Number of triangles: "<<2*m<<"\n";

  if(m % 2 != 0)
    {
      std::cout<<"The number of triangles must be even"<<std::endl;
      return 0;
    }

  // Apply the main algorithm from the thesis. The next
  auto ans = th::genSpace(m/2);

  // If Monte-carlo style algorithm is needed, comment out the previous line and
  // use the following line instead:

  // auto ans = th::genPoints(m/2, m/2);

  std::cout<<"After transformation, there are "<<ans.size()<<" elements \n";
  for(auto& v: ans)
    {
      std::cout<<v;
    }

  // If monte-carlo algorithm is needed, comment the following line and
  // uncomment the line after that.
  auto outs = th::removeDuplicates(ans);
  // auto& outs = ans;
  std::cout<<"\nAfter removing duplicates, there are "<<outs.size()<<" elements.\n";
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

  return 0;
}
