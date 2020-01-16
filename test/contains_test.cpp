#include "gtest/gtest.h"
#include <contains.hpp>
#include <vector>

using namespace gp;
using namespace std;

TEST(contains, negativeTest)
{
    const vector<int> data{1, 2, 3, 4, 5, 6, 7};
    EXPECT_FALSE(contains(data, 0));
    EXPECT_FALSE(contains(data, 8));
}

TEST(contains, positiveTest)
{
    const vector<int> data{1, 2, 3, 4, 5};
    EXPECT_TRUE(contains(data, 1));
    EXPECT_TRUE(contains(data, 2));
    EXPECT_TRUE(contains(data, 3));
    EXPECT_TRUE(contains(data, 4));
    EXPECT_TRUE(contains(data, 5));
}
