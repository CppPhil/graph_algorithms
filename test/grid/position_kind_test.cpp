#include "gtest/gtest.h"
#include <grid/position_kind.hpp>
#include <sstream>
#include <type_traits>

using namespace gp;
using namespace grid;

class PositionKindPrintTest : public ::testing::Test {
public:
    using this_type = PositionKindPrintTest;
    using base_type = ::testing::Test;

    PositionKindPrintTest() : oss{} {}

protected:
    virtual void SetUp() override { oss.str(""); }

    virtual void TearDown() override {}

    std::ostringstream oss;
};

TEST(positionKind, value)
{
    static_assert(
        std::is_same_v<std::underlying_type_t<PositionKind>, int>,
        "underyling type of PositionKind was an unexpected type!");

    EXPECT_EQ(static_cast<int>(PositionKind::Start), 1);
    EXPECT_EQ(static_cast<int>(PositionKind::Goal), 2);
    EXPECT_EQ(static_cast<int>(PositionKind::Empty), 3);
    EXPECT_EQ(static_cast<int>(PositionKind::Wall), 4);
    EXPECT_EQ(static_cast<int>(PositionKind::OnPath), 5);
}

TEST_F(PositionKindPrintTest, printTestStartKind)
{
    oss << PositionKind::Start;
    EXPECT_EQ(oss.str(), "S");
}

TEST_F(PositionKindPrintTest, printTestGoalKind)
{
    oss << PositionKind::Goal;
    EXPECT_EQ(oss.str(), "G");
}

TEST_F(PositionKindPrintTest, printTestEmptyKind)
{
    oss << PositionKind::Empty;
    EXPECT_EQ(oss.str(), "E");
}

TEST_F(PositionKindPrintTest, printTestWallKind)
{
    oss << PositionKind::Wall;
    EXPECT_EQ(oss.str(), "W");
}

TEST_F(PositionKindPrintTest, printTestOnPathKind)
{
    oss << PositionKind::OnPath;
    EXPECT_EQ(oss.str(), "P");
}
