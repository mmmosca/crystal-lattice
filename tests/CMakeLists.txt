include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)

# Prevent overriding parent compiler settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(
    tests
    test_crystalattice.cpp
)

target_link_libraries(
    tests
    PRIVATE
    Eigen3::Eigen
    periodic_point_cloud
    crystal_lattice
    GTest::gtest_main
)

gtest_discover_tests(tests)
