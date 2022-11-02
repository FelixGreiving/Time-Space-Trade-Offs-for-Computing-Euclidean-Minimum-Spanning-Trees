#include <gtest/gtest.h>
#include "AssEdges.hpp"

TEST(AssEdges, Konstruktortest){
    K::Point_3 p1{1,1,1};
    K::Point_3 p2{2,2,1};
    AssPoints assPoints1{p1,p2};
    AssPoints assPoints2{p2,p1};
    AssEdges assEdge{assPoints1, assPoints2};

    EXPECT_EQ(assEdge.p1, assPoints1);

    EXPECT_EQ(assEdge.p2, assPoints2);
}