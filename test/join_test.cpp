#include "gtest/gtest.h"
#include <join.hpp>

TEST(join, joinTest)
{
    std::string elements[] = {"aap", "noot", "mies"};

    typedef std::vector<std::string> strings;

    EXPECT_EQ("", gp::join(strings(), ""));
    EXPECT_EQ("", gp::join(strings(), "bla"));
    EXPECT_EQ("aap", gp::join(strings(elements, elements + 1), ""));
    EXPECT_EQ("aap", gp::join(strings(elements, elements + 1), "#"));
    EXPECT_EQ("aap", gp::join(strings(elements, elements + 1), "##"));
    EXPECT_EQ("aapnoot", gp::join(strings(elements, elements + 2), ""));
    EXPECT_EQ("aap#noot", gp::join(strings(elements, elements + 2), "#"));
    EXPECT_EQ("aap##noot", gp::join(strings(elements, elements + 2), "##"));
    EXPECT_EQ("aapnootmies", gp::join(strings(elements, elements + 3), ""));
    EXPECT_EQ("aap#noot#mies", gp::join(strings(elements, elements + 3), "#"));
    EXPECT_EQ(
        "aap##noot##mies", gp::join(strings(elements, elements + 3), "##"));
    EXPECT_EQ(
        "aap  noot  mies", gp::join(strings(elements, elements + 3), "  "));

    EXPECT_EQ("aapnootmies", gp::join(strings(elements, elements + 3), "\0"));
    EXPECT_EQ(
        "aapnootmies",
        gp::join(
            strings(elements, elements + 3), std::string("\0", 1).c_str()));
    EXPECT_EQ(
        "aapnootmies",
        gp::join(
            strings(elements, elements + 3), std::string("\0+", 2).c_str()));
    EXPECT_EQ(
        "aap+noot+mies",
        gp::join(
            strings(elements, elements + 3), std::string("+\0", 2).c_str()));
}
