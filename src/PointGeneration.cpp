#include "PointGeneration.hpp"
#include <random>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include <fstream>
#include "RNG.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;



/// @brief Berechne number an Punkten in allgemeiner Lage aus [4*number]x[4*number] und schreibe diese in die Datei randomPoints.txt
/// @param number Anzahl an Punkten in allgemeiner Lage
void generatePoints(int number){

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<int> distr(0, 4 * number);

  // Speichere alle validen Punkte im Vektor points
  std::vector<K::Point_3> points{};
  int count = 0;

  for (int n = 0; n < number; n++) {
    // Wähle einen zufälligen Punkt p aus [4*number]x[4*number]
    K::Point_3 p{distr(eng), distr(eng), 1};
    bool quit = false;

    // Test, ob der zufällig gewählte Punkt bereits im Vektor points enthalten ist
    for(unsigned int i = 0; i<points.size(); i++){
      if(points[i].x() == p.x() && points[i].y() == p.y()){
        n=n-1;
        quit = true;
        break;
      }
    }
    if(quit){continue;}


    // Test, ob die Längen aller entstehenden Kanten disjunkt sind. Beginnt bei dem dritten eingefügten Punkt
    if(n>2){
      Point pNew{p.x(), p.y()};
      for(unsigned int i = 0; i<points.size(); i++){
        Point act{points[i].x(), points[i].y()};
        Edge newEdge{act, pNew};
        double actDist = newEdge.calcLength();

        for(unsigned int j=0; j<points.size()-1;j++){
          Point tail{points[j].x(), points[j].y()};
          for(unsigned int k=j+1; k<points.size();k++){
            Point head{points[k].x(), points[k].y()};
            Edge e{tail, head};
            if(actDist == e.calcLength()){
              n=n-1;
              quit=true;
              break;
            }
          }
          if(quit){break;}
        }
        if(quit){break;}
      }
    }
    if(quit){continue;}

    if(n>2){
      Point pNew{p.x(), p.y()};
      for(unsigned int i=0; i<points.size()-1; i++){
        Point act{points[i].x(), points[i].y()};
        Edge newEdge{act, pNew};
        double actDist = newEdge.calcLength();
        for(unsigned int j=i+1; j<points.size(); j++){
          Point tail{points[j].x(), points[j].y()};
          Edge e{tail, pNew};
          if(actDist == e.calcLength()){
              n=n-1;
              quit=true;
              break;
            }
        }
        if(quit){break;}
      }
    }
    if(quit){continue;}

    if(n>1){
      // Test auf Kollinearität
      for(int i = 0; i < n-1; i++){
        for(int j = i + 1; j < n; j++){
          quit = CGAL::collinear(points[i], points[j], p);
          if(quit){
            n=n-1; 
            break;}
        }
        if(quit){break;}
      }
      if(quit){continue;}
    }

    // Test auf Kozirkularität
    if(n>2){
      for(int i = 0; i < n-2; i++){
        for(int j = i+1; j < n-1; j++){
          K::Point_3 newCenter = CGAL::circumcenter(points[i], points[j], p);
          for(int k = j+1; k < n; k++){
            K::Point_3 knownCenter = CGAL::circumcenter(points[i], points[j], points[k]);
            if(newCenter.x() == knownCenter.x() && newCenter.y() == knownCenter.y()){
              quit = true;
              n=n-1;
              break;
            }
          }
          if(quit){break;}
        }
        if(quit){break;}
      }
      if(quit){continue;}
    }

    // Füge p in den Vektor ein und gebe in der Konsole den i-ten Punkt aus
    count++;
    points.push_back(p);
  }


  // Schreibe die zufälligen Punkten in eine Test-Datei, die initial alle Punkte für den RNG-Algorithmus enthält
  std::string filename("data/Aktuelle_Ergebnisse/zufaellige_Eingabepunkte.txt");
  std::fstream file_out;

  file_out.open(filename, std::ios_base::out);
  if(!file_out.is_open()){
    std::cerr << "failed to open " << filename << "\n";
  }else{
    for(unsigned int i=0; i < points.size(); i++){
      file_out << points[i].x() << " " << points[i].y() << std::endl;
    }
  }

}
