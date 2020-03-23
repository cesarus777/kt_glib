#pragma once

#include <iostream>

#include <macro/error_handler.hpp>

#define START_TEST_CASE(test_name) \
  std::cout << "Testing : " << test_name << std::endl;

#define END_TEST_CASE \
  std::cout << "Tested successful" << std::endl;

#define CHECK(expr) \
  expr ? good_check() : bad_check(#expr);

#define START_TEST_MODULE(module_name) \
  std::cout << "Testing module : " << module_name << std::endl;

#define END_TEST_MODULE \
  std::cout << "Tested successful" << std::endl;

#define START_TEST_SUBMODULE(submodule_name) \
  std::cout << "\tTesting submodule : " << submodule_name << std::endl;

#define END_TEST_SUBMODULE \
  std::cout << "\tTested successful" << std::endl;

