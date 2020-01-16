#include "gtest/gtest.h"
#include <grid/position.hpp>
#include <pl/size_t.hpp>
#include <sstream>

using namespace gp;
using namespace grid;
using namespace pl::literals::integer_literals;

class PositionTest : public ::testing::Test {
public:
    using this_type = PositionTest;
    using base_type = ::testing::Test;

protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}

    const Position position{Column{5}, Row{7}};
};

TEST_F(PositionTest, columnTest) { EXPECT_EQ(position.column().value(), 5_zu); }

TEST_F(PositionTest, rowTest) { EXPECT_EQ(position.row().value(), 7_zu); }

TEST_F(PositionTest, printTest)
{
    std::ostringstream oss{};
    oss << position;

    EXPECT_EQ(
        oss.str(), "{\"column\": {\"value\": 5},\"row\": {\"value\": 7}}");
}
