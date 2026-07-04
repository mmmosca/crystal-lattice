#include <gtest/gtest.h>
#include <crystal_lattice/crystalattice.h>

struct ReducedTestCase
{
    std::vector<double> cell_parameters;
};

class ReducedParameterizedTest :
    public ::testing::TestWithParam<ReducedTestCase>
{
};

INSTANTIATE_TEST_SUITE_P(
    NiggliUnitCellTests,
    ReducedParameterizedTest,
    ::testing::Values(
        // All axes are already reduced
        ReducedTestCase{std::vector<double> {10, 10, 10, 90, 90, 90}},
        // Z is not reduced with respect to Y 
        ReducedTestCase{std::vector<double> {10, 10, 10*std::sqrt(2), 45, 90, 90}},
        // Z is not reduced with respect to X
        ReducedTestCase{std::vector<double> {10, 10, 10*std::sqrt(2), 90, 45, 90}},
        // Y is not reduced with respect to Z 
        ReducedTestCase{std::vector<double> {10, 10*std::sqrt(2), 10, 90, 90, 45}},
        // Y is not reduced with respect to X 
        ReducedTestCase{std::vector<double> {10, 10*std::sqrt(2), 10, 45, 90, 90}},
        // X is not reduced with respect to Y
        ReducedTestCase{std::vector<double> {10*std::sqrt(2), 10, 10, 90, 90, 45}},
        // X is not reduced with respect to Z
        ReducedTestCase{std::vector<double> {10*std::sqrt(2), 10, 10, 90, 45, 90}}
    )
);

TEST_P(ReducedParameterizedTest, NiggliReducedMode)
{
    Lattice lattice;
    const auto& testCase = GetParam();
    
    lattice.setCellParameters(testCase.cell_parameters);
    lattice.updateParametersToReducedMode();

    double a = lattice.cell_parameters[0],
        b = lattice.cell_parameters[1],
        c = lattice.cell_parameters[2],
        alpha = lattice.cell_parameters[3] * pi / 180,
        beta = lattice.cell_parameters[4] * pi / 180,
        gamma = lattice.cell_parameters[5] * pi / 180;
        
    EXPECT_LE(std::abs(a * std::cos(gamma)), b/2);
    EXPECT_LE(std::abs(b * std::cos(gamma)), a/2);
    EXPECT_LE(std::abs(b * std::cos(alpha)), c/2);
    EXPECT_LE(std::abs(c * std::cos(alpha)), b/2);
    EXPECT_LE(std::abs(c * std::cos(beta)), a/2);
    EXPECT_LE(std::abs(a * std::cos(beta)), c/2);

    EXPECT_TRUE(
        ((a * b * std::cos(gamma) >= 0) && (b * c * std::cos(alpha) >= 0) && (c * a * std::cos(beta) >= 0)) ||
        ((a * b * std::cos(gamma) <= 0) && (b * c * std::cos(alpha) <= 0) && (c * a * std::cos(beta) <= 0))
    );
}
