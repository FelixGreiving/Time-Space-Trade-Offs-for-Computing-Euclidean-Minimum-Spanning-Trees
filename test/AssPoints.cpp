#include <gtest/gtest.h>
#include "AssPoints.hpp"

TEST(AssPoints, Konstruktortest){
    K::Point_3 p1{1,1,1};
    K::Point_3 p2{2,2,1};
    AssPoints AssPoints{p1,p2};

    EXPECT_EQ(AssPoints.p.x(), 1);

    EXPECT_EQ(AssPoints.p, p1);

    EXPECT_EQ(AssPoints.associatedPoint, p2);
}


TEST(AssPoints, KleinerOperator){
  K::Point_3 p1{1,1,1};
  K::Point_3 p2{1,2,1};
  K::Point_3 p3{2,1,1};
  K::Point_3 p4{2,2,1};

  AssPoints p11{p1,p1};
  AssPoints p22{p2,p1};
  AssPoints p33{p3,p1};
  AssPoints p44{p4,p1};
  
  EXPECT_TRUE(p11<p22);
  EXPECT_TRUE(p22<p33);
  EXPECT_TRUE(p33<p44);
  EXPECT_FALSE(p22<p11);
  EXPECT_FALSE(p33<p22);
  EXPECT_FALSE(p44<p33);
}


TEST(AssPoints, GleichOperator){
  K::Point_3 p1{1,1,1};
  K::Point_3 p2{1,2,1};
  K::Point_3 p3{2,1,1};
  K::Point_3 p4{2,2,1};

  AssPoints p11{p1,p1};
  AssPoints p22{p2,p1};
  AssPoints p33{p3,p1};
  AssPoints p44{p4,p1};

  EXPECT_TRUE(p11==p11);
  EXPECT_TRUE(p22==p22);
  EXPECT_TRUE(p33==p33);
  EXPECT_TRUE(p44==p44);
  EXPECT_FALSE(p11==p22);
  EXPECT_FALSE(p11==p33);
  EXPECT_FALSE(p11==p44);
  EXPECT_FALSE(p22==p33);
  EXPECT_FALSE(p22==p44);
  EXPECT_FALSE(p33==p44);
}