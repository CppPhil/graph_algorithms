#include "gtest/gtest.h"
#include <edge.hpp>
#include <string>

using namespace gp;
using namespace std;

const Edge<string, int, string> e{"EDGE", "V1", "V2", 25};

TEST(edge, identifier) { EXPECT_EQ(e.identifier(), string{"EDGE"}); }

TEST(edge, source) { EXPECT_EQ(e.source(), string{"V1"}); }

TEST(edge, target) { EXPECT_EQ(e.target(), string{"V2"}); }

TEST(edge, data) { EXPECT_EQ(e.data(), 25); }

TEST(edge, equality)
{
    const Edge<string, int, string> e1{"EDGE1", "V1", "V2", 90};

    const Edge<string, int, string> e2{"EDGE2", "V2", "V1", 40};

    EXPECT_EQ(e1, e1);
    EXPECT_EQ(e2, e2);
    EXPECT_FALSE(e1 == e2);
    EXPECT_FALSE(e2 == e1);
}

TEST(edge, inequality)
{
    const Edge<string, int, string> e1{"EDGE1", "V1", "V2", 90};

    const Edge<string, int, string> e2{"EDGE2", "V2", "V1", 40};

    EXPECT_NE(e1, e2);
    EXPECT_NE(e2, e1);
    EXPECT_FALSE(e1 != e1);
    EXPECT_FALSE(e2 != e2);
}

TEST(edge, swap)
{
    Edge<string, int, string> e1{"EDGE1", "V1", "V2", 90};

    Edge<string, int, string> e2{"EDGE2", "V2", "V1", 40};

    swap(e1, e2);

    EXPECT_EQ(e1.identifier(), string{"EDGE2"});
    EXPECT_EQ(e1.source(), string{"V2"});
    EXPECT_EQ(e1.target(), string{"V1"});
    EXPECT_EQ(e1.data(), 40);

    EXPECT_EQ(e2.identifier(), string{"EDGE1"});
    EXPECT_EQ(e2.source(), string{"V1"});
    EXPECT_EQ(e2.target(), string{"V2"});
    EXPECT_EQ(e2.data(), 90);
}