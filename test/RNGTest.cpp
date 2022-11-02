#include "RNGTest.hpp"


TEST_F(RNGTest, calcRNG_allgemein) {
  std::ifstream in("data/Beispiele/RNG_Beispiel_1/RNG_Beispiel_1.txt");
  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;
  std::set<Point> inputPoints(begin, end);

  init(inputPoints, 0);
  calculateRNG();


  // Manuelle Überprüfung, ob die Adjazenzlisten korrekt erstellt wurden
  std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> adjLists;
  
  AssPoints p1{K::Point_3{80,4,1}, K::Point_3{80,4,1}};
  struct OrientedAdjList e1{p1};
  adjLists.insert(e1);


  AssPoints p2{K::Point_3{79, 33, 1}, K::Point_3{79, 33, 1}};
  struct OrientedAdjList e2{p2};
  adjLists.insert(e2);
  AssEdges edge1{p2, p1};

  auto it = adjLists.find(e2);
  it->e.insert(edge1);


  AssPoints p3{K::Point_3{70, 64, 1}, K::Point_3{70, 64, 1}};
  struct OrientedAdjList e3{p3};
  adjLists.insert(e3);


  AssPoints p4{K::Point_3{64, 62, 1}, K::Point_3{64, 62, 1}};
  struct OrientedAdjList e4{p4};
  adjLists.insert(e4);
  AssEdges edge2{p4, p3};

  it = adjLists.find(e4);
  it->e.insert(edge2);


  AssPoints p5{K::Point_3{64, 56, 1}, K::Point_3{64, 56, 1}};
  struct OrientedAdjList e5{p5};
  adjLists.insert(e5);
  AssEdges edge3{p5, p4};

  it = adjLists.find(e5);
  it->e.insert(edge3);


  AssPoints p6{K::Point_3{60, 46, 1}, K::Point_3{60, 46, 1}};
  struct OrientedAdjList e6{p6};
  adjLists.insert(e6);
  AssEdges edge4{p6, p2};
  AssEdges edge5{p6, p5};

  it = adjLists.find(e6);
  it->e.insert(edge4);
  it->e.insert(edge5);


  AssPoints p7{K::Point_3{48, 23, 1}, K::Point_3{48, 23, 1}};
  struct OrientedAdjList e7{p7};
  adjLists.insert(e7);


  AssPoints p8{K::Point_3{47, 37, 1}, K::Point_3{47, 37, 1}};
  struct OrientedAdjList e8{p8};
  adjLists.insert(e8);
  AssEdges edge6{p8, p6};

  it = adjLists.find(e8);
  it->e.insert(edge6);


  AssPoints p9{K::Point_3{46, 33, 1}, K::Point_3{46, 33, 1}};
  struct OrientedAdjList e9{p9};
  adjLists.insert(e9);
  AssEdges edge7{p9, p8};
  AssEdges edge8{p9, p7};

  it = adjLists.find(e9);
  it->e.insert(edge7);
  it->e.insert(edge8);


  AssPoints p10{K::Point_3{40, 65, 1}, K::Point_3{40, 65, 1}};
  struct OrientedAdjList e10{p10};
  adjLists.insert(e10);
  AssEdges edge9{p10, p4};

  it = adjLists.find(e10);
  it->e.insert(edge9);


  AssPoints p11{K::Point_3{39, 19, 1}, K::Point_3{39, 19, 1}};
  struct OrientedAdjList e11{p11};
  adjLists.insert(e11);
  AssEdges edge10{p11, p7};

  it = adjLists.find(e11);
  it->e.insert(edge10);


  AssPoints p12{K::Point_3{39, 4, 1}, K::Point_3{39, 4, 1}};
  struct OrientedAdjList e12{p12};
  adjLists.insert(e12);
  AssEdges edge11{p12, p11};

  it = adjLists.find(e12);
  it->e.insert(edge11);


  AssPoints p13{K::Point_3{32, 49, 1}, K::Point_3{32, 49, 1}};
  struct OrientedAdjList e13{p13};
  adjLists.insert(e13);
  AssEdges edge12{p13, p8};
  AssEdges edge13{p13, p10};

  it = adjLists.find(e13);
  it->e.insert(edge12);
  it->e.insert(edge13);


  AssPoints p14{K::Point_3{30, 49, 1}, K::Point_3{30, 49, 1}};
  struct OrientedAdjList e14{p14};
  adjLists.insert(e14);
  AssEdges edge14{p14, p13};

  it = adjLists.find(e14);
  it->e.insert(edge14);


  AssPoints p15{K::Point_3{28, 22, 1}, K::Point_3{28, 22, 1}};
  struct OrientedAdjList e15{p15};
  adjLists.insert(e15);
  AssEdges edge15{p15, p11};

  it = adjLists.find(e15);
  it->e.insert(edge15);


  AssPoints p16{K::Point_3{22, 27, 1}, K::Point_3{22, 27, 1}};
  struct OrientedAdjList e16{p16};
  adjLists.insert(e16);
  AssEdges edge16{p16, p15};
  AssEdges edge17{p16, p14};

  it = adjLists.find(e16);
  it->e.insert(edge16);
  it->e.insert(edge17);


  AssPoints p17{K::Point_3{17, 1, 1}, K::Point_3{17, 1, 1}};
  struct OrientedAdjList e17{p17};
  adjLists.insert(e17);
  AssEdges edge18{p17, p12};

  it = adjLists.find(e17);
  it->e.insert(edge18);


  AssPoints p18{K::Point_3{13, 52, 1}, K::Point_3{13, 52, 1}};
  struct OrientedAdjList e18{p18};
  adjLists.insert(e18);
  AssEdges edge19{p18, p14};

  it = adjLists.find(e18);
  it->e.insert(edge19);


  AssPoints p19{K::Point_3{2, 53, 1}, K::Point_3{2, 53, 1}};
  struct OrientedAdjList e19{p19};
  adjLists.insert(e19);
  AssEdges edge20{p19, p18};

  it = adjLists.find(e19);
  it->e.insert(edge20);


  AssPoints p20{K::Point_3{1, 10, 1}, K::Point_3{1, 10, 1}};
  struct OrientedAdjList e20{p20};
  adjLists.insert(e20);
  AssEdges edge21{p20, p17};

  it = adjLists.find(e20);
  it->e.insert(edge21);


  EXPECT_TRUE(compareGraphs(adjLists));
}


TEST_F(RNGTest, test_parser) {
  std::ifstream in("data/Beispiele/RNG_Beispiel_1/RNG_Beispiel_1.txt");
  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;
  std::set<Point> inputPoints(begin, end);

  init(inputPoints, 0);
  calculateRNG();


  // Manuelle Überprüfung, ob die Adjazenzlisten korrekt erstellt wurden
  std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> adjLists;

  auto adjListS = R"(
    //AssPoints
    p1 (80, 4) (80, 4)
    p2 (79, 33) (79, 33)
    p3 (70, 64) (70, 64)
    p4 (64, 62) (64, 62)
    p5 (64, 56) (64, 56)
    p6 (60, 46) (60, 46)
    p7 (48, 23) (48, 23)
    p8 (47, 37) (47, 37)
    p9 (46, 33) (46, 33)
    p10 (40, 65) (40, 65)
    p11 (39, 19) (39, 19)
    p12 (39, 4) (39, 4)
    p13 (32, 49) (32, 49)
    p14 (30, 49) (30, 49)
    p15 (28, 22) (28, 22)
    p16 (22, 27) (22, 27)
    p17 (17, 1) (17, 1)
    p18 (13, 52) (13, 52)
    p19 (2, 53) (2, 53)
    p20 (1, 10) (1, 10)

    //Edges
    e1 p2 p1
    e2 p4 p3
    e3 p5 p4
    e4 p6 p2
    e5 p6 p5
    e6 p8 p6
    e7 p9 p8
    e8 p9 p7
    e9 p10 p4
    e10 p11 p7
    e11 p12 p11
    e12 p13 p8
    e13 p13 p10
    e14 p14 p13
    e15 p15 p11
    e16 p16 p15
    e17 p16 p14
    e18 p17 p12
    e19 p18 p14
    e20 p19 p18
    e21 p20 p17

    //?
    p2 e1
    p4 e2
    p5 e3
    p6 e4
    p6 e5
    p8 e6
    p9 e7
    p9 e8
    p10 e9
    p11 e10
    p12 e11
    p13 e12
    p13 e13
    p14 e14
    p15 e15
    p16 e16
    p16 e17
    p17 e18
    p18 e19
    p19 e20
    p20 e21
  )";

  adjLists = parseAdjList(adjListS);


  EXPECT_TRUE(compareGraphs(adjLists));
}



TEST_F(RNGTest, calcRNG_same_angle_case_1) {
  std::ifstream in("data/Beispiele/RNG_Beispiel_2/RNG_gleiche_Winkel.txt");
  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;
  std::set<Point> inputPoints(begin, end);

  init(inputPoints, 0);
  calculateRNG();


  // Manuelle Überprüfung, ob die Adjazenzlisten korrekt erstellt wurden
  std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> adjLists;

  auto adjListS = R"(
    // AssPoints
    p1 (120, 112) (120, 112)
    p2 (118, 24) (118, 24)
    p3 (115, 22) (115, 22)
    p4 (110, 51) (110, 51)
    p5 (110, 21) (110, 21)
    p6 (104, 5) (104, 5)
    p7 (99, 56) (99, 56)
    p8 (98, 16) (98, 16)
    p9 (96, 74) (96, 74)
    p10 (96, 73) (96, 73)
    p11 (95, 118) (95, 118)
    p12 (82, 61) (82, 61)
    p13 (79, 17) (79, 17)
    p14 (67, 6) (67, 6)
    p15 (64, 105) (64, 105)
    p16 (56, 53) (56, 53)
    p17 (56, 4) (56, 4)
    p18 (55, 94) (55, 94)
    p19 (53, 33) (53, 33)
    p20 (48, 78) (48, 78)
    p21 (45, 17) (45, 17)
    p22 (43, 106) (43, 106)
    p23 (40, 116) (40, 116)
    p24 (39, 114) (39, 114)
    p25 (37, 8) (37, 8)
    p26 (15, 26) (15, 26)
    p27 (11, 29) (11, 29)
    p28 (8, 111) (8, 111)
    p29 (2, 9) (2, 9)
    p30 (0, 105) (0, 105) 

    // AssEdges
    e1 p3 p2
    e2 p4 p2
    e3 p5 p3
    e4 p7 p4
    e5 p8 p5
    e6 p8 p6
    e7 p10 p7
    e8 p10 p9
    e9 p11 p1
    e10 p11 p9
    e11 p12 p7
    e12 p13 p8
    e13 p14 p13
    e14 p15 p11
    e15 p16 p12
    e16 p17 p14
    e17 p18 p15
    e18 p19 p16
    e19 p20 p18
    e20 p20 p16
    e21 p21 p17
    e22 p21 p19
    e23 p22 p18
    e24 p24 p22
    e25 p24 p23
    e26 p25 p21
    e27 p26 p25
    e28 p27 p26
    e29 p28 p24
    e30 p29 p26
    e31 p30 p28

    // Insert AssEdges
    p3 e1
    p4 e2
    p5 e3
    p7 e4
    p8 e5
    p8 e6
    p10 e7
    p10 e8
    p11 e9
    p11 e10
    p12 e11
    p13 e12
    p14 e13
    p15 e14
    p16 e15
    p17 e16
    p18 e17
    p19 e18
    p20 e19
    p20 e20
    p21 e21
    p21 e22
    p22 e23 
    p24 e24 
    p24 e25
    p25 e26 
    p26 e27 
    p27 e28 
    p28 e29 
    p29 e30
    p30 e31 
  )";

  adjLists = parseAdjList(adjListS);


  EXPECT_TRUE(compareGraphs(adjLists));
}



TEST_F(RNGTest, calcRNG_same_angle_case_2) {

  std::ifstream in("data/Beispiele/RNG_Beispiel_3/RNG_gleiche_Winkel.txt");
  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;
  std::set<Point> inputPoints(begin, end);

  init(inputPoints, 0);
  calculateRNG();

  // Manuelle Überprüfung, ob die Adjazenzlisten korrekt erstellt wurden
  std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> adjLists;

  auto adjListS = R"(
    // AssPoints
    p1 (119, 81) (119, 81)
    p2 (116, 32) (116, 32)
    p3 (113, 34) (113, 34)
    p4 (107, 51) (107, 51) 
    p5 (106, 46) (106, 46)
    p6 (105, 5) (105, 5)
    p7 (104, 95) (104, 95) 
    p8 (103, 45) (103, 45)
    p9 (101, 65) (101, 65)
    p10 (97, 69) (97, 69)
    p11 (95, 42) (95, 42)
    p12 (93, 77) (93, 77)
    p13 (90, 59) (90, 59)
    p14 (81, 115) (81, 115)
    p15 (74, 100) (74, 100)
    p16 (74, 31) (74, 31)
    p17 (71, 93) (71, 93) 
    p18 (56, 19) (56, 19)
    p19 (54, 6) (54, 6)
    p20 (38, 50) (38, 50)
    p21 (32, 50) (32, 50)
    p22 (30, 35) (30, 35)
    p23 (26, 45) (26, 45)
    p24 (25, 107) (25, 107)
    p25 (15, 54) (15, 54)
    p26 (14, 118) (14, 118)
    p27 (13, 93) (13, 93)
    p28 (11, 11) (11, 11)
    p29 (5, 113) (5, 113)
    p30 (4, 119) (4, 119) 

    // AssEdges
    e1 p3 p2
    e2 p5 p3
    e3 p5 p4
    e4 p6 p2
    e5 p7 p1
    e6 p8 p5
    e7 p9 p1
    e8 p9 p4
    e9 p10 p9
    e10 p11 p8
    e11 p12 p7
    e12 p12 p10
    e13 p13 p10
    e14 p13 p11
    e15 p15 p14
    e16 p16 p11
    e17 p17 p12 
    e18 p17 p15
    e19 p18 p15
    e20 p19 p18
    e21 p21 p20
    e22 p22 p18
    e23 p23 p21
    e24 p23 p22
    e25 p24 p17
    e26 p25 p23
    e27 p26 p24
    e28 p27 p24
    e29 p27 p25
    e30 p28 p22
    e31 p30 p26
    e32 p30 p29

    // Insert AssEdges
    p3 e1
    p5 e2
    p5 e3
    p6 e4
    p7 e5
    p8 e6
    p9 e7
    p9 e8
    p10 e9
    p11 e10
    p12 e11
    p12 e12
    p13 e13
    p13 e14
    p15 e15
    p16 e16
    p17 e17
    p17 e18
    p18 e19
    p19 e20
    p21 e21
    p22 e22
    p23 e23 
    p23 e24 
    p24 e25
    p25 e26 
    p26 e27 
    p27 e28 
    p27 e29 
    p28 e30
    p30 e31
    p30 e32 
  )";

  adjLists = parseAdjList(adjListS);


  EXPECT_TRUE(!compareGraphs(adjLists));

} 