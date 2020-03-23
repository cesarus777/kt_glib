#pragma once

#include <iostream>
#include <string>

#ifdef W_ABORT
#define ABORT_ERROR_HANDLER std::cerr << "\n\x1b[1;31mFatal ERROR\n\t"  \
                                      << "\x1b[0merror at function "    \
                                      << "\x1b[1;35m" << __func__       \
                                      << "\x1b[0m, in line "            \
                                      << "\x1b[1m"    << __LINE__       \
                                      << "\x1b[0m, from file '"         \
                                      << "\x1b[1m"    << __FILE__       \
                                      << "\x1b[0m'"   <<  std::endl;    \
                            abort();
#endif

void good_check();

void bad_check(std::string expr);

