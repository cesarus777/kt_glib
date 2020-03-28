#include <array>
#include <iostream>

#include <ellipse.hpp>
#include <macro/error_handler.hpp>
#include <macro/math_macro.hpp>
#include <macro/test.hpp>

void test_base_hpp();
void test_circle_hpp();
void test_ellipse_hpp();
void test_polygon_hpp();
void test_rectangle_hpp();
void test_square_hpp();
void test_triangle_hpp();

void test_includes()
{
  test_base_hpp();
  test_circle_hpp();
  test_ellipse_hpp();
  test_polygon_hpp();
  test_rectangle_hpp();
  test_square_hpp();
  test_triangle_hpp();
}

void test_base_hpp() {}

void test_circle_hpp() {}

void test_ellipse_hpp()
{
  START_TEST_MODULE("mygeo::Ellipse")
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::Ellipse")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " triplets of"
              << "distance and 2 points in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y verity, "
              << "where p1 and p2 are focuses of Ellipse, dist is double major-axis, "
              << "and verity is ability to create such Ellipse" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;
    std::array<bool, n_test> bools;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 5> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      focuses[i] = std::move(std::make_pair(p1, p2));
      bool b;
      std::cin >> b;
      bools[i] = b;
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      2.0, 3.0, 1.0, 0.5, 10.0
    };

    constexpr std::array<bool, n_test> bools = {
      false, true, true, false, true,
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse(focuses[i].first, focuses[i].second, dists[i]);
        SUB_CHECK(bools[i] == true)
      }
      catch(std::invalid_argument &e)
      {
        SUB_CHECK(bools[i] == false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::focuses")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " triplets of"
              << "distance and 2 points in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 5> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      focuses[i] = std::move(std::make_pair(p1, p2));
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        bool check_value = (e.focuses() == focuses[i]);
        SUB_CHECK(check_value == true)
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::fdistance")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " triplets of"
              << "distance and 2 points in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 5> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      focuses[i] = std::move(std::make_pair(p1, p2));
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        bool check_value = (e.fdistance() == distance(focuses[i].first, focuses[i].second));
        SUB_CHECK(check_value == true)
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::eccentricity")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " triplets of"
              << "distance and 2 points in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 5> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      focuses[i] = std::move(std::make_pair(p1, p2));
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        double eccentricity = distance(focuses[i].first, focuses[i].second) / dists[i];
        bool check_value = (e.eccentricity() == eccentricity);
        SUB_CHECK(check_value == true)
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::center")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " distances and triplets of"
              << "points in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y p3.x, p3.y, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis, "
              << "and p3 is center of Ellipse" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;
    std::array<mygeo::Point, n_test> centers;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, > arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      mygeo::Point p3(arr[5], arr[6]);
      focuses[i] = std::move(std::make_pair(p1, p2));
      centers[i] = std::move(p3);
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };

    const std::array<mygeo::Point, n_test> centers = {
      mygeo::Point(0.0, 0.0),
      mygeo::Point(0.0, 0.0),
      mygeo::Point(0.75, 0.75),
      mygeo::Point(0.75, 0.75),
      mygeo::Point(4.5, 2.0),
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        bool check_value = (e.center() == centers[i]);
        SUB_CHECK(check_value == true)
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::perimeter")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " sets, each contains "
              << "distance 2 points and perimeter in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y perim, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis, "
              << "perim is perimeter" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;
    std::array<double, n_test> perimeters;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 6> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      focuses[i] = std::move(std::make_pair(p1, p2));
      perimeters[i] = arr[5];
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };

    constexpr std::array<double, n_test> perimeters = {
      15.06008, 8.27263, 2.70309, 128.01155, 20.92950
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        double perim = e.perimeter();
        double diff = std::abs(perim - perimeters[i]);
        double eps = perimeters[i] * 0.0063;
        bool check_value = (diff < eps);
        SUB_CHECK(check_value == true)
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::area")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " sets, each contains "
              << "distance 2 points and perimeter in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y area, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis, "
              << "area is its area" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;
    std::array<double, n_test> areas;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 6> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      focuses[i] = std::move(std::make_pair(p1, p2));
      areas[i] = arr[5];
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };

    constexpr std::array<double, n_test> areas = {
      17.99573, 5.268611, 0.5553604, 1288.05297, 13.603495,
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        bool check_value = EQUAL(e.area(), areas[i]);
        SUB_CHECK(check_value == true)
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  {
    START_TEST_SUBMODULE("mygeo::Ellipse::containsPoint")
#ifdef CIN_TEST
    size_t n_test;
#ifdef MANUAL_TEST
    n_test = 5;
    std::cout << "Input " << n_test << " distances and triplets of"
              << "points in the next order:\n\t"
              << "dist p1.x p1.y p2.x p2.y p3.x p3.y verity, "
              << "where p1 and p2 are focuses of Ellipse, "
              << "dist is double major-axis, "
              << "p3 is testing point of Ellipse, "
              << "and verity is its belonging to the Ellipse" << std::endl;
#else
    std::cin >> n_test;
#endif

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses;
    std::array<double, n_test> dists;
    std::array<mygeo::Point, n_test> points;
    std::array<bool, n_test> bools;

    for(size_t i = 0; i < n_test; ++i)
    {
      std::array<double, 8> arr;
      for(auto elem : arr)
        std::cin >> elem;
      dists[i] = arr[0];
      mygeo::Point p1(arr[1], arr[2]);
      mygeo::Point p2(arr[3], arr[4]);
      mygeo::Point p3(arr[5], arr[6]);
      focuses[i] = std::move(std::make_pair(p1, p2));
      points[i] = std::move(p3);
      bool b;
      std::cin >> b;
      bools[i] = b;
    }
#else

    constexpr size_t n_test = 5;

    std::array<std::pair<mygeo::Point, mygeo::Point>, n_test> focuses = {
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(-1.0, 0.0), mygeo::Point(1.0, 0.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.5, 0.5), mygeo::Point(1.0, 1.0)),
      std::make_pair( mygeo::Point(0.0, 0.0), mygeo::Point(9.0, 4.0)),
    };

    constexpr std::array<double, n_test> dists = {
      5.0, 3.0, 1.0, 40.5, 10.0
    };

    const std::array<mygeo::Point, n_test> points = {
      mygeo::Point(0.0, 0.0),
      mygeo::Point(2.30, 0.01),
      mygeo::Point(0.9, 1.1),
      mygeo::Point(12.75, 13.05),
      mygeo::Point(0.5, 1.0),
    };

    constexpr std::array<bool, n_test> bools = {
      true, false, true, true, false,
    };
#endif

    for(size_t i = 0; i < n_test; ++i)
    {
      try
      {
        mygeo::Ellipse e(focuses[i].first, focuses[i].second, dists[i]);
        bool check_value = e.containsPoint(points[i]);
        SUB_CHECK(check_value == bools[i])
      }
      catch(std::invalid_argument &e)
      {
        std::cerr << "Exeption : " << e.what() << std::endl;
        SUB_CHECK(false)
      }
    }

    END_TEST_SUBMODULE
  }
  END_TEST_MODULE
}

void test_polygon_hpp() {}

void test_rectangle_hpp() {}

void test_square_hpp() {}

void test_triangle_hpp() {}

