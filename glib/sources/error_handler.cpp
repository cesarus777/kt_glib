#include <macro/error_handler.hpp>

#include <iostream>
#include <string>

void good_check()
{
  std::cout << "Good check" << std::endl;
}

void bad_check(std::string expr)
{
  std::cerr << "\x1b[1:31mBad test check\x1b[0m : \n\t" << expr << std::endl;
  std::cerr << "End  testing" << std::endl;
  exit(EXIT_FAILURE);
}

