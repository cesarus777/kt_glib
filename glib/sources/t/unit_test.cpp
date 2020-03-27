#include <array>
#include <iostream>

#include <base_algorithm.hpp>
#include <macro/error_handler.hpp>
#include <macro/math_macro.hpp>
#include <macro/test.hpp>

void math_macro_cpp();
void base_algorithm_cpp();

void test_sources()
{
  math_macro_cpp();
  base_algorithm_cpp();
}

void math_macro_cpp()
{
  START_TEST_CASE("my_math::tan_sum")

#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of angles in the next order:\n\t"
            << "angle1 angle2 tan(angle1 + angle2)" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<double, double>, n_test> angles;
  std::array<double, n_test> tans;

  for(size_t i = 0; i < n_test; ++i)
  {
    double a1, a2, tan;
    std::cin >> a1 >> a2 >> tan;
    angles[i] = std::move(std::make_pair(a1, a2));
    tans[i] = tan;
  }

#else

  constexpr size_t n_test = 5;

  constexpr std::array<std::pair<double, double>, n_test> angles = {
    std::make_pair( my_math::pi / 4.0, my_math::pi / 4.0  ),
    std::make_pair( my_math::pi / 6.0, my_math::pi / 6.0  ),
    std::make_pair( my_math::pi / 5.0, my_math::pi / 25.0 ),
    std::make_pair( my_math::pi / 2.0, 0.0                ),
    std::make_pair( my_math::pi * 1.5, my_math::pi * 2.5  )
  };

  constexpr std::array<double, n_test> tans = {
    std::tan(my_math::pi / 2.0),
    std::tan(my_math::pi / 3.0),
    std::tan(my_math::pi * 0.24),
    std::tan(my_math::pi / 2.0),
    0.0,
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    double check_value = my_math::tan_sum(std::tan(angles[i].first), std::tan(angles[i].second));
    check_value = std::atan(check_value);
    double tan = std::atan(tans[i]);

#ifdef DEBUG
    std::cout << check_value << " ?= " << tan << std::endl;
#endif

    CHECK(EQUAL(check_value, tan))
  }

  END_TEST_CASE
}

void base_algorithm_cpp()
{
  {
  START_TEST_CASE("mygeo::distance")

#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of points in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y distance" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> points;
  std::array<double, n_test> dists;

  for(size_t i = 0; i < n_test; ++i)
  {
    double x1, y1, x2, y2, dist;
    std::cin >> x1 >> y1 >> x2 >> y2 >> dist;
    points[i] = std::move(std::make_pair(mygeo::Point(x1, y1), mygeo::Point(x2, y2)));
    dists[i] = dist;
  }

#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> points = {
    std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(1.0, 0.0) ),
    std::make_pair( mygeo::Point(5.0, 8.0), mygeo::Point(5.0, 8.0) ),
    std::make_pair( mygeo::Point(3.0, 7.0), mygeo::Point(7.0, 10.0) ),
    std::make_pair( mygeo::Point(12.3, -345.95), mygeo::Point(-34.0, 1.09) ),
    std::make_pair( mygeo::Point(-34.03456, 0.0), mygeo::Point(1.0, 2340.08765) ),
  };

  constexpr std::array<double, n_test> dists = {
    1.0, 0.0, 5.0, 350.114911993, 2340.349894797,
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    double check_value = mygeo::distance(points[i].first, points[i].second);

#ifdef DEBUG
    std::cout << check_value << " ?= " << dists[i] << std::endl;
#endif

    CHECK(EQUAL(check_value, dists[i]))
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::isPolygon")

#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_INPUT
  n_test = 5;
  std::cout << "Input " << n_test << " sets of points in the next order:\n\t"
            << "n p1.x p1.y p2.x p2.y ... pn.x pn.y verity\n"
            << "..." << "..." << "..."
            << "m p1.x p1.y p2.x p2.y ... pm.x pm.y, verity\n"
            << "where n, ..., m are numbers of vertices of each polygon,"
            << "and p1, ... pn/pm are vertices of each polygon" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::vector<std::vector<mygeo::Point>, n_test> polygons;
  std::array<bool, n_test> bools;

  for(size_t i = 0; i < n_test; ++i)
  {
    size_t n_vert;
    std::cin >> n_vert;
    for(size_t j = 0; j < n_vert; ++j)
    {
      double x, y;
      std::cin >> x >> y;
      polygons[i].push_back(mygeo::Point(x, y));
    }
    bool b;
    std::cin >> b;
    bools[i] = b;
  }

#else

  constexpr size_t n_test = 5;

  std::vector<std::vector<mygeo::Point>> polygons = {
    { mygeo::Point(0.0, 0.0), mygeo::Point(1.0, 1.0), mygeo::Point(2.0, 2.0) },
    { mygeo::Point(0.0, 0.0), mygeo::Point(0.0, 1.0), mygeo::Point(1.0, 0.0) },
    { mygeo::Point(0.0, 0.0), mygeo::Point(0.0, 1.0), mygeo::Point(1.0, 1.0),
      mygeo::Point(1.0, 0.0) },
    { mygeo::Point(0.0, 0.0), mygeo::Point(0.0, 1.0), mygeo::Point(1.0, 0.0),
      mygeo::Point(1.0, 1.0) },
    { mygeo::Point(0.0, 0.0), mygeo::Point(0.0, 1.0), mygeo::Point(1.0, 1.0),
      mygeo::Point(1.5, 0.5), mygeo::Point(1.0, 0.0) },
  };
  constexpr std::array<bool, n_test> bools = {
    false, true, true, false, true,
  };

#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    bool check_value = mygeo::isPolygon(polygons[i]);

#ifdef DEBUG
    std::cout << check_value << " ?= " << bools[i] << std::endl;
#endif

    CHECK(check_value == bools[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::are_intersected")
  
#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of lines in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y p3.x p3.y p4.x p4.y verity, "
            << "where p1 and p2 are start and end of the first line, "
            << "p3 and p4 are start and end of the second line" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines;
  std::array<bool, n_test> bools;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 8> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    mygeo::Point p3(coord[4], coord[5]);
    mygeo::Point p4(coord[6], coord[7]);
    mygeo::Line l1(p1, p2);
    mygeo::Line l2(p3, p4);
    lines[i] = std::move(std::make_pair(l1, l2));
    bool b;
    std::cin >> b;
    bools[i] = b;
  }

#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines = {
    std::make_pair( mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(1.0, 1.0)),
                    mygeo::Line(mygeo::Point(1.0, 0.0), mygeo::Point(0.0, 1.0))),
    std::make_pair( mygeo::Line(mygeo::Point(4907.26, -5204.13), mygeo::Point(-5444.55, 2440.28)),
                    mygeo::Line(mygeo::Point(8374.62, -1984.44), mygeo::Point(3039.23, -3627.46))),
    std::make_pair( mygeo::Line(mygeo::Point(-304.592, -566.716), mygeo::Point(-390.475, -574.829)),
                    mygeo::Line(mygeo::Point(823.290, -611.583), mygeo::Point(266.385, 587.052))),
    std::make_pair( mygeo::Line(mygeo::Point(94.29, 96.4474), mygeo::Point(24.585, 57.8739)),
                    mygeo::Line(mygeo::Point(-2.44925, -83.1508), mygeo::Point(34.8, 81.4))),
    std::make_pair( mygeo::Line(mygeo::Point(2.0, -5.0), mygeo::Point(-9.0, 3.0)),
                    mygeo::Line(mygeo::Point(2.0, 6.0), mygeo::Point(2.0, -1.0))),
  };

  constexpr std::array<bool, n_test> bools = {
    true, false, false, true, false,
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    bool check_value = mygeo::are_intersected(lines[i].first, lines[i].second);

#ifdef DEBUG
    std::cout << check_value << " ?= " << bools[i] << std::endl;
#endif

    CHECK(check_value == bools[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::includes")
  
#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of lines in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y p3.x p3.y p4.x p4.y verity, "
            << "where p1 and p2 are start and end of the first line, "
            << "p3 and p4 are start and end of the second line" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines;
  std::array<bool, n_test> bools;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 8> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    mygeo::Point p3(coord[4], coord[5]);
    mygeo::Point p4(coord[6], coord[7]);
    mygeo::Line l1(p1, p2);
    mygeo::Line l2(p3, p4);
    lines[i] = std::move(std::make_pair(l1, l2));
    bool b;
    std::cin >> b;
    bools[i] = b;
  }

#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines = {
    std::make_pair( mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(2.0, 2.0)),
                    mygeo::Line(mygeo::Point(2.0, 2.0), mygeo::Point(1.0, 1.0))),
    std::make_pair( mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(1.0, 1.0)),
                    mygeo::Line(mygeo::Point(1.0, 1.0), mygeo::Point(2.0, 2.0))),
    std::make_pair( mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(1.0, 1.0)),
                    mygeo::Line(mygeo::Point(0.0, 1.0), mygeo::Point(1.0, 0.0))),
    std::make_pair( mygeo::Line(mygeo::Point(-1.0, -3.0), mygeo::Point(5.0, 3.0)),
                    mygeo::Line(mygeo::Point(2.0, 0.0), mygeo::Point(3.5, 1.5))),
    std::make_pair( mygeo::Line(mygeo::Point(2.0, -5.0), mygeo::Point(-9.0, 3.0)),
                    mygeo::Line(mygeo::Point(2.0, 6.0), mygeo::Point(2.0, -1.0))),
  };

  constexpr std::array<bool, n_test> bools = {
    true, false, false, true, false,
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    bool check_value = includes(lines[i].first, lines[i].second);

#ifdef DEBUG
    std::cout << check_value << " ?= " << bools[i] << std::endl;
#endif

    CHECK(check_value == bools[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::intersect")
  
#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of lines in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y p3.x p3.y p4.x p4.y i.x i.y, "
            << "where p1 and p2 are start and end of the first line, "
            << "p3 and p4 are start and end of the second line, "
            << "i is point of intersection of this lines" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines;
  std::array<mygeo::Point, n_test> points;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 10> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    mygeo::Point p3(coord[4], coord[5]);
    mygeo::Point p4(coord[6], coord[7]);
    mygeo::Point p5(coord[8], coord[9]);
    mygeo::Line l1(p1, p2);
    mygeo::Line l2(p3, p4);
    lines[i] = std::move(std::make_pair(l1, l2));
    points[i] = std::move(p5);
  }

#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines = {
    std::make_pair( mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(1.0, 1.0)),
                    mygeo::Line(mygeo::Point(1.0, 0.0), mygeo::Point(0.0, 1.0))),
    std::make_pair( mygeo::Line(mygeo::Point(4907.26, -5204.13), mygeo::Point(-5444.55, 2440.28)),
                    mygeo::Line(mygeo::Point(8374.62, -1984.44), mygeo::Point(3039.23, -3627.46))),
    std::make_pair( mygeo::Line(mygeo::Point(-304.592, -566.716), mygeo::Point(-390.475, -574.829)),
                    mygeo::Line(mygeo::Point(823.290, -611.583), mygeo::Point(266.385, 587.052))),
    std::make_pair( mygeo::Line(mygeo::Point(94.29, 96.4474), mygeo::Point(24.585, 57.8739)),
                    mygeo::Line(mygeo::Point(-2.44925, -83.1508), mygeo::Point(34.8, 81.4))),
    std::make_pair( mygeo::Line(mygeo::Point(2.0, -5.0), mygeo::Point(-9.0, 3.0)),
                    mygeo::Line(mygeo::Point(2.0, 6.0), mygeo::Point(2.0, -1.0))),
  };

  std::array<mygeo::Point, n_test> points = {
    mygeo::Point(0.5, 0.5),
    mygeo::Point(2850.77368, -3685.49465),
    mygeo::Point(755.8988, -466.53596),
    mygeo::Point(30.17462, 60.96709),
    mygeo::Point(2.0, -1.0),
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    mygeo::Point check_value = mygeo::intersect(lines[i].first, lines[i].second);

#ifdef DEBUG
    std::cout << "{ " << check_value.x << ", " << check_value.y
        << " } ?= { " << points[i].x << ", " << points[i].y << " }" << std::endl;
#endif

    CHECK(check_value == points[i])
  }

  END_TEST_CASE
  }





  {
  START_TEST_CASE("mygeo::belongs_to")
#ifdef CIN_TEST

  size_t n_test

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of points and lines in the next order:\n\t"
            << "p.x p.y p1.x p1.y p2.x p2.y verity, "
            << "where p1 and p2 are start and end of the line" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Point, mygeo::Line>, n_test> pairs;
  std::array<bool, n_test> bools;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 6> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p(coord[0], coord[1]);
    mygeo::Point p1(coord[2], coord[3]);
    mygeo::Point p2(coord[4], coord[5]);
    mygeo::Line l(p1, p2);
    pairs[i] = std::move(std::make_pair(p, l));
    bool b;
    std::cin >> b;
    bools[i] = b;
  }

#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Point, mygeo::Line>, n_test> pairs = {
    std::make_pair( mygeo::Point(1.0, 1.0), mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(2.0, 2.0))),
    std::make_pair( mygeo::Point(1.0, 1.0), mygeo::Line(mygeo::Point(6.4, 4.0), mygeo::Point(-7.7, -2.7))),
    std::make_pair( mygeo::Point(1.03, -42.0872), mygeo::Line(mygeo::Point(36.09, -84.52), mygeo::Point(-44.37, 12.86))),
    std::make_pair( mygeo::Point(-777.777, -267.763), mygeo::Line(mygeo::Point(-991.825, -227.878), mygeo::Point(-71.528, -399.362))),
    std::make_pair( mygeo::Point(0.0, 7373.98), mygeo::Line(mygeo::Point(392.0, 6970.0), mygeo::Point(8018.0, -889.0))),
  };

  constexpr std::array<bool, n_test> bools = {
    true, false, true, true, false,
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    bool check_value = mygeo::belongs_to(pairs[i].first, pairs[i].second);

#ifdef DEBUG
    std::cout << check_value << " ?= " << bools[i] << std::endl;
#endif

    CHECK(check_value == bools[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::turn_left")

#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of lines in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y p3.x p3.y p4.x p4.y verity, "
            << "where p1 and p2 are start and end of the first line, "
            << "p3 and p4 are start and end of the second line" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines;
  std::array<bool, n_test> bools;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 8> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    mygeo::Point p3(coord[4], coord[5]);
    mygeo::Point p4(coord[6], coord[7]);
    mygeo::Line l1(p1, p2);
    mygeo::Line l2(p3, p4);
    lines[i] = std::move(std::make_pair(l1, l2));
    bool b;
    std::cin >> b;
    bools[i] = b;
  }

#else

  constexpr size_t n_test = 5;

  mygeo::Line l(mygeo::Point(40.0, -80.0), mygeo::Point(-45.0, 13.0));
  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines = {
    std::make_pair( mygeo::Line(mygeo::Point(-45.0, 13.0), mygeo::Point(30.0, 50.0)), l),
    std::make_pair( mygeo::Line(mygeo::Point(-45.0, 13.0), mygeo::Point(-50.0, 335.0)), l),
    std::make_pair( mygeo::Line(mygeo::Point(-45.0, 13.0), mygeo::Point(-150.0, 15.0)), l),
    std::make_pair( mygeo::Line(mygeo::Point(-45.0, 13.0), mygeo::Point(-5.0, -75.0)), l),
    std::make_pair( mygeo::Line(mygeo::Point(-45.0, 13.0), mygeo::Point(150.0, -15.0)), l),
  };

  constexpr std::array<bool, n_test> bools = {
    false, false, true, true, false
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    bool check_value = mygeo::turn_left(lines[i].second, lines[i].first);

#ifdef DEBUG
    std::cout << check_value << " ?= " << bools[i] << std::endl;
#endif

    CHECK(check_value == bools[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::is_continuation")

#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_TEST
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of lines in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y p3.x p3.y p4.x p4.y verity, "
            << "where p1 and p2 are start and end of the first line, "
            << "p3 and p4 are start and end of the second line" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines;
  std::array<bool, n_test> bools;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 8> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    mygeo::Point p3(coord[4], coord[5]);
    mygeo::Point p4(coord[6], coord[7]);
    mygeo::Line l1(p1, p2);
    mygeo::Line l2(p3, p4);
    lines[i] = std::move(std::make_pair(l1, l2));
    bool b;
    std::cin >> b;
    bools[i] = b;
  }

#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Line, mygeo::Line>, n_test> lines = {
    std::make_pair( mygeo::Line(mygeo::Point(37.1854, -13.9851), mygeo::Point(-30.7378, 28.4512)),
                    mygeo::Line(mygeo::Point(61.4175, -31.0682), mygeo::Point(1.54173, 47.3601))),
    std::make_pair( mygeo::Line(mygeo::Point(-39.8781, 97.1982), mygeo::Point(49.4649, -69.2930)),
                    mygeo::Line(mygeo::Point(49.4649, -69.2930), mygeo::Point(61.4175, -31.0682))),
    std::make_pair( mygeo::Line(mygeo::Point(-60.4843, 9.07052), mygeo::Point(72.7178, 94.5366)),
                    mygeo::Line(mygeo::Point(72.7178, 94.5366), mygeo::Point(-1.87722, -47.8032))),
    std::make_pair( mygeo::Line(mygeo::Point(70.1076, 43.9295), mygeo::Point(-56.4386, -73.8891)),
                    mygeo::Line(mygeo::Point(-53.0859, 29.1946), mygeo::Point(26.0331, -13.3472))),
    std::make_pair( mygeo::Line(mygeo::Point(34.5470, -75.1774), mygeo::Point(75.8481, 29.8303)),
                    mygeo::Line(mygeo::Point(-75.1628, 90.3827), mygeo::Point(75.8481, 29.8303))),
  };

  constexpr std::array<bool, n_test> bools = {
    false, true, true, false, true,
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    bool check_value = mygeo::is_continuation(lines[i].first, lines[i].second);

#ifdef DEBUG
    std::cout << check_value << " ?= " << bools[i] << std::endl;
#endif

    CHECK(check_value == bools[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::line_mid \\ for Points")
#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_INPUT
  n_test = 5;
  std::cout << "Input " << n_test << " triplets of points in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y p3.x p3.y, "
            << "where p1 and p2 are end points of line and p3 is its middle" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> points;
  std::array<mygeo::Point, n_test> mids;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 6> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    points[i] = std::move(std::make_pair(p1, p2));
    mygeo::Point p3(coord[4], coord[5]);
    mids[i] = std::move(p3);
  }
 
#else

  constexpr size_t n_test = 5;

  std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> points = {
    std::make_pair(mygeo::Point(0.0, 0.0), mygeo::Point(2.0, 2.0)),
    std::make_pair(mygeo::Point(73.5822, -67.1408), mygeo::Point(-25.7569, 62.2525)),
    std::make_pair(mygeo::Point(-13.4589, -55.7949), mygeo::Point(-90.4444, 42.1780)),
    std::make_pair(mygeo::Point(-86.0303, -71.6530), mygeo::Point(-83.8443, -7.50341)),
    std::make_pair(mygeo::Point(52.9091, 38.1110), mygeo::Point(-7.84307, -20.9061)),
  };

  std::array<mygeo::Point, n_test> mids = {
    mygeo::Point(1.0, 1.0),
    mygeo::Point(23.91265, -2.44415),
    mygeo::Point(-51.95165, -6.80845),
    mygeo::Point(-84.9373, -39.5782),
    mygeo::Point(22.533015, 8.60245),
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    mygeo::Point check_value = mygeo::line_mid(points[i].first, points[i].second);

#ifdef DEBUG
    std::cout << "{ " << check_value.x << ", " << check_value.y
        << " } ?= { " << mids[i].x << ", " << mids[i].y << " }" << std::endl;
#endif

    CHECK(check_value == mids[i])
  }

  END_TEST_CASE
  }



  {
  START_TEST_CASE("mygeo::line_mid \\ for Line")
#ifdef CIN_TEST

  size_t n_test;

#ifdef MANUAL_INPUT
  n_test = 5;
  std::cout << "Input " << n_test << " pairs of lines and points in the next order:\n\t"
            << "p1.x p1.y p2.x p2.y m.x m.y, "
            << "where p1 and p2 are start and end of the line, and m is its middle point" << std::endl;
#else
  std::cin >> n_test;
#endif

  std::array<mygeo::Line, n_test> lines;
  std::array<mygeo::Point, n_test> mids;

  for(size_t i = 0; i < n_test; ++i)
  {
    std::array<double, 6> coord;
    for(auto elem : coord)
      std::cin >> elem;
    mygeo::Point p1(coord[0], coord[1]);
    mygeo::Point p2(coord[2], coord[3]);
    lines[i] = std::move(mygeo::Line(p1, p2));
    mygeo::Point p3(coord[4], coord[5]);
    mids[i] = std::move(p3);
  }
 
#else

  constexpr size_t n_test = 5;

  std::array<mygeo::Line, n_test> lines = {
    mygeo::Line(mygeo::Point(0.0, 0.0), mygeo::Point(2.0, 2.0)),
    mygeo::Line(mygeo::Point(73.5822, -67.1408), mygeo::Point(-25.7569, 62.2525)),
    mygeo::Line(mygeo::Point(-13.4589, -55.7949), mygeo::Point(-90.4444, 42.1780)),
    mygeo::Line(mygeo::Point(-86.0303, -71.6530), mygeo::Point(-83.8443, -7.50341)),
    mygeo::Line(mygeo::Point(52.9091, 38.1110), mygeo::Point(-7.84307, -20.9061)),
  };

  std::array<mygeo::Point, n_test> mids = {
    mygeo::Point(1.0, 1.0),
    mygeo::Point(23.91265, -2.44415),
    mygeo::Point(-51.95165, -6.80845),
    mygeo::Point(-84.9373, -39.5782),
    mygeo::Point(22.533015, 8.60245),
  };
#endif

  for(size_t i = 0; i < n_test; ++i)
  {
    mygeo::Point check_value = mygeo::line_mid(lines[i]);

#ifdef DEBUG
    std::cout << "{ " << check_value.x << ", " << check_value.y
        << " } ?= { " << mids[i].x << ", " << mids[i].y << " }" << std::endl;
#endif

    CHECK(check_value == mids[i])
  }

  END_TEST_CASE
  }
}

