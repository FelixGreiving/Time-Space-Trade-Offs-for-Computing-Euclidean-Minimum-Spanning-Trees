#include <gtest/gtest.h>
#include "utils.hpp"

// Demonstrate some basic assertions.
TEST(utils, binarySearch) {
  K::Point_3 p1{9,1,1};
  K::Point_3 p2{8,3,1};
  K::Point_3 p3{8,2,1};
  K::Point_3 p4{7,2,1};
  K::Point_3 p5{4,4,1};
  K::Point_3 p6{4,1,1};
  K::Point_3 p7{2,7,1};

  std::vector<K::Point_3> vecPoints(8);
  vecPoints[0] = p1;
  vecPoints[1] = p2;
  vecPoints[2] = p3;
  vecPoints[3] = p4;
  vecPoints[4] = p5;
  vecPoints[5] = p6;
  vecPoints[6] = p7;

  EXPECT_TRUE(binarySearch(vecPoints, 9, 1));
  EXPECT_TRUE(binarySearch(vecPoints, 7,2));
  EXPECT_TRUE(binarySearch(vecPoints, 2, 7));
  EXPECT_FALSE(binarySearch(vecPoints, 1, 1));
  EXPECT_FALSE(binarySearch(vecPoints, 7, 3));

}

// Demonstrate some basic assertions.
TEST(utils, minBinarySearch) {
  K::Point_3 p1{9,1,1};
  K::Point_3 p2{8,3,1};
  K::Point_3 p3{8,2,1};
  K::Point_3 p4{7,2,1};
  K::Point_3 p5{4,4,1};
  K::Point_3 p6{4,1,1};
  K::Point_3 p7{2,7,1};

  std::vector<K::Point_3> vecPoints(8);
  vecPoints[0] = p1;
  vecPoints[1] = p2;
  vecPoints[2] = p3;
  vecPoints[3] = p4;
  vecPoints[4] = p5;
  vecPoints[5] = p6;
  vecPoints[6] = p7;

  EXPECT_EQ(minBinarySearch(vecPoints, 9, 0), 0);
  EXPECT_EQ(minBinarySearch(vecPoints, 8, 2), 1);
  EXPECT_EQ(minBinarySearch(vecPoints, 8, 1), 2);
  EXPECT_EQ(minBinarySearch(vecPoints, 2, 7), 5);
  EXPECT_EQ(minBinarySearch(vecPoints, 2, 6), 6);
  // Laut Voraussetzung sind Punkte größer gleich (9,1) nicht erlaubt
}

TEST(utils, maxBinarySearch){
  K::Point_3 p1{9,1,1};
  K::Point_3 p2{8,3,1};
  K::Point_3 p3{8,2,1};
  K::Point_3 p4{7,2,1};
  K::Point_3 p5{4,4,1};
  K::Point_3 p6{4,1,1};
  K::Point_3 p7{2,7,1};

  std::vector<K::Point_3> vecPoints(8);
  vecPoints[0] = p1;
  vecPoints[1] = p2;
  vecPoints[2] = p3;
  vecPoints[3] = p4;
  vecPoints[4] = p5;
  vecPoints[5] = p6;
  vecPoints[6] = p7;

  EXPECT_EQ(maxBinarySearch(vecPoints, 9, 1), 1);
  EXPECT_EQ(maxBinarySearch(vecPoints, 9, 0), 1);
  EXPECT_EQ(maxBinarySearch(vecPoints, 8, 2), 3);
  EXPECT_EQ(maxBinarySearch(vecPoints, 8, 1), 3);
  EXPECT_EQ(maxBinarySearch(vecPoints, 2, 8), 6);
  // Laut Voraussetzung sindPunkte kleiner gleich (2,7) nicht erlaubt
}