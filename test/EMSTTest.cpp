#include "EMSTTest.hpp"


TEST_F(EMSTTest, Beispiel_2_EMST){

  std::ifstream in("data/Beispiele/EMST_Beispiel_2/EMST_Beispiel_2.txt");
  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;
  std::vector<Point> inputPoints(begin, end);


  // Erwarteter Ausgabevektor zur Berechnung des EMSTs, sortiert nach Kantenlänge
  std::vector<Edge> expectedEMST{};
  expectedEMST.reserve(29);

  expectedEMST.push_back(Edge{Point{112, 64}, Point{116, 65}});
  expectedEMST.push_back(Edge{Point{60, 24}, Point{63, 21}});
  expectedEMST.push_back(Edge{Point{107, 0}, Point{111, 4}});
  expectedEMST.push_back(Edge{Point{23, 28}, Point{28, 25}});
  expectedEMST.push_back(Edge{Point{18, 5}, Point{22, 10}});
  expectedEMST.push_back(Edge{Point{75, 105}, Point{82, 111}});
  expectedEMST.push_back(Edge{Point{63, 21}, Point{66, 12}});
  expectedEMST.push_back(Edge{Point{14, 71}, Point{20, 62}});
  expectedEMST.push_back(Edge{Point{12, 90}, Point{22, 95}});
  expectedEMST.push_back(Edge{Point{72, 34}, Point{76, 23}});
  expectedEMST.push_back(Edge{Point{111, 24}, Point{119, 33}});
  expectedEMST.push_back(Edge{Point{63, 21}, Point{76, 23}});
  expectedEMST.push_back(Edge{Point{95, 90}, Point{107, 99}});
  expectedEMST.push_back(Edge{Point{22, 10}, Point{28, 25}});
  expectedEMST.push_back(Edge{Point{3, 58}, Point{14, 71}});
  expectedEMST.push_back(Edge{Point{12, 90}, Point{14, 71}});
  expectedEMST.push_back(Edge{Point{98, 50}, Point{112, 64}});
  expectedEMST.push_back(Edge{Point{111, 4}, Point{111, 24}});
  expectedEMST.push_back(Edge{Point{91, 70}, Point{95, 90}});
  expectedEMST.push_back(Edge{Point{72, 34}, Point{77, 54}});
  expectedEMST.push_back(Edge{Point{91, 70}, Point{98, 50}});
  expectedEMST.push_back(Edge{Point{77, 54}, Point{91, 70}});
  expectedEMST.push_back(Edge{Point{32, 116}, Point{54, 117}});
  expectedEMST.push_back(Edge{Point{22, 95}, Point{32, 116}});
  expectedEMST.push_back(Edge{Point{54, 117}, Point{75, 105}});
  expectedEMST.push_back(Edge{Point{82, 111}, Point{95, 90}});
  expectedEMST.push_back(Edge{Point{98, 50}, Point{119, 33}});
  expectedEMST.push_back(Edge{Point{56, 72}, Point{77, 54}});
  expectedEMST.push_back(Edge{Point{28, 25}, Point{60, 24}});


  // Erwarteter Ausgabevektor zur Berechnung des RNGs, sortiert nach Kantenlänge
  std::vector<Edge> expectedRNG{};
  expectedRNG.reserve(33);

  expectedRNG.push_back(Edge{Point{112, 64}, Point{116, 65}});
  expectedRNG.push_back(Edge{Point{60, 24}, Point{63, 21}});
  expectedRNG.push_back(Edge{Point{107, 0}, Point{111, 4}});
  expectedRNG.push_back(Edge{Point{23, 28}, Point{28, 25}});
  expectedRNG.push_back(Edge{Point{18, 5}, Point{22, 10}});
  expectedRNG.push_back(Edge{Point{75, 105}, Point{82, 111}});
  expectedRNG.push_back(Edge{Point{63, 21}, Point{66, 12}});
  expectedRNG.push_back(Edge{Point{14, 71}, Point{20, 62}});
  expectedRNG.push_back(Edge{Point{12, 90}, Point{22, 95}});
  expectedRNG.push_back(Edge{Point{72, 34}, Point{76, 23}});
  expectedRNG.push_back(Edge{Point{111, 24}, Point{119, 33}});
  expectedRNG.push_back(Edge{Point{63, 21}, Point{76, 23}});
  expectedRNG.push_back(Edge{Point{95, 90}, Point{107, 99}});
  expectedRNG.push_back(Edge{Point{60, 24}, Point{72, 34}});
  expectedRNG.push_back(Edge{Point{22, 10}, Point{28, 25}});
  expectedRNG.push_back(Edge{Point{3, 58}, Point{14, 71}});
  expectedRNG.push_back(Edge{Point{12, 90}, Point{14, 71}});
  expectedRNG.push_back(Edge{Point{98, 50}, Point{112, 64}});
  expectedRNG.push_back(Edge{Point{111, 4}, Point{111, 24}});
  expectedRNG.push_back(Edge{Point{91, 70}, Point{95, 90}});
  expectedRNG.push_back(Edge{Point{72, 34}, Point{77, 54}});
  expectedRNG.push_back(Edge{Point{91, 70}, Point{98, 50}});
  expectedRNG.push_back(Edge{Point{77, 54}, Point{91, 70}});
  expectedRNG.push_back(Edge{Point{32, 116}, Point{54, 117}});
  expectedRNG.push_back(Edge{Point{22, 95}, Point{32, 116}});
  expectedRNG.push_back(Edge{Point{54, 117}, Point{75, 105}});
  expectedRNG.push_back(Edge{Point{82, 111}, Point{95, 90}});
  expectedRNG.push_back(Edge{Point{98, 50}, Point{119, 33}});
  expectedRNG.push_back(Edge{Point{56, 72}, Point{77, 54}});
  expectedRNG.push_back(Edge{Point{28, 25}, Point{60, 24}});
  expectedRNG.push_back(Edge{Point{20, 62}, Point{23, 28}});
  expectedRNG.push_back(Edge{Point{20, 62}, Point{56, 72}});
  expectedRNG.push_back(Edge{Point{56, 72}, Point{75, 105}}); 


  std::vector<Edge> expectedSNet_1{};
  expectedSNet_1.push_back(Edge{Point{23, 28}, Point{20, 62}});


  std::vector<Edge> expectedSNet_10{};
  expectedSNet_10.reserve(15);

  expectedSNet_10.push_back(Edge{Point{3, 58}, Point{14, 71}});
  expectedSNet_10.push_back(Edge{Point{28, 25}, Point{23, 28}});
  expectedSNet_10.push_back(Edge{Point{12, 90}, Point{14, 71}});
  expectedSNet_10.push_back(Edge{Point{75, 105}, Point{54, 117}});
  expectedSNet_10.push_back(Edge{Point{20, 62}, Point{23, 28}});
  expectedSNet_10.push_back(Edge{Point{56, 72}, Point{77, 54}});
  expectedSNet_10.push_back(Edge{Point{60, 24}, Point{63, 21}});
  expectedSNet_10.push_back(Edge{Point{54, 117}, Point{75, 105}});
  expectedSNet_10.push_back(Edge{Point{107, 99}, Point{95, 90}});
  expectedSNet_10.push_back(Edge{Point{112, 64}, Point{116, 65}});
  expectedSNet_10.push_back(Edge{Point{119, 33}, Point{111, 24}});
  expectedSNet_10.push_back(Edge{Point{111, 4}, Point{111, 24}});
  expectedSNet_10.push_back(Edge{Point{91, 70}, Point{77, 54}});
  expectedSNet_10.push_back(Edge{Point{63, 21}, Point{66, 12}});
  expectedSNet_10.push_back(Edge{Point{28, 25}, Point{22, 10}});


  std::vector<Edge> expectedSNet_30{};
  expectedSNet_30.reserve(32);

  expectedSNet_30.push_back(Edge{Point{3, 58}, Point{14, 71}});
  expectedSNet_30.push_back(Edge{Point{22, 95}, Point{32, 116}});
  expectedSNet_30.push_back(Edge{Point{54, 117}, Point{75, 105}});
  expectedSNet_30.push_back(Edge{Point{82, 111}, Point{95, 90}});
  expectedSNet_30.push_back(Edge{Point{107, 99}, Point{95, 90}});
  expectedSNet_30.push_back(Edge{Point{91, 70}, Point{98, 50}});
  expectedSNet_30.push_back(Edge{Point{112, 64}, Point{116, 65}});
  expectedSNet_30.push_back(Edge{Point{112, 64}, Point{98, 50}});
  expectedSNet_30.push_back(Edge{Point{119, 33}, Point{111, 24}});
  expectedSNet_30.push_back(Edge{Point{111, 4}, Point{107, 0}});
  expectedSNet_30.push_back(Edge{Point{111, 4}, Point{111, 24}});
  expectedSNet_30.push_back(Edge{Point{119, 33}, Point{98, 50}});
  expectedSNet_30.push_back(Edge{Point{91, 70}, Point{77, 54}});
  expectedSNet_30.push_back(Edge{Point{72, 34}, Point{76, 23}});
  expectedSNet_30.push_back(Edge{Point{63, 21}, Point{66, 12}});
  expectedSNet_30.push_back(Edge{Point{63, 21}, Point{60, 24}});
  expectedSNet_30.push_back(Edge{Point{28, 25}, Point{22, 10}});
  expectedSNet_30.push_back(Edge{Point{18, 5}, Point{22, 10}});
  expectedSNet_30.push_back(Edge{Point{28, 25}, Point{23, 28}});
  expectedSNet_30.push_back(Edge{Point{20, 62}, Point{14, 71}});
  expectedSNet_30.push_back(Edge{Point{12, 90}, Point{14, 71}});
  expectedSNet_30.push_back(Edge{Point{20, 62}, Point{56, 72}});
  expectedSNet_30.push_back(Edge{Point{75, 105}, Point{54, 117}});
  expectedSNet_30.push_back(Edge{Point{32, 116}, Point{22, 95}});
  expectedSNet_30.push_back(Edge{Point{20, 62}, Point{23, 28}});
  expectedSNet_30.push_back(Edge{Point{60, 24}, Point{72, 34}});
  expectedSNet_30.push_back(Edge{Point{77, 54}, Point{56, 72}});
  expectedSNet_30.push_back(Edge{Point{56, 72}, Point{77, 54}});
  expectedSNet_30.push_back(Edge{Point{91, 70}, Point{95, 90}});
  expectedSNet_30.push_back(Edge{Point{82, 111}, Point{75, 105}});
  expectedSNet_30.push_back(Edge{Point{60, 24}, Point{63, 21}});
  expectedSNet_30.push_back(Edge{Point{76, 23}, Point{72, 34}});


  // Hilfsgraph G für O(1) 
  Graph expectedG_1{};
  expectedG_1.setOfAdjLists.insert(AdjList(Point{20, 62}));
  auto it = expectedG_1.setOfAdjLists.find(AdjList(Point{20, 62}));
  it->e.insert(Edge{Point{20, 62}, Point{23, 28}, 40});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{23, 28}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{23, 28}));
  it->e.insert(Edge{Point{23, 28}, Point{20, 62}, 1});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{54, 117}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{54, 117}));
  it->e.insert(Edge{Point{54, 117}, Point{56, 72}, 6});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{56, 72}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{56, 72}));
  it->e.insert(Edge{Point{56, 72}, Point{77, 54}, 1});
  it->e.insert(Edge{Point{56, 72}, Point{75, 105}, 1});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{75, 105}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{75, 105}));
  it->e.insert(Edge{Point{75, 105}, Point{54, 117}, 1});
  it->e.insert(Edge{Point{75, 105}, Point{56, 72}, 1});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{77, 54}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{77, 54}));
  it->e.insert(Edge{Point{77, 54}, Point{75, 105}, 4});



  // Hilfsgraph G für O(10) Kanten
  Graph expectedG_10{};

  expectedG_10.setOfAdjLists.insert(AdjList(Point{3, 58}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{3, 58}));
  it->e.insert(Edge{Point{3, 58}, Point{14, 71}, 1});
  
  expectedG_10.setOfAdjLists.insert(AdjList(Point{12, 90}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{12, 90}));
  it->e.insert(Edge{Point{12, 90}, Point{14, 71}, 1});
  
  expectedG_10.setOfAdjLists.insert(AdjList(Point{14, 71}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{14, 71}));
  it->e.insert(Edge{Point{14, 71}, Point{20, 62}, 1});
  it->e.insert(Edge{Point{14, 71}, Point{3, 58}, 1});
  it->e.insert(Edge{Point{14, 71}, Point{32, 116}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{20, 62}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{20, 62}));
  it->e.insert(Edge{Point{20, 62}, Point{14, 71}, 1});
  it->e.insert(Edge{Point{20, 62}, Point{23, 28}, 1});
  it->e.insert(Edge{Point{20, 62}, Point{56, 72}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{22, 10}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{22, 10}));
  it->e.insert(Edge{Point{22, 10}, Point{28, 25}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{23, 28}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{23, 28}));
  it->e.insert(Edge{Point{23, 28}, Point{28, 25}, 1});
  it->e.insert(Edge{Point{23, 28}, Point{20, 62}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{28, 25}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{28, 25}));
  it->e.insert(Edge{Point{28, 25}, Point{23, 28}, 1});
  it->e.insert(Edge{Point{28, 25}, Point{22, 10}, 3});
  it->e.insert(Edge{Point{28, 25}, Point{60, 24}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{32, 116}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{32, 116}));
  it->e.insert(Edge{Point{32, 116}, Point{54, 117}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{54, 117}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{54, 117}));
  it->e.insert(Edge{Point{54, 117}, Point{95, 90}, 3});
  it->e.insert(Edge{Point{54, 117}, Point{12, 90}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{56, 72}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{56, 72}));
  it->e.insert(Edge{Point{56, 72}, Point{77, 54}, 1});
  it->e.insert(Edge{Point{56, 72}, Point{20, 62}, 1});
  it->e.insert(Edge{Point{56, 72}, Point{75, 105}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{60, 24}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{60, 24}));
  it->e.insert(Edge{Point{60, 24}, Point{63, 21}, 1});
  it->e.insert(Edge{Point{60, 24}, Point{72, 34}, 1});
  it->e.insert(Edge{Point{60, 24}, Point{28, 25}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{63, 21}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{63, 21}));
  it->e.insert(Edge{Point{63, 21}, Point{60, 24}, 3});
  // Hier tritt Kante doppelt auf!
  it->e.insert(Edge{Point{63, 21}, Point{60, 24}, 3, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{72, 34}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{72, 34}));
  it->e.insert(Edge{Point{72, 34}, Point{56, 72}, 2});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{75, 105}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{75, 105}));
  it->e.insert(Edge{Point{75, 105}, Point{54, 117}, 1});
  it->e.insert(Edge{Point{75, 105}, Point{56, 72}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{76, 23}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{76, 23}));
  it->e.insert(Edge{Point{76, 23}, Point{63, 21}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{77, 54}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{77, 54}));
  it->e.insert(Edge{Point{77, 54}, Point{91, 70}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{91, 70}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{91, 70}));
  it->e.insert(Edge{Point{91, 70}, Point{75, 105}, 3});
  it->e.insert(Edge{Point{91, 70}, Point{76, 23}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{95, 90}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{95, 90}));
  it->e.insert(Edge{Point{95, 90}, Point{107, 99}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{98, 50}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{98, 50}));
  it->e.insert(Edge{Point{98, 50}, Point{112, 64}, 1});
  it->e.insert(Edge{Point{98, 50}, Point{91, 70}, 1});
  it->e.insert(Edge{Point{98, 50}, Point{119, 33}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{107, 0}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{107, 0}));
  it->e.insert(Edge{Point{107, 0}, Point{111, 4}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{107, 99}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{107, 99}));
  it->e.insert(Edge{Point{107, 99}, Point{98, 50}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{111, 4}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{111, 4}));
  it->e.insert(Edge{Point{111, 4}, Point{98, 50}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{112, 64}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{112, 64}));
  it->e.insert(Edge{Point{112, 64}, Point{98, 50}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{119, 33}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{119, 33}));
  it->e.insert(Edge{Point{119, 33}, Point{107, 0}, 3});



  // Hilfsgraph G für O(30) Kanten
  Graph expectedG_30{};
  
  expectedG_30.setOfAdjLists.insert(AdjList(Point{3, 58}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{3, 58}));
  it->e.insert(Edge{Point{3, 58}, Point{14, 71}, 1});
  
  expectedG_30.setOfAdjLists.insert(AdjList(Point{12, 90}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{12, 90}));
  it->e.insert(Edge{Point{12, 90}, Point{14, 71}, 1});
  it->e.insert(Edge{Point{12, 90}, Point{22, 95}, 1});
  
  expectedG_30.setOfAdjLists.insert(AdjList(Point{14, 71}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{14, 71}));
  it->e.insert(Edge{Point{14, 71}, Point{20, 62}, 1});
  it->e.insert(Edge{Point{14, 71}, Point{3, 58}, 1});
  it->e.insert(Edge{Point{14, 71}, Point{12, 90}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{18, 5}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{18, 5}));
  it->e.insert(Edge{Point{18, 5}, Point{22, 10}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{20, 62}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{20, 62}));
  it->e.insert(Edge{Point{20, 62}, Point{14, 71}, 1});
  it->e.insert(Edge{Point{20, 62}, Point{23, 28}, 1});
  it->e.insert(Edge{Point{20, 62}, Point{56, 72}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{22, 10}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{22, 10}));
  it->e.insert(Edge{Point{22, 10}, Point{28, 25}, 1});
  it->e.insert(Edge{Point{22, 10}, Point{18, 5}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{22, 95}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{22, 95}));
  it->e.insert(Edge{Point{22, 95}, Point{12, 90}, 1});
  it->e.insert(Edge{Point{22, 95}, Point{32, 116}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{23, 28}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{23, 28}));
  it->e.insert(Edge{Point{23, 28}, Point{28, 25}, 1});
  it->e.insert(Edge{Point{23, 28}, Point{20, 62}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{28, 25}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{28, 25}));
  it->e.insert(Edge{Point{28, 25}, Point{23, 28}, 1});
  it->e.insert(Edge{Point{28, 25}, Point{22, 10}, 1});
  it->e.insert(Edge{Point{28, 25}, Point{60, 24}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{32, 116}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{32, 116}));
  it->e.insert(Edge{Point{32, 116}, Point{54, 117}, 1});
  it->e.insert(Edge{Point{32, 116}, Point{22, 95}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{54, 117}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{54, 117}));
  it->e.insert(Edge{Point{54, 117}, Point{32, 116}, 1});
  it->e.insert(Edge{Point{54, 117}, Point{75, 105}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{56, 72}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{56, 72}));
  it->e.insert(Edge{Point{56, 72}, Point{77, 54}, 1});
  it->e.insert(Edge{Point{56, 72}, Point{20, 62}, 1});
  it->e.insert(Edge{Point{56, 72}, Point{75, 105}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{60, 24}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{60, 24}));
  it->e.insert(Edge{Point{60, 24}, Point{63, 21}, 1});
  it->e.insert(Edge{Point{60, 24}, Point{72, 34}, 1});
  it->e.insert(Edge{Point{60, 24}, Point{28, 25}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{63, 21}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{63, 21}));
  it->e.insert(Edge{Point{63, 21}, Point{60, 24}, 1});
  it->e.insert(Edge{Point{63, 21}, Point{66, 12}, 1});
  it->e.insert(Edge{Point{63, 21}, Point{76, 23}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{66, 12}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{66, 12}));
  it->e.insert(Edge{Point{66, 12}, Point{63, 21}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{72, 34}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{72, 34}));
  it->e.insert(Edge{Point{72, 34}, Point{76, 23}, 1});
  it->e.insert(Edge{Point{72, 34}, Point{60, 24}, 1});
  it->e.insert(Edge{Point{72, 34}, Point{77, 54}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{75, 105}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{75, 105}));
  it->e.insert(Edge{Point{75, 105}, Point{54, 117}, 1});
  it->e.insert(Edge{Point{75, 105}, Point{56, 72}, 1});
  it->e.insert(Edge{Point{75, 105}, Point{82, 111}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{76, 23}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{76, 23}));
  it->e.insert(Edge{Point{76, 23}, Point{63, 21}, 1});
  it->e.insert(Edge{Point{76, 23}, Point{72, 34}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{77, 54}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{77, 54}));
  it->e.insert(Edge{Point{77, 54}, Point{91, 70}, 1});
  it->e.insert(Edge{Point{77, 54}, Point{72, 34}, 1});
  it->e.insert(Edge{Point{77, 54}, Point{56, 72}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{82, 111}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{82, 111}));
  it->e.insert(Edge{Point{82, 111}, Point{75, 105}, 1});
  it->e.insert(Edge{Point{82, 111}, Point{95, 90}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{91, 70}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{91, 70}));
  it->e.insert(Edge{Point{91, 70}, Point{95, 90}, 1});
  it->e.insert(Edge{Point{91, 70}, Point{98, 50}, 1});
  it->e.insert(Edge{Point{91, 70}, Point{77, 54}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{95, 90}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{95, 90}));
  it->e.insert(Edge{Point{95, 90}, Point{107, 99}, 1});
  it->e.insert(Edge{Point{95, 90}, Point{91, 70}, 1});
  it->e.insert(Edge{Point{95, 90}, Point{82, 111}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{98, 50}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{98, 50}));
  it->e.insert(Edge{Point{98, 50}, Point{112, 64}, 1});
  it->e.insert(Edge{Point{98, 50}, Point{91, 70}, 1});
  it->e.insert(Edge{Point{98, 50}, Point{119, 33}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{107, 0}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{107, 0}));
  it->e.insert(Edge{Point{107, 0}, Point{111, 4}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{107, 99}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{107, 99}));
  it->e.insert(Edge{Point{107, 99}, Point{95, 90}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{111, 4}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{111, 4}));
  it->e.insert(Edge{Point{111, 4}, Point{107, 0}, 1});
  it->e.insert(Edge{Point{111, 4}, Point{111, 24}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{111, 24}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{111, 24}));
  it->e.insert(Edge{Point{111, 24}, Point{119, 33}, 1});
  it->e.insert(Edge{Point{111, 24}, Point{111, 4}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{112, 64}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{112, 64}));
  it->e.insert(Edge{Point{112, 64}, Point{116, 65}, 1});
  it->e.insert(Edge{Point{112, 64}, Point{98, 50}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{116, 65}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{116, 65}));
  it->e.insert(Edge{Point{116, 65}, Point{112, 64}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{119, 33}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{119, 33}));
  it->e.insert(Edge{Point{119, 33}, Point{111, 24}, 1});
  it->e.insert(Edge{Point{119, 33}, Point{98, 50}, 1});



  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_1{};
  std::vector<Edge> temp{};
  temp.push_back(Edge{Point{20, 62}, Point{23, 28}, 40});
  temp.push_back(Edge{Point{23, 28}, Point{20, 62}, 1});
  expectedFaceCyclesOfG_1.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{54, 117}, Point{56, 72}, 6});
  temp.push_back(Edge{Point{56, 72}, Point{75, 105}, 1});
  temp.push_back(Edge{Point{75, 105}, Point{54, 117}, 1});
  expectedFaceCyclesOfG_1.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{56, 72}, Point{77, 54}, 1});
  temp.push_back(Edge{Point{77, 54}, Point{75, 105}, 4});
  temp.push_back(Edge{Point{75, 105}, Point{56, 72}, 1});
  expectedFaceCyclesOfG_1.push_back(temp);
  temp.resize(0);


  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_10{};
  temp.push_back(Edge{Point{3, 58}, Point{14, 71}, 1});
  temp.push_back(Edge{Point{14, 71}, Point{32, 116}, 3});
  temp.push_back(Edge{Point{32, 116}, Point{54, 117}, 1});
  temp.push_back(Edge{Point{54, 117}, Point{95, 90}, 3});
  temp.push_back(Edge{Point{95, 90}, Point{107, 99}, 1});
  temp.push_back(Edge{Point{107, 99}, Point{98, 50}, 3});
  temp.push_back(Edge{Point{98, 50}, Point{112, 64}, 1});
  temp.push_back(Edge{Point{112, 64}, Point{98, 50}, 3});
  temp.push_back(Edge{Point{98, 50}, Point{119, 33}, 1});
  temp.push_back(Edge{Point{119, 33}, Point{107, 0}, 3});
  temp.push_back(Edge{Point{107, 0}, Point{111, 4}, 1});
  temp.push_back(Edge{Point{111, 4}, Point{98, 50}, 3});
  temp.push_back(Edge{Point{98, 50}, Point{91, 70}, 1});
  temp.push_back(Edge{Point{91, 70}, Point{76, 23}, 3});
  temp.push_back(Edge{Point{76, 23}, Point{63, 21}, 1});
  temp.push_back(Edge{Point{63, 21}, Point{60, 24}, 3, 1});
  temp.push_back(Edge{Point{60, 24}, Point{28, 25}, 1});
  temp.push_back(Edge{Point{28, 25}, Point{22, 10}, 3});
  temp.push_back(Edge{Point{22, 10}, Point{28, 25}, 1});
  temp.push_back(Edge{Point{28, 25}, Point{23, 28}, 1});
  temp.push_back(Edge{Point{23, 28}, Point{20, 62}, 1});
  temp.push_back(Edge{Point{20, 62}, Point{14, 71}, 1});
  temp.push_back(Edge{Point{14, 71}, Point{3, 58}, 1});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{12, 90}, Point{14, 71}, 1});
  temp.push_back(Edge{Point{14, 71}, Point{20, 62}, 1});
  temp.push_back(Edge{Point{20, 62}, Point{56, 72}, 1});
  temp.push_back(Edge{Point{56, 72}, Point{75, 105}, 1});
  temp.push_back(Edge{Point{75, 105}, Point{54, 117}, 1});
  temp.push_back(Edge{Point{54, 117}, Point{12, 90}, 3});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{20, 62}, Point{23, 28}, 1});
  temp.push_back(Edge{Point{23, 28}, Point{28, 25}, 1});
  temp.push_back(Edge{Point{28, 25}, Point{60, 24}, 1});
  temp.push_back(Edge{Point{60, 24}, Point{72, 34}, 1});
  temp.push_back(Edge{Point{72, 34}, Point{56, 72}, 2});
  temp.push_back(Edge{Point{56, 72}, Point{20, 62}, 1});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{56, 72}, Point{77, 54}, 1});
  temp.push_back(Edge{Point{77, 54}, Point{91, 70}, 1});
  temp.push_back(Edge{Point{91, 70}, Point{75, 105}, 3});
  temp.push_back(Edge{Point{75, 105}, Point{56, 72}, 1});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{60, 24}, Point{63, 21}, 1});
  temp.push_back(Edge{Point{63, 21}, Point{60, 24}, 3});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);


  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_30{};
  temp.push_back(Edge{Point{3, 58}, Point{14, 71}, 1});
  temp.push_back(Edge{Point{14, 71}, Point{12, 90}, 1});
  temp.push_back(Edge{Point{12, 90}, Point{22, 95}, 1});
  temp.push_back(Edge{Point{22, 95}, Point{32, 116}, 1});
  temp.push_back(Edge{Point{32, 116}, Point{54, 117}, 1});
  temp.push_back(Edge{Point{54, 117}, Point{75, 105}, 1});
  temp.push_back(Edge{Point{75, 105}, Point{82, 111}, 1});
  temp.push_back(Edge{Point{82, 111}, Point{95, 90}, 1});
  temp.push_back(Edge{Point{95, 90}, Point{107, 99}, 1});
  temp.push_back(Edge{Point{107, 99}, Point{95, 90}, 1});
  temp.push_back(Edge{Point{95, 90}, Point{91, 70}, 1});
  temp.push_back(Edge{Point{91, 70}, Point{98, 50}, 1});
  temp.push_back(Edge{Point{98, 50}, Point{112, 64}, 1});
  temp.push_back(Edge{Point{112, 64}, Point{116, 65}, 1});
  temp.push_back(Edge{Point{116, 65}, Point{112, 64}, 1});
  temp.push_back(Edge{Point{112, 64}, Point{98, 50}, 1});
  temp.push_back(Edge{Point{98, 50}, Point{119, 33}, 1});
  temp.push_back(Edge{Point{119, 33}, Point{111, 24}, 1});
  temp.push_back(Edge{Point{111, 24}, Point{111, 4}, 1});
  temp.push_back(Edge{Point{111, 4}, Point{107, 0}, 1});
  temp.push_back(Edge{Point{107, 0}, Point{111, 4}, 1});
  temp.push_back(Edge{Point{111, 4}, Point{111, 24}, 1});
  temp.push_back(Edge{Point{111, 24}, Point{119, 33}, 1});
  temp.push_back(Edge{Point{119, 33}, Point{98, 50}, 1});
  temp.push_back(Edge{Point{98, 50}, Point{91, 70}, 1});
  temp.push_back(Edge{Point{91, 70}, Point{77, 54}, 1});
  temp.push_back(Edge{Point{77, 54}, Point{72, 34}, 1});
  temp.push_back(Edge{Point{72, 34}, Point{76, 23}, 1});
  temp.push_back(Edge{Point{76, 23}, Point{63, 21}, 1});
  temp.push_back(Edge{Point{63, 21}, Point{66, 12}, 1});
  temp.push_back(Edge{Point{66, 12}, Point{63, 21}, 1});
  temp.push_back(Edge{Point{63, 21}, Point{60, 24}, 1});
  temp.push_back(Edge{Point{60, 24}, Point{28, 25}, 1});
  temp.push_back(Edge{Point{28, 25}, Point{22, 10}, 1});
  temp.push_back(Edge{Point{22, 10}, Point{18, 5}, 1});
  temp.push_back(Edge{Point{18, 5}, Point{22, 10}, 1});
  temp.push_back(Edge{Point{22, 10}, Point{28, 25}, 1});
  temp.push_back(Edge{Point{28, 25}, Point{23, 28}, 1});
  temp.push_back(Edge{Point{23, 28}, Point{20, 62}, 1});
  temp.push_back(Edge{Point{20, 62}, Point{14, 71}, 1});
  temp.push_back(Edge{Point{14, 71}, Point{3, 58}, 1});
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{12, 90}, Point{14, 71}, 1});
  temp.push_back(Edge{Point{14, 71}, Point{20, 62}, 1});
  temp.push_back(Edge{Point{20, 62}, Point{56, 72}, 1});
  temp.push_back(Edge{Point{56, 72}, Point{75, 105}, 1});
  temp.push_back(Edge{Point{75, 105}, Point{54, 117}, 1});
  temp.push_back(Edge{Point{54, 117}, Point{32, 116}, 1});
  temp.push_back(Edge{Point{32, 116}, Point{22, 95}, 1});
  temp.push_back(Edge{Point{22, 95}, Point{12, 90}, 1});

  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{20, 62}, Point{23, 28}, 1});
  temp.push_back(Edge{Point{23, 28}, Point{28, 25}, 1});
  temp.push_back(Edge{Point{28, 25}, Point{60, 24}, 1});
  temp.push_back(Edge{Point{60, 24}, Point{72, 34}, 1});
  temp.push_back(Edge{Point{72, 34}, Point{77, 54}, 1});
  temp.push_back(Edge{Point{77, 54}, Point{56, 72}, 1});
  temp.push_back(Edge{Point{56, 72}, Point{20, 62}, 1});
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{56, 72}, Point{77, 54}, 1});
  temp.push_back(Edge{Point{77, 54}, Point{91, 70}, 1});
  temp.push_back(Edge{Point{91, 70}, Point{95, 90}, 1});
  temp.push_back(Edge{Point{95, 90}, Point{82, 111}, 1});
  temp.push_back(Edge{Point{82, 111}, Point{75, 105}, 1});

  temp.push_back(Edge{Point{75, 105}, Point{56, 72}, 1});
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{60, 24}, Point{63, 21}, 1});
  temp.push_back(Edge{Point{63, 21}, Point{76, 23}, 1});
  temp.push_back(Edge{Point{76, 23}, Point{72, 34}, 1});
  temp.push_back(Edge{Point{72, 34}, Point{60, 24}, 1});

  expectedFaceCyclesOfG_30.push_back(temp);



  /*
  Teste die Berechnung für s=30, also für O(n) Speicher
  */
 // Es muss einmal init aufgerufen worden sein, da benutzerdefinierter Destruktor mit Speicherplatzfreigabe
  init(inputPoints, 30);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  std::vector<Edge> calculatedEMST_30 = parseEdgeFile("data/Beispiele/EMST_Beispiel_2/O(30)/Euklidischer_Minimaler_Spannbaum.txt");
  // std::vector<Edge> calculatedEMST_30 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_30);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  std::vector<Edge> calculatedRNG_30 = parseEdgeFile("data/Beispiele/EMST_Beispiel_2/O(30)/Relativer_Nachbarschaftsgraph.txt");
  // std::vector<Edge> calculatedRNG_30 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_30);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  std::vector<Edge> calculatedSNet_30 = parseSNetBlock("data/Beispiele/EMST_Beispiel_2/O(30)/s-Netz.txt");
  // std::vector<Edge> calculatedSNet_30 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_30, calculatedSNet_30);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Kanten enthält
  Graph calculatedG_30 = parseGBlock("data/Beispiele/EMST_Beispiel_2/O(30)/Hilfsgraph_G.txt");
  // Graph calculatedG_30 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_30, calculatedG_30);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben

  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_30 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_2/O(30)/face_cycles_G.txt");
  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_30 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_30, calculatedFaceCyclesOfG_30);



  /*
  Teste die Berechnung für s=10, um den Sonderfall zu zeigen (also für ~O(log n) Speicher) 
  */
  // init(inputPoints, 10);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  std::vector<Edge> calculatedEMST_10 = parseEdgeFile("data/Beispiele/EMST_Beispiel_2/O(10)/Euklidischer_Minimaler_Spannbaum.txt");
  // std::vector<Edge> calculatedEMST_10 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_10);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  std::vector<Edge> calculatedRNG_10 = parseEdgeFile("data/Beispiele/EMST_Beispiel_2/O(10)/Relativer_Nachbarschaftsgraph.txt");
  // std::vector<Edge> calculatedRNG_10 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_10);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  std::vector<Edge> calculatedSNet_10 = parseSNetBlock("data/Beispiele/EMST_Beispiel_2/O(10)/s-Netz.txt");
  // std::vector<Edge> calculatedSNet_10 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_10, calculatedSNet_10);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Kanten enthält
  Graph calculatedG_10 = parseGBlock("data/Beispiele/EMST_Beispiel_2/O(10)/Hilfsgraph_G.txt");
  // Graph calculatedG_10 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_10, calculatedG_10);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben
  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_10 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_2/O(10)/face_cycles_G.txt");
  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_10 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_10, calculatedFaceCyclesOfG_10);



  /*
  Teste die Berechnung für s=1, also für O(1) Speicher 
  */
  // init(inputPoints, 1);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  std::vector<Edge> calculatedEMST_1 = parseEdgeFile("data/Beispiele/EMST_Beispiel_2/O(1)/Euklidischer_Minimaler_Spannbaum.txt");
  // std::vector<Edge> calculatedEMST_1 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_1);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  std::vector<Edge> calculatedRNG_1 = parseEdgeFile("data/Beispiele/EMST_Beispiel_2/O(1)/Relativer_Nachbarschaftsgraph.txt");
  // std::vector<Edge> calculatedRNG_1 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_1);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  std::vector<Edge> calculatedSNet_1 = parseSNetBlock("data/Beispiele/EMST_Beispiel_2/O(1)/s-Netz.txt");
  // std::vector<Edge> calculatedSNet_1 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_1, calculatedSNet_1);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Punkte und Kanten enthält
  Graph calculatedG_1 = parseGBlock("data/Beispiele/EMST_Beispiel_2/O(1)/Hilfsgraph_G.txt");
  // Graph calculatedG_1 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_1, calculatedG_1);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben
  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_1 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_2/O(1)/face_cycles_G.txt");
  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_1 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_1, calculatedFaceCyclesOfG_1);

}




TEST_F(EMSTTest, Beispiel_3_EMST){

  std::ifstream in("data/Beispiele/EMST_Beispiel_3/EMST_Beispiel_3.txt");
  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;
  std::vector<Point> inputPoints(begin, end);


  // Erwarteter Ausgabevektor zur Berechnung des EMSTs, sortiert nach Kantenlänge
  std::vector<Edge> expectedEMST{};
  expectedEMST.reserve(29);

  expectedEMST.push_back(Edge{Point{81, 23}, Point{82, 22}});
  expectedEMST.push_back(Edge{Point{90, 117}, Point{91, 113}});
  expectedEMST.push_back(Edge{Point{109, 17}, Point{115, 16}});
  expectedEMST.push_back(Edge{Point{109, 17}, Point{110, 10}});
  expectedEMST.push_back(Edge{Point{82, 22}, Point{83, 14}});
  expectedEMST.push_back(Edge{Point{110, 10}, Point{113, 2}});
  expectedEMST.push_back(Edge{Point{74, 13}, Point{83, 14}});
  expectedEMST.push_back(Edge{Point{24, 20}, Point{33, 23}});
  expectedEMST.push_back(Edge{Point{70, 69}, Point{72, 82}});
  expectedEMST.push_back(Edge{Point{33, 23}, Point{46, 20}});
  expectedEMST.push_back(Edge{Point{0, 80}, Point{8, 69}});
  expectedEMST.push_back(Edge{Point{65, 55}, Point{70, 69}});
  expectedEMST.push_back(Edge{Point{34, 63}, Point{43, 75}});
  expectedEMST.push_back(Edge{Point{118, 97}, Point{119, 113}});
  expectedEMST.push_back(Edge{Point{8, 69}, Point{11, 53}});
  expectedEMST.push_back(Edge{Point{72, 82}, Point{89, 80}});
  expectedEMST.push_back(Edge{Point{11, 53}, Point{28, 43}});
  expectedEMST.push_back(Edge{Point{19, 90}, Point{38, 96}});
  expectedEMST.push_back(Edge{Point{28, 43}, Point{33, 23}});
  expectedEMST.push_back(Edge{Point{28, 43}, Point{34, 63}});
  expectedEMST.push_back(Edge{Point{0, 80}, Point{19, 90}});
  expectedEMST.push_back(Edge{Point{2, 28}, Point{24, 20}});
  expectedEMST.push_back(Edge{Point{10, 1}, Point{24, 20}});
  expectedEMST.push_back(Edge{Point{38, 96}, Point{46, 119}});
  expectedEMST.push_back(Edge{Point{83, 14}, Point{109, 17}});
  expectedEMST.push_back(Edge{Point{43, 75}, Point{70, 69}});
  expectedEMST.push_back(Edge{Point{91, 113}, Point{119, 113}});
  expectedEMST.push_back(Edge{Point{46, 20}, Point{74, 13}});
  expectedEMST.push_back(Edge{Point{89, 80}, Point{91, 113}});
  

  // Erwarteter Ausgabevektor zur Berechnung des RNGs, sortiert nach Kantenlänge
  std::vector<Edge> expectedRNG{};
  expectedRNG.reserve(33);

  expectedRNG.push_back(Edge{Point{81, 23}, Point{82, 22}});
  expectedRNG.push_back(Edge{Point{90, 117}, Point{91, 113}});
  expectedRNG.push_back(Edge{Point{109, 17}, Point{115, 16}});
  expectedRNG.push_back(Edge{Point{109, 17}, Point{110, 10}});
  expectedRNG.push_back(Edge{Point{82, 22}, Point{83, 14}});
  expectedRNG.push_back(Edge{Point{110, 10}, Point{113, 2}});
  expectedRNG.push_back(Edge{Point{74, 13}, Point{83, 14}});
  expectedRNG.push_back(Edge{Point{24, 20}, Point{33, 23}});
  expectedRNG.push_back(Edge{Point{70, 69}, Point{72, 82}});
  expectedRNG.push_back(Edge{Point{33, 23}, Point{46, 20}});
  expectedRNG.push_back(Edge{Point{0, 80}, Point{8, 69}});
  expectedRNG.push_back(Edge{Point{65, 55}, Point{70, 69}});
  expectedRNG.push_back(Edge{Point{34, 63}, Point{43, 75}});
  expectedRNG.push_back(Edge{Point{118, 97}, Point{119, 113}});
  expectedRNG.push_back(Edge{Point{8, 69}, Point{11, 53}});
  expectedRNG.push_back(Edge{Point{72, 82}, Point{89, 80}});
  expectedRNG.push_back(Edge{Point{11, 53}, Point{28, 43}});
  expectedRNG.push_back(Edge{Point{19, 90}, Point{38, 96}});
  expectedRNG.push_back(Edge{Point{28, 43}, Point{33, 23}});
  expectedRNG.push_back(Edge{Point{28, 43}, Point{34, 63}});
  expectedRNG.push_back(Edge{Point{0, 80}, Point{19, 90}});
  expectedRNG.push_back(Edge{Point{38, 96}, Point{43, 75}});
  expectedRNG.push_back(Edge{Point{2, 28}, Point{24, 20}});
  expectedRNG.push_back(Edge{Point{10, 1}, Point{24, 20}});
  expectedRNG.push_back(Edge{Point{38, 96}, Point{46, 119}});
  expectedRNG.push_back(Edge{Point{83, 14}, Point{109, 17}});
  expectedRNG.push_back(Edge{Point{2, 28}, Point{11, 53}});
  expectedRNG.push_back(Edge{Point{43, 75}, Point{70, 69}});
  expectedRNG.push_back(Edge{Point{91, 113}, Point{119, 113}});
  expectedRNG.push_back(Edge{Point{46, 20}, Point{74, 13}});
  expectedRNG.push_back(Edge{Point{89, 80}, Point{91, 113}});
  expectedRNG.push_back(Edge{Point{65, 55}, Point{81, 23}});
  expectedRNG.push_back(Edge{Point{46, 119}, Point{90, 117}});


  // S-Netz für O(1)
  std::vector<Edge> expectedSNet_1{};
  expectedSNet_1.reserve(1);
  expectedSNet_1.push_back(Edge{Point{46, 119}, Point{90, 117}});

  // S-Netz für O(6)
  std::vector<Edge> expectedSNet_6{};
  expectedSNet_6.reserve(8);
  expectedSNet_6.push_back(Edge{Point{0, 80}, Point{8, 69}});
  expectedSNet_6.push_back(Edge{Point{0, 80}, Point{19, 90}});
  expectedSNet_6.push_back(Edge{Point{81, 23}, Point{82, 22}});
  expectedSNet_6.push_back(Edge{Point{113, 2}, Point{110, 10}});
  expectedSNet_6.push_back(Edge{Point{24, 20}, Point{10, 1}});
  expectedSNet_6.push_back(Edge{Point{81, 23}, Point{65, 55}});
  expectedSNet_6.push_back(Edge{Point{72, 82}, Point{89, 80}});
  expectedSNet_6.push_back(Edge{Point{118, 97}, Point{119, 113}});


    // S-Netz für O(10)
  std::vector<Edge> expectedSNet_10{};
  expectedSNet_10.reserve(14);
  expectedSNet_10.push_back(Edge{Point{0, 80}, Point{8, 69}});
  expectedSNet_10.push_back(Edge{Point{34, 63}, Point{43, 75}});
  expectedSNet_10.push_back(Edge{Point{0, 80}, Point{19, 90}});
  expectedSNet_10.push_back(Edge{Point{89, 80}, Point{72, 82}});
  expectedSNet_10.push_back(Edge{Point{81, 23}, Point{82, 22}});
  expectedSNet_10.push_back(Edge{Point{115, 16}, Point{109, 17}});
  expectedSNet_10.push_back(Edge{Point{110, 10}, Point{109, 17}});
  expectedSNet_10.push_back(Edge{Point{46, 20}, Point{33, 23}});
  expectedSNet_10.push_back(Edge{Point{24, 20}, Point{2, 28}});
  expectedSNet_10.push_back(Edge{Point{2, 28}, Point{24, 20}});
  expectedSNet_10.push_back(Edge{Point{46, 20}, Point{74, 13}});
  expectedSNet_10.push_back(Edge{Point{70, 69}, Point{43, 75}});
  expectedSNet_10.push_back(Edge{Point{38, 96}, Point{43, 75}});
  expectedSNet_10.push_back(Edge{Point{89, 80}, Point{91, 113}}); 
  expectedSNet_10.push_back(Edge{Point{91, 113}, Point{119, 113}});

  // S-Netz für O(30)
  std::vector<Edge> expectedSNet_30{};
  expectedSNet_30.reserve(31);
  expectedSNet_30.push_back(Edge{Point{0, 80}, Point{8, 69}});
  expectedSNet_30.push_back(Edge{Point{11, 53}, Point{28, 43}});
  expectedSNet_30.push_back(Edge{Point{34, 63}, Point{43, 75}});
  expectedSNet_30.push_back(Edge{Point{38, 96}, Point{19, 90}});
  expectedSNet_30.push_back(Edge{Point{0, 80}, Point{19, 90}});
  expectedSNet_30.push_back(Edge{Point{90, 117}, Point{91, 113}});
  expectedSNet_30.push_back(Edge{Point{119, 113}, Point{118, 97}});
  expectedSNet_30.push_back(Edge{Point{119, 113}, Point{91, 113}});
  expectedSNet_30.push_back(Edge{Point{89, 80}, Point{72, 82}});
  expectedSNet_30.push_back(Edge{Point{70, 69}, Point{65, 55}});
  expectedSNet_30.push_back(Edge{Point{81, 23}, Point{82, 22}});
  expectedSNet_30.push_back(Edge{Point{83, 14}, Point{109, 17}});
  expectedSNet_30.push_back(Edge{Point{115, 16}, Point{109, 17}});
  expectedSNet_30.push_back(Edge{Point{110, 10}, Point{113, 2}});
  expectedSNet_30.push_back(Edge{Point{110, 10}, Point{109, 17}});
  expectedSNet_30.push_back(Edge{Point{83, 14}, Point{74, 13}});
  expectedSNet_30.push_back(Edge{Point{46, 20}, Point{33, 23}});
  expectedSNet_30.push_back(Edge{Point{24, 20}, Point{10, 1}});
  expectedSNet_30.push_back(Edge{Point{24, 20}, Point{2, 28}});
  expectedSNet_30.push_back(Edge{Point{11, 53}, Point{8, 69}});
  expectedSNet_30.push_back(Edge{Point{2, 28}, Point{24, 20}});
  expectedSNet_30.push_back(Edge{Point{28, 43}, Point{11, 53}});
  expectedSNet_30.push_back(Edge{Point{28, 43}, Point{33, 23}});
  expectedSNet_30.push_back(Edge{Point{74, 13}, Point{83, 14}});
  expectedSNet_30.push_back(Edge{Point{82, 22}, Point{81, 23}});
  expectedSNet_30.push_back(Edge{Point{65, 55}, Point{70, 69}});
  expectedSNet_30.push_back(Edge{Point{43, 75}, Point{34, 63}});
  expectedSNet_30.push_back(Edge{Point{38, 96}, Point{43, 75}});
  expectedSNet_30.push_back(Edge{Point{70, 69}, Point{72, 82}});
  expectedSNet_30.push_back(Edge{Point{89, 80}, Point{91, 113}});
  expectedSNet_30.push_back(Edge{Point{90, 117}, Point{46, 119}});
  expectedSNet_30.push_back(Edge{Point{38, 96}, Point{46, 119}});


  // Hilfsgrapph für O(1)
  Graph expectedG_1{};
  expectedG_1.setOfAdjLists.insert(AdjList(Point{38, 96}));
  auto it = expectedG_1.setOfAdjLists.find(AdjList(Point{38, 96}));
  it->e.insert(Edge{Point{38, 96}, Point{90, 117}, 6});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{46, 119}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{46, 119}));
  it->e.insert(Edge{Point{46, 119}, Point{38, 96}, 1});
  it->e.insert(Edge{Point{46, 119}, Point{90, 117}, 1});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{65, 55}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{65, 55}));
  it->e.insert(Edge{Point{65, 55}, Point{81, 23}, 1});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{81, 23}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{81, 23}));
  it->e.insert(Edge{Point{81, 23}, Point{46, 119}, 23});

  expectedG_1.setOfAdjLists.insert(AdjList(Point{90, 117}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{90, 117}));
  it->e.insert(Edge{Point{90, 117}, Point{91, 113}, 1});
  it->e.insert(Edge{Point{90, 117}, Point{46, 119}, 1}); 

    expectedG_1.setOfAdjLists.insert(AdjList(Point{91, 113}));
  it = expectedG_1.setOfAdjLists.find(AdjList(Point{91, 113}));
  it->e.insert(Edge{Point{91, 113}, Point{65, 55}, 8}); 


  // Hilfsgrapph für O(6)
  Graph expectedG_6{};

  expectedG_6.setOfAdjLists.insert(AdjList(Point{0, 80}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{0, 80}));
  it->e.insert(Edge{Point{0, 80}, Point{8, 69}, 1});
  it->e.insert(Edge{Point{0, 80}, Point{19, 90}, 1}); 

  expectedG_6.setOfAdjLists.insert(AdjList(Point{8, 69}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{8, 69}));
  it->e.insert(Edge{Point{8, 69}, Point{0, 80}, 7});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{10, 1}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{10, 1}));
  it->e.insert(Edge{Point{10, 1}, Point{0, 80}, 5});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{19, 90}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{19, 90}));
  it->e.insert(Edge{Point{19, 90}, Point{46, 119}, 2});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{24, 20}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{24, 20}));
  it->e.insert(Edge{Point{24, 20}, Point{10, 1}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{28, 43}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{28, 43}));
  it->e.insert(Edge{Point{28, 43}, Point{81, 23}, 6});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{34, 63}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{34, 63}));
  it->e.insert(Edge{Point{34, 63}, Point{28, 43}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{38, 96}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{38, 96}));
  it->e.insert(Edge{Point{38, 96}, Point{72, 82}, 3});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{46, 119}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{46, 119}));
  it->e.insert(Edge{Point{46, 119}, Point{38, 96}, 1});
  it->e.insert(Edge{Point{46, 119}, Point{90, 117}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{65, 55}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{65, 55}));
  it->e.insert(Edge{Point{65, 55}, Point{70, 69}, 1});
  it->e.insert(Edge{Point{65, 55}, Point{81, 23}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{70, 69}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{70, 69}));
  it->e.insert(Edge{Point{70, 69}, Point{34, 63}, 2});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{72, 82}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{72, 82}));
  it->e.insert(Edge{Point{72, 82}, Point{89, 80}, 1});
  it->e.insert(Edge{Point{72, 82}, Point{65, 55}, 2});  

  expectedG_6.setOfAdjLists.insert(AdjList(Point{81, 23}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{81, 23}));
  it->e.insert(Edge{Point{81, 23}, Point{82, 22}, 1});
  it->e.insert(Edge{Point{81, 23}, Point{65, 55}, 1}); 

  expectedG_6.setOfAdjLists.insert(AdjList(Point{82, 22}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{82, 22}));
  it->e.insert(Edge{Point{82, 22}, Point{113, 2}, 6});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{89, 80}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{89, 80}));
  it->e.insert(Edge{Point{89, 80}, Point{72, 82}, 1});
  it->e.insert(Edge{Point{89, 80}, Point{91, 113}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{90, 117}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{90, 117}));
  it->e.insert(Edge{Point{90, 117}, Point{91, 113}, 1});
  it->e.insert(Edge{Point{90, 117}, Point{46, 119}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{91, 113}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{91, 113}));
  it->e.insert(Edge{Point{91, 113}, Point{91, 113}, 4});
  it->e.insert(Edge{Point{91, 113}, Point{90, 117}, 1});
  it->e.insert(Edge{Point{91, 113}, Point{89, 80}, 1});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{110, 10}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{110, 10}));
  it->e.insert(Edge{Point{110, 10}, Point{24, 20}, 6});

  expectedG_6.setOfAdjLists.insert(AdjList(Point{113, 2}));
  it = expectedG_6.setOfAdjLists.find(AdjList(Point{113, 2}));
  it->e.insert(Edge{Point{113, 2}, Point{110, 10}, 1});


  // Hilfsgrapph für O(10)
  Graph expectedG_10{};

  expectedG_10.setOfAdjLists.insert(AdjList(Point{0, 80}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{0, 80}));
  it->e.insert(Edge{Point{0, 80}, Point{8, 69}, 1});
  it->e.insert(Edge{Point{0, 80}, Point{19, 90}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{2, 28}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{2, 28}));
  it->e.insert(Edge{Point{2, 28}, Point{24, 20}, 1});
  it->e.insert(Edge{Point{2, 28}, Point{0, 80}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{8, 69}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{8, 69}));
  it->e.insert(Edge{Point{8, 69}, Point{34, 63}, 3});
 
  expectedG_10.setOfAdjLists.insert(AdjList(Point{19, 90}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{19, 90}));
  it->e.insert(Edge{Point{19, 90}, Point{46, 119}, 2});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{24, 20}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{24, 20}));
  it->e.insert(Edge{Point{24, 20}, Point{2, 28}, 1});
  it->e.insert(Edge{Point{24, 20}, Point{2, 28}, 4});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{33, 23}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{33, 23}));
  it->e.insert(Edge{Point{33, 23}, Point{24, 20}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{34, 63}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{34, 63}));
  it->e.insert(Edge{Point{34, 63}, Point{43, 75}, 1});
  it->e.insert(Edge{Point{34, 63}, Point{46, 20}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{38, 96}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{38, 96}));
  it->e.insert(Edge{Point{38, 96}, Point{43, 75}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{43, 75}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{43, 75}));
  it->e.insert(Edge{Point{43, 75}, Point{34, 63}, 1});
  it->e.insert(Edge{Point{43, 75}, Point{70, 69}, 1});
  it->e.insert(Edge{Point{43, 75}, Point{0, 80}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{46, 20}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{46, 20}));
  it->e.insert(Edge{Point{46, 20}, Point{33, 23}, 1});
  it->e.insert(Edge{Point{46, 20}, Point{74, 13}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{46, 119}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{46, 119}));
  it->e.insert(Edge{Point{46, 119}, Point{38, 96}, 1});
  it->e.insert(Edge{Point{46, 119}, Point{90, 117}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{65, 55}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{65, 55}));
  it->e.insert(Edge{Point{65, 55}, Point{70, 69}, 1});
  it->e.insert(Edge{Point{65, 55}, Point{81, 23}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{70, 69}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{70, 69}));
  it->e.insert(Edge{Point{70, 69}, Point{65, 55}, 1});
  it->e.insert(Edge{Point{70, 69}, Point{89, 80}, 2});
  it->e.insert(Edge{Point{70, 69}, Point{43, 75}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{72, 82}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{72, 82}));
  it->e.insert(Edge{Point{72, 82}, Point{70, 69}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{74, 13}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{74, 13}));
  it->e.insert(Edge{Point{74, 13}, Point{81, 23}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{81, 23}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{81, 23}));
  it->e.insert(Edge{Point{81, 23}, Point{82, 22}, 1});
  it->e.insert(Edge{Point{81, 23}, Point{65, 55}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{82, 22}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{82, 22}));
  it->e.insert(Edge{Point{82, 22}, Point{115, 16}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{89, 80}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{89, 80}));
  it->e.insert(Edge{Point{89, 80}, Point{72, 82}, 1});
  it->e.insert(Edge{Point{89, 80}, Point{91, 113}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{90, 117}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{90, 117}));
  it->e.insert(Edge{Point{90, 117}, Point{91, 113}, 1});
  it->e.insert(Edge{Point{90, 117}, Point{46, 119}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{91, 113}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{91, 113}));
  it->e.insert(Edge{Point{91, 113}, Point{91, 113}, 4});
  it->e.insert(Edge{Point{91, 113}, Point{90, 117}, 1});
  it->e.insert(Edge{Point{91, 113}, Point{89, 80}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{109, 17}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{109, 17}));
  it->e.insert(Edge{Point{109, 17}, Point{110, 10}, 3});
  it->e.insert(Edge{Point{109, 17}, Point{46, 20}, 3});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{110, 10}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{110, 10}));
  it->e.insert(Edge{Point{110, 10}, Point{109, 17}, 1});

  expectedG_10.setOfAdjLists.insert(AdjList(Point{115, 16}));
  it = expectedG_10.setOfAdjLists.find(AdjList(Point{115, 16}));
  it->e.insert(Edge{Point{115, 16}, Point{109, 17}, 1});



  // Hilfsgrapph für O(30)
  Graph expectedG_30{};

  expectedG_30.setOfAdjLists.insert(AdjList(Point{0, 80}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{0, 80}));
  it->e.insert(Edge{Point{0, 80}, Point{8, 69}, 1});
  it->e.insert(Edge{Point{0, 80}, Point{19, 90}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{2, 28}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{2, 28}));
  it->e.insert(Edge{Point{2, 28}, Point{24, 20}, 1});
  it->e.insert(Edge{Point{2, 28}, Point{11, 53}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{8, 69}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{8, 69}));
  it->e.insert(Edge{Point{8, 69}, Point{0, 80}, 1});
  it->e.insert(Edge{Point{8, 69}, Point{11, 53}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{10, 1}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{10, 1}));
  it->e.insert(Edge{Point{10, 1}, Point{24, 20}, 1}); 

  expectedG_30.setOfAdjLists.insert(AdjList(Point{11, 53}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{11, 53}));
  it->e.insert(Edge{Point{11, 53}, Point{8, 69}, 1});
  it->e.insert(Edge{Point{11, 53}, Point{28, 43}, 1});
  it->e.insert(Edge{Point{11, 53}, Point{2, 28}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{19, 90}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{19, 90}));
  it->e.insert(Edge{Point{19, 90}, Point{0, 80}, 1});
  it->e.insert(Edge{Point{19, 90}, Point{46, 119}, 2});  

  expectedG_30.setOfAdjLists.insert(AdjList(Point{24, 20}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{24, 20}));
  it->e.insert(Edge{Point{24, 20}, Point{28, 43}, 2});
  it->e.insert(Edge{Point{24, 20}, Point{2, 28}, 1});
  it->e.insert(Edge{Point{24, 20}, Point{10, 1}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{28, 43}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{28, 43}));
  it->e.insert(Edge{Point{28, 43}, Point{11, 53}, 1});
  it->e.insert(Edge{Point{28, 43}, Point{33, 23}, 1});
  it->e.insert(Edge{Point{28, 43}, Point{34, 63}, 1}); 

  expectedG_30.setOfAdjLists.insert(AdjList(Point{33, 23}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{33, 23}));
  it->e.insert(Edge{Point{33, 23}, Point{24, 20}, 1});
  it->e.insert(Edge{Point{33, 23}, Point{46, 20}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{34, 63}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{34, 63}));
  it->e.insert(Edge{Point{34, 63}, Point{43, 75}, 1});
  it->e.insert(Edge{Point{34, 63}, Point{28, 43}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{38, 96}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{38, 96}));
  it->e.insert(Edge{Point{38, 96}, Point{19, 90}, 1});
  it->e.insert(Edge{Point{38, 96}, Point{43, 75}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{43, 75}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{43, 75}));
  it->e.insert(Edge{Point{43, 75}, Point{34, 63}, 1});
  it->e.insert(Edge{Point{43, 75}, Point{38, 96}, 1});
  it->e.insert(Edge{Point{43, 75}, Point{70, 69}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{46, 20}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{46, 20}));
  it->e.insert(Edge{Point{46, 20}, Point{33, 23}, 1});
  it->e.insert(Edge{Point{46, 20}, Point{74, 13}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{46, 119}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{46, 119}));
  it->e.insert(Edge{Point{46, 119}, Point{38, 96}, 1});
  it->e.insert(Edge{Point{46, 119}, Point{90, 117}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{65, 55}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{65, 55}));
  it->e.insert(Edge{Point{65, 55}, Point{70, 69}, 1});
  it->e.insert(Edge{Point{65, 55}, Point{81, 23}, 1});  

  expectedG_30.setOfAdjLists.insert(AdjList(Point{70, 69}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{70, 69}));
  it->e.insert(Edge{Point{70, 69}, Point{72, 82}, 1});
  it->e.insert(Edge{Point{70, 69}, Point{65, 55}, 1});
  it->e.insert(Edge{Point{70, 69}, Point{43, 75}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{72, 82}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{72, 82}));
  it->e.insert(Edge{Point{72, 82}, Point{70, 69}, 1});
  it->e.insert(Edge{Point{72, 82}, Point{89, 80}, 1}); 

  expectedG_30.setOfAdjLists.insert(AdjList(Point{74, 13}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{74, 13}));
  it->e.insert(Edge{Point{74, 13}, Point{83, 14}, 1});
  it->e.insert(Edge{Point{74, 13}, Point{46, 20}, 1}); 

  expectedG_30.setOfAdjLists.insert(AdjList(Point{81, 23}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{81, 23}));
  it->e.insert(Edge{Point{81, 23}, Point{82, 22}, 1});
  it->e.insert(Edge{Point{81, 23}, Point{65, 55}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{82, 22}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{82, 22}));
  it->e.insert(Edge{Point{82, 22}, Point{81, 23}, 1});
  it->e.insert(Edge{Point{82, 22}, Point{83, 14}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{83, 14}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{83, 14}));
  it->e.insert(Edge{Point{83, 14}, Point{82, 22}, 1});
  it->e.insert(Edge{Point{83, 14}, Point{74, 13}, 1});
  it->e.insert(Edge{Point{83, 14}, Point{109, 17}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{89, 80}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{89, 80}));
  it->e.insert(Edge{Point{89, 80}, Point{72, 82}, 1});
  it->e.insert(Edge{Point{89, 80}, Point{91, 113}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{90, 117}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{90, 117}));
  it->e.insert(Edge{Point{90, 117}, Point{91, 113}, 1});
  it->e.insert(Edge{Point{90, 117}, Point{46, 119}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{91, 113}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{91, 113}));
  it->e.insert(Edge{Point{91, 113}, Point{90, 117}, 1});
  it->e.insert(Edge{Point{91, 113}, Point{119, 113}, 1});
  it->e.insert(Edge{Point{91, 113}, Point{89, 80}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{109, 17}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{109, 17}));
  it->e.insert(Edge{Point{109, 17}, Point{115, 16}, 1});
  it->e.insert(Edge{Point{109, 17}, Point{110, 10}, 1});
  it->e.insert(Edge{Point{109, 17}, Point{83, 14}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{110, 10}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{110, 10}));
  it->e.insert(Edge{Point{110, 10}, Point{109, 17}, 1});
  it->e.insert(Edge{Point{110, 10}, Point{113, 2}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{113, 2}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{113, 2}));
  it->e.insert(Edge{Point{113, 2}, Point{110, 10}});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{115, 16}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{115, 16}));
  it->e.insert(Edge{Point{115, 16}, Point{109, 17}});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{118, 97}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{118, 97}));
  it->e.insert(Edge{Point{118, 97}, Point{119, 113}, 1});

  expectedG_30.setOfAdjLists.insert(AdjList(Point{119, 113}));
  it = expectedG_30.setOfAdjLists.find(AdjList(Point{119, 113}));
  it->e.insert(Edge{Point{119, 113}, Point{118, 97}, 1});
  it->e.insert(Edge{Point{119, 113}, Point{91, 113}, 1});


  // Face-Cycles des Hilfsgraphs für O(1)
  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_1{};
  std::vector<Edge> temp{};

  temp.push_back(Edge{Point{38, 96}, Point{90, 117}, 6});
  temp.push_back(Edge{Point{90, 117}, Point{46, 119}, 1});
  temp.push_back(Edge{Point{46, 119}, Point{38, 96}, 1});
  expectedFaceCyclesOfG_1.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{46, 119}, Point{90, 117}, 1});
  temp.push_back(Edge{Point{90, 117}, Point{91, 113}, 1});
  temp.push_back(Edge{Point{91, 113}, Point{65, 55}, 8});
  temp.push_back(Edge{Point{65, 55}, Point{81, 23}, 1});
  temp.push_back(Edge{Point{81, 23}, Point{46, 119}, 23});
  expectedFaceCyclesOfG_1.push_back(temp);
  temp.resize(0);


  // Face-Cycles des Hilfsgraphs für O(6)
  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_6{};

  temp.push_back(Edge{Point{0, 80}, Point{8, 69}, 1});
  temp.push_back(Edge{Point{8, 69}, Point{0, 80}, 7}); 
  expectedFaceCyclesOfG_6.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{0, 80}, Point{19, 90}, 1});
  temp.push_back(Edge{Point{19, 90}, Point{46, 119}, 2});
  temp.push_back(Edge{Point{46, 119}, Point{90, 117}, 1});
  temp.push_back(Edge{Point{90, 117}, Point{91, 113}, 1});
  temp.push_back(Edge{Point{91, 113}, Point{91, 113}, 4});
  temp.push_back(Edge{Point{91, 113}, Point{89, 80}, 1});
  temp.push_back(Edge{Point{89, 80}, Point{72, 82}, 1});
  temp.push_back(Edge{Point{72, 82}, Point{65, 55}, 2});
  temp.push_back(Edge{Point{65, 55}, Point{81, 23}, 1});
  temp.push_back(Edge{Point{81, 23}, Point{82, 22}, 1});
  temp.push_back(Edge{Point{82, 22}, Point{113, 2}, 6});
  temp.push_back(Edge{Point{113, 2}, Point{110, 10}, 1});
  temp.push_back(Edge{Point{110, 10}, Point{24, 20}, 6}); 
  temp.push_back(Edge{Point{24, 20}, Point{10, 1}, 1});
  temp.push_back(Edge{Point{10, 1}, Point{0, 80}, 5}); 
  expectedFaceCyclesOfG_6.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{28, 43}, Point{81, 23}, 6});
  temp.push_back(Edge{Point{81, 23}, Point{65, 55}, 1});
  temp.push_back(Edge{Point{65, 55}, Point{70, 69}, 1});
  temp.push_back(Edge{Point{70, 69}, Point{34, 63}, 2});
  temp.push_back(Edge{Point{34, 63}, Point{28, 43}, 1}); 
  expectedFaceCyclesOfG_6.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{38, 96}, Point{72, 82}, 3});
  temp.push_back(Edge{Point{72, 82}, Point{89, 80}, 1});
  temp.push_back(Edge{Point{89, 80}, Point{91, 113}, 1});
  temp.push_back(Edge{Point{91, 113}, Point{90, 117}, 1});
  temp.push_back(Edge{Point{90, 117}, Point{46, 119}, 1}); 
  temp.push_back(Edge{Point{46, 119}, Point{38, 96}, 1}); 
  expectedFaceCyclesOfG_6.push_back(temp);
  temp.resize(0);


  // Face-Cycles des Hilfsgraphs für O(10)
  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_10{};

  temp.push_back(Edge{Point{0, 80}, Point{8, 69}, 1});
  temp.push_back(Edge{Point{8, 69}, Point{34, 63}, 3});
  temp.push_back(Edge{Point{34, 63}, Point{43, 75}, 1});
  temp.push_back(Edge{Point{43, 75}, Point{0, 80}, 3}); 
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{0, 80}, Point{19, 90}, 1});
  temp.push_back(Edge{Point{19, 90}, Point{46, 119}, 2});
  temp.push_back(Edge{Point{46, 119}, Point{90, 117}, 1});
  temp.push_back(Edge{Point{90, 117}, Point{91, 113}, 1});
  temp.push_back(Edge{Point{91, 113}, Point{91, 113}, 4}); 
  temp.push_back(Edge{Point{91, 113}, Point{89, 80}, 1}); 

  temp.push_back(Edge{Point{89, 80}, Point{72, 82}, 1});
  temp.push_back(Edge{Point{72, 82}, Point{70, 69}, 1});
  temp.push_back(Edge{Point{70, 69}, Point{65, 55}, 1});
  temp.push_back(Edge{Point{65, 55}, Point{81, 23}, 1});
  temp.push_back(Edge{Point{81, 23}, Point{82, 22}, 1}); 
  temp.push_back(Edge{Point{82, 22}, Point{115, 16}, 3}); 

  temp.push_back(Edge{Point{115, 16}, Point{109, 17}, 1});
  temp.push_back(Edge{Point{109, 17}, Point{110, 10}, 3});
  temp.push_back(Edge{Point{110, 10}, Point{109, 17}, 1});
  temp.push_back(Edge{Point{109, 17}, Point{46, 20}, 3});
  temp.push_back(Edge{Point{46, 20}, Point{33, 23}, 1}); 
  temp.push_back(Edge{Point{33, 23}, Point{24, 20}, 3}); 
  temp.push_back(Edge{Point{24, 20}, Point{2, 28}, 1});
  temp.push_back(Edge{Point{2, 28}, Point{0, 80}, 3});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{2, 28}, Point{24, 20}, 1});
  temp.push_back(Edge{Point{24, 20}, Point{2, 28}, 4});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{34, 63}, Point{46, 20}, 3});
  temp.push_back(Edge{Point{46, 20}, Point{74, 13}, 1});
  temp.push_back(Edge{Point{74, 13}, Point{81, 23}, 3});
  temp.push_back(Edge{Point{81, 23}, Point{65, 55}, 1});
  temp.push_back(Edge{Point{65, 55}, Point{70, 69}, 1}); 
  temp.push_back(Edge{Point{70, 69}, Point{43, 75}, 1}); 
  temp.push_back(Edge{Point{43, 75}, Point{34, 63}, 1});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{38, 96}, Point{43, 75}, 1});
  temp.push_back(Edge{Point{43, 75}, Point{70, 69}, 1});
  temp.push_back(Edge{Point{70, 69}, Point{89, 80}, 2});
  temp.push_back(Edge{Point{89, 80}, Point{91, 113}, 1});
  temp.push_back(Edge{Point{91, 113}, Point{90, 117}, 1}); 
  temp.push_back(Edge{Point{90, 117}, Point{46, 119}, 1}); 
  temp.push_back(Edge{Point{46, 119}, Point{38, 96}});
  expectedFaceCyclesOfG_10.push_back(temp);
  temp.resize(0);



  // Face-Cycles des Hilfsgraphs für O(30)
  std::vector<std::vector<Edge>> expectedFaceCyclesOfG_30{};
  
  temp.push_back(Edge{Point{0, 80}, Point{8, 69}, 1});
  temp.push_back(Edge{Point{8, 69}, Point{11, 53}, 1});
  temp.push_back(Edge{Point{11, 53}, Point{28, 43}, 1});
  temp.push_back(Edge{Point{28, 43}, Point{34, 63}, 1});
  temp.push_back(Edge{Point{34, 63}, Point{43, 75}, 1}); 
  temp.push_back(Edge{Point{43, 75}, Point{38, 96}, 1}); 
  temp.push_back(Edge{Point{38, 96}, Point{19, 90}, 1});
  temp.push_back(Edge{Point{19, 90}, Point{0, 80}, 1});
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{0, 80}, Point{19, 90}, 1});
  temp.push_back(Edge{Point{19, 90}, Point{46, 119}, 2});
  temp.push_back(Edge{Point{46, 119}, Point{90, 117}, 1});
  temp.push_back(Edge{Point{90, 117}, Point{91, 113}, 1});
  temp.push_back(Edge{Point{91, 113}, Point{119, 113}, 1}); 
  temp.push_back(Edge{Point{119, 113}, Point{118, 97}, 1}); 
  temp.push_back(Edge{Point{118, 97}, Point{119, 113}, 1});
  temp.push_back(Edge{Point{119, 113}, Point{91, 113}, 1});

  temp.push_back(Edge{Point{91, 113}, Point{89, 80}, 1});
  temp.push_back(Edge{Point{89, 80}, Point{72, 82}, 1});
  temp.push_back(Edge{Point{72, 82}, Point{70, 69}, 1});
  temp.push_back(Edge{Point{70, 69}, Point{65, 55}, 1});
  temp.push_back(Edge{Point{65, 55}, Point{81, 23}, 1}); 
  temp.push_back(Edge{Point{81, 23}, Point{82, 22}, 1}); 
  temp.push_back(Edge{Point{82, 22}, Point{83, 14}, 1});

  temp.push_back(Edge{Point{83, 14}, Point{109, 17}, 1});
  temp.push_back(Edge{Point{109, 17}, Point{115, 16}, 1});
  temp.push_back(Edge{Point{115, 16}, Point{109, 17}, 1});
  temp.push_back(Edge{Point{109, 17}, Point{110, 10}, 1});
  temp.push_back(Edge{Point{110, 10}, Point{113, 2}, 1}); 
  temp.push_back(Edge{Point{113, 2}, Point{110, 10}, 1}); 
  temp.push_back(Edge{Point{110, 10}, Point{109, 17}, 1});

  temp.push_back(Edge{Point{109, 17}, Point{83, 14}, 1});
  temp.push_back(Edge{Point{83, 14}, Point{74, 13}, 1});
  temp.push_back(Edge{Point{74, 13}, Point{46, 20}, 1});
  temp.push_back(Edge{Point{46, 20}, Point{33, 23}, 1});
  temp.push_back(Edge{Point{33, 23}, Point{24, 20}, 1}); 
  temp.push_back(Edge{Point{24, 20}, Point{10, 1}, 1}); 

  temp.push_back(Edge{Point{10, 1}, Point{24, 20}, 1});
  temp.push_back(Edge{Point{24, 20}, Point{2, 28}, 1});
  temp.push_back(Edge{Point{2, 28}, Point{11, 53}, 1});
  temp.push_back(Edge{Point{11, 53}, Point{8, 69}, 1}); 
  temp.push_back(Edge{Point{8, 69}, Point{0, 80}, 1}); 
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{2, 28}, Point{24, 20}, 1});
  temp.push_back(Edge{Point{24, 20}, Point{28, 43}, 2});
  temp.push_back(Edge{Point{28, 43}, Point{11, 53}, 1});
  temp.push_back(Edge{Point{11, 53}, Point{2, 28}, 1}); 
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{28, 43}, Point{33, 23}, 1});
  temp.push_back(Edge{Point{33, 23}, Point{46, 20}, 1});
  temp.push_back(Edge{Point{46, 20}, Point{74, 13}, 1});
  temp.push_back(Edge{Point{74, 13}, Point{83, 14}, 1});
  temp.push_back(Edge{Point{83, 14}, Point{82, 22}, 1}); 
  temp.push_back(Edge{Point{82, 22}, Point{81, 23}, 1});  

  temp.push_back(Edge{Point{81, 23}, Point{65, 55}, 1});
  temp.push_back(Edge{Point{65, 55}, Point{70, 69}, 1});
  temp.push_back(Edge{Point{70, 69}, Point{43, 75}, 1});
  temp.push_back(Edge{Point{43, 75}, Point{34, 63}, 1}); 
  temp.push_back(Edge{Point{34, 63}, Point{28, 43}, 1}); 
  expectedFaceCyclesOfG_30.push_back(temp);
  temp.resize(0);

  temp.push_back(Edge{Point{38, 96}, Point{43, 75}, 1});
  temp.push_back(Edge{Point{43, 75}, Point{70, 69}, 1});
  temp.push_back(Edge{Point{70, 69}, Point{72, 82}, 1});
  temp.push_back(Edge{Point{72, 82}, Point{89, 80}, 1});
  temp.push_back(Edge{Point{89, 80}, Point{91, 113}, 1}); 
  temp.push_back(Edge{Point{91, 113}, Point{90, 117}, 1}); 
  temp.push_back(Edge{Point{90, 117}, Point{46, 119}, 1});
  temp.push_back(Edge{Point{46, 119}, Point{38, 96}, 1});
  expectedFaceCyclesOfG_30.push_back(temp);




  /*
  Teste die Berechnung für s=30, also für O(n) Speicher
  */
 // Es muss einmal init aufgerufen worden sein, da benutzerdefinierter Destruktor mit Speicherplatzfreigabe
  init(inputPoints, 30);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedEMST_30 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(30)/Euklidischer_Minimaler_Spannbaum.txt");
  std::vector<Edge> calculatedEMST_30 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_30);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedRNG_30 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(30)/Relativer_Nachbarschaftsgraph.txt");
  std::vector<Edge> calculatedRNG_30 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_30);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  // std::vector<Edge> calculatedSNet_30 = parseSNetBlock("data/Beispiele/EMST_Beispiel_3/O(30)/s-Netz.txt");
  std::vector<Edge> calculatedSNet_30 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_30, calculatedSNet_30);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Kanten enthält
  // Graph calculatedG_30 = parseGBlock("data/Beispiele/EMST_Beispiel_3/O(30)/Hilfsgraph_G.txt");
  Graph calculatedG_30 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_30, calculatedG_30);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben

  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_30 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_3/O(30)/face_cycles_G.txt");
  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_30 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_30, calculatedFaceCyclesOfG_30);



  /*
  Teste die Berechnung für s=10, um den Sonderfall zu zeigen (also für O(log n) Speicher) 
  */
  init(inputPoints, 10);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedEMST_10 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(10)/Euklidischer_Minimaler_Spannbaum.txt");
  std::vector<Edge> calculatedEMST_10 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_10);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedRNG_10 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(10)/Relativer_Nachbarschaftsgraph.txt");
  std::vector<Edge> calculatedRNG_10 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_10);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  // std::vector<Edge> calculatedSNet_10 = parseSNetBlock("data/Beispiele/EMST_Beispiel_3/O(10)/s-Netz.txt");
  std::vector<Edge> calculatedSNet_10 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_10, calculatedSNet_10);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Kanten enthält
  // Graph calculatedG_10 = parseGBlock("data/Beispiele/EMST_Beispiel_3/O(10)/Hilfsgraph_G.txt");
  Graph calculatedG_10 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_10, calculatedG_10);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben

  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_10 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_3/O(10)/face_cycles_G.txt");
  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_10 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_10, calculatedFaceCyclesOfG_10);




  /*
  Teste die Berechnung für s=6, um den Sonderfall zu zeigen (also für O(log n) Speicher) 
  */
  init(inputPoints, 6);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedEMST_6 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(6)/Euklidischer_Minimaler_Spannbaum.txt");
  std::vector<Edge> calculatedEMST_6 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_6);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedRNG_6 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(6)/Relativer_Nachbarschaftsgraph.txt");
  std::vector<Edge> calculatedRNG_6 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_6);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  // std::vector<Edge> calculatedSNet_6 = parseSNetBlock("data/Beispiele/EMST_Beispiel_3/O(6)/s-Netz.txt");
  std::vector<Edge> calculatedSNet_6 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_6, calculatedSNet_6);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Kanten enthält
  // Graph calculatedG_6 = parseGBlock("data/Beispiele/EMST_Beispiel_3/O(6)/Hilfsgraph_G.txt");
  Graph calculatedG_6 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_6, calculatedG_6);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben

  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_6 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_3/O(6)/face_cycles_G.txt");
  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_6 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_6, calculatedFaceCyclesOfG_6);




  /*
  Teste die Berechnung für s=1, also für O(1) Speicher 
  */
  init(inputPoints, 1);
  
  // Prüfe, ob die Kanten des EMSTs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedEMST_1 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(1)/Euklidischer_Minimaler_Spannbaum.txt");
  std::vector<Edge> calculatedEMST_1 = parseEdgeFile("data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt");
  EXPECT_EQ(expectedEMST, calculatedEMST_1);

  // Prüfe, ob alle Kanten des RNGs korrekt und in der richtigen Reihenfolge berechnet werden
  // std::vector<Edge> calculatedRNG_1 = parseEdgeFile("data/Beispiele/EMST_Beispiel_3/O(1)/Relativer_Nachbarschaftsgraph.txt");
  std::vector<Edge> calculatedRNG_1 = parseEdgeFile("data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt");
  EXPECT_EQ(expectedRNG, calculatedRNG_1);

  // Prüfe, ob das S-Netz zum entstehenden RNG korrekt berechnet wurde
  // std::vector<Edge> calculatedSNet_1 = parseSNetBlock("data/Beispiele/EMST_Beispiel_3/O(1)/s-Netz.txt");
  std::vector<Edge> calculatedSNet_1 = parseSNetBlock("data/Aktuelle_Ergebnisse/s-Netz.txt");
  EXPECT_EQ(expectedSNet_1, calculatedSNet_1);

  // Prüfe, ob der Hilfsgraph G zum entstehenden RNG korrekt berechnet wurde

  // Prüfe, ob der Hilfsgraph G alle benötigten Punkte und Kanten enthält
  // Graph calculatedG_1 = parseGBlock("data/Beispiele/EMST_Beispiel_3/O(1)/Hilfsgraph_G.txt");
  Graph calculatedG_1 = parseGBlock("data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt");
  EXPECT_EQ(expectedG_1, calculatedG_1);

  // Prüfe, ob alle Kanten des Hilfsgraphs G den richtigen Nachfolger haben

  // std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_1 = parseFaceCyclesOfG("data/Beispiele/EMST_Beispiel_3/O(1)/face_cycles_G.txt");
  std::vector<std::vector<Edge>> calculatedFaceCyclesOfG_1 = parseFaceCyclesOfG("data/Aktuelle_Ergebnisse/face_cycles_G.txt");
  EXPECT_EQ(expectedFaceCyclesOfG_1, calculatedFaceCyclesOfG_1);


}
