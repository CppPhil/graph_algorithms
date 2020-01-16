#include "gtest/gtest.h"
#include <cstddef>
#include <string>
#include <vertex.hpp>

using namespace std;
using namespace gp;

TEST(vertex, identifier)
{
    const Vertex<string, nullptr_t> v{"MyVertex", nullptr};

    EXPECT_EQ(v.identifier(), string{"MyVertex"});
}

TEST(vertex, data)
{
    const Vertex<string, int> v{"MyVertex", 5};

    EXPECT_EQ(v.data(), 5);
}

TEST(vertex, equality)
{
    const Vertex<string, int> v1{"A", 0};
    const Vertex<string, int> v2{"B", 1};

    EXPECT_EQ(v1, v1);
    EXPECT_FALSE(v1 == v2);
    EXPECT_EQ(v2, v2);
    EXPECT_FALSE(v2 == v1);
}

TEST(vertex, inequality)
{
    const Vertex<string, int> v1{"A", 0};
    const Vertex<string, int> v2{"B", 1};

    EXPECT_FALSE(v1 != v1);
    EXPECT_NE(v1, v2);
    EXPECT_FALSE(v2 != v2);
    EXPECT_NE(v2, v1);
}

TEST(vertex, swap)
{
    Vertex<int, int> v1{0, 1};
    Vertex<int, int> v2{2, 3};
    swap(v1, v2);

    EXPECT_EQ(v1.identifier(), 2);
    EXPECT_EQ(v1.data(), 3);
    EXPECT_EQ(v2.identifier(), 0);
    EXPECT_EQ(v2.data(), 1);
}
