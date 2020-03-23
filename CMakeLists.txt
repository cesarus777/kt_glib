cmake_minimum_required(VERSION 3.13)

project(ktglib)

add_library(ktglib-src OBJECT
    glib/sources/base_algorithm.cpp
    glib/sources/math_macro.cpp
)

add_library(ktglib-test OBJECT
    glib/sources/t/unit_test.cpp
)

include_directories(glib/include)

add_executable(ktglib-standalone standalone/main_standalone.cpp $<TARGET_OBJECTS:ktglib-src>)
add_executable(unit-tests tests/main_test.cpp $<TARGET_OBJECTS:ktglib-test>)

