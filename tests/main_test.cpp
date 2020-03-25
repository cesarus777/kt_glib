#include <cfenv>
#include <iomanip>

#include <macro/test.hpp>

void test_sources();

int main()
{
#ifdef DEBUG
  std::cout << std::setprecision(15);
#endif
  std::fesetround(FE_TONEAREST);
  test_sources();
}

