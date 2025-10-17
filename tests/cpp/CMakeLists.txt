include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_orderbook test_orderbook.cpp)
target_link_libraries(test_orderbook PRIVATE
  orderbook
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_orderbook)
