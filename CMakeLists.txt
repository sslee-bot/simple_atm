cmake_minimum_required(VERSION 3.14)
project(simple_atm CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} example.cpp src/atm_controller.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/v1.14.0.tar.gz)
FetchContent_MakeAvailable(googletest)

add_executable(atm_controller_test test/atm_controller_test.cpp src/atm_controller.cpp)
target_include_directories(atm_controller_test PRIVATE include)
target_link_libraries(atm_controller_test PRIVATE GTest::gtest_main)
