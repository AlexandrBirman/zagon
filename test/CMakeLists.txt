include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRCS hello_test.cpp)
add_executable(zagon_tests ${SRCS})

target_include_directories(zagon_tests PUBLIC ./)
target_link_libraries(zagon_tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(zagon_tests)

add_custom_target(check ALL COMMAND zagon_tests)

include_directories(../src)