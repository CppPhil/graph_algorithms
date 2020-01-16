#include "gtest/gtest.h"
#include <ciso646>
#include <grid/create.hpp>
#include <grid/data_structure.hpp>
#include <pl/numeric.hpp>
#include <pl/size_t.hpp>

using namespace gp;
using namespace pl::literals::integer_literals;

class GridDataStructureTest : public ::testing::Test {
public:
    using this_type = GridDataStructureTest;
    using base_type = ::testing::Test;

protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}

    const grid::DataStructure grid{grid::create()};
};

TEST(GridTest, zeroColumns)
{
    const auto lambda = [] {
        return grid::DataStructure{grid::Column{0_zu}, grid::Row{1_zu}};
    };
    EXPECT_THROW(lambda(), std::out_of_range);
}

TEST(GridTest, zeroRows)
{
    const auto lambda = [] {
        return grid::DataStructure{grid::Column{1_zu}, grid::Row{0_zu}};
    };
    EXPECT_THROW(lambda(), std::out_of_range);
}

TEST_F(GridDataStructureTest, columnCountTest)
{
    EXPECT_EQ(grid.columnCount().value(), 15_zu);
}

TEST_F(GridDataStructureTest, rowCountTest)
{
    EXPECT_EQ(grid.rowCount().value(), 15_zu);
}

TEST_F(GridDataStructureTest, atTest)
{
    const std::size_t startColumn{0};
    const std::size_t startRow{12};

    const std::size_t goalColumn{13};
    const std::size_t goalRow{2};

    const std::size_t firstWallRow{2};
    const std::size_t firstWallColumnBegin{5};
    const std::size_t firstWallColumnEnd{12};

    const std::size_t secondWallColumn{12};
    const std::size_t secondWallRowBegin{3};
    const std::size_t secondWallRowEnd{12};

    const std::size_t thirdWallRow{12};
    const std::size_t thirdWallColumnBegin{2};
    const std::size_t thirdWallColumnEnd{11};

    for (std::size_t column{0}; column < grid.columnCount().value(); ++column) {
        for (std::size_t row{0}; row < grid.rowCount().value(); ++row) {
            const grid::Column   curCol{column};
            const grid::Row      curRow{row};
            const grid::Position currentPosition{curCol, curRow};

            if ((column == startColumn) and (row == startRow)) {
                EXPECT_EQ(grid.at(currentPosition), grid::PositionKind::Start);
            }
            else if ((column == goalColumn) and (row == goalRow)) {
                EXPECT_EQ(grid.at(currentPosition), grid::PositionKind::Goal);
            }
            else if (
                ((row == firstWallRow)
                 and pl::is_between(
                     column, firstWallColumnBegin, firstWallColumnEnd))
                or ((column == secondWallColumn)
                    and pl::is_between(
                        row, secondWallRowBegin, secondWallRowEnd))
                or ((row == thirdWallRow)
                    and pl::is_between(
                        column, thirdWallColumnBegin, thirdWallColumnEnd))) {
                EXPECT_EQ(grid.at(currentPosition), grid::PositionKind::Wall);
            }
            else {
                EXPECT_EQ(grid.at(currentPosition), grid::PositionKind::Empty);
            }
        }
    }
}

TEST_F(GridDataStructureTest, stringTest)
{
    const std::string expected{
        R"(EEEEEEEEEEEEEEE
EEEEEEEEEEEEEEE
EEEEEWWWWWWWWGE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
EEEEEEEEEEEEWEE
SEWWWWWWWWWWWEE
EEEEEEEEEEEEEEE
EEEEEEEEEEEEEEE
S: start
G: goal
E: empty
W: wall
P: on path)"};
    const std::string actual{grid.asString()};
    EXPECT_EQ(expected, actual);
}
