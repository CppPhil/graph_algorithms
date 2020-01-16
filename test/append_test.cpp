#include "gtest/gtest.h"
#include <append.hpp>
#include <vector>

using namespace gp;
using namespace std;

TEST(append, firstEmpty)
{
    const vector<int> result{append(vector<int>{}, vector<int>{1, 2, 3, 4})};

    const vector<int> expected{1, 2, 3, 4};

    EXPECT_EQ(result, expected);
}

TEST(append, secondEmpty)
{
    const vector<int> result{append(vector<int>{1, 2, 3}, vector<int>{})};

    const vector<int> expected{1, 2, 3};

    EXPECT_EQ(result, expected);
}

TEST(append, appendTest)
{
    const vector<int> result{
        append(vector<int>{1, 2, 3}, vector<int>{4, 5, 6})};

    const vector<int> expected{1, 2, 3, 4, 5, 6};

    EXPECT_EQ(result, expected);
}
