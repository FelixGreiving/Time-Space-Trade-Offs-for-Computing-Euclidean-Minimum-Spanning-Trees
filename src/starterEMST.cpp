#include "PointGeneration.hpp"
#include "RNG.hpp"
#include <fstream>
#include <CGAL/draw_triangulation_2.h>



int main()
{
  // Berechnet den EMST zu Punkte in allgemeiner Lage

  generatePoints(30);
  std::ifstream in("data/Aktuelle_Ergebnisse/zufaellige_Eingabepunkte.txt");

  std::istream_iterator<Point> begin(in);
  std::istream_iterator<Point> end;

  std::vector<Point> randomPoints(begin, end);

  int s = 10;
  EMST emst{randomPoints, s};


  // Berechnet den RNG zu Punkten in allgemeiner LAge
  
  // generatePoints(30);
  // std::ifstream in("data/zufaellige_Eingabepunkte.txt");

  // std::istream_iterator<Point> begin(in);
  // std::istream_iterator<Point> end;

  // std::set<Point> randomPoints(begin, end);

  // RNG rng{randomPoints, 0};
  // rng.calculateRNG();

  return 0;
}