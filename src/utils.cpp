#include "utils.hpp"



/// @brief Drehe alle Eingabepunkte um den Winkel k*60° und speichere diese in dem Vektor vecPoints
/// @param inputPoint Menge an Eingabepunkten
/// @param transformer Transformationsobjekt zur Drehung der Eingabepunkte
/// @param vecPoints Referenz auf Vektor von Punkten, in den die gedrehten Punkte eingefügt werden können
void rotatePoints(std::set<K::Point_3>& inputPoints, Transformer& transformer, std::vector<K::Point_3>& vecPoints){
  
  std::transform(inputPoints.begin(), inputPoints.end(), std::inserter(vecPoints, vecPoints.begin()),
  [&transformer](const K::Point_3 &p) -> K::Point_3 {
    return transformer.rotate(p);
  }); 
}



/// @brief Gebe zurück, ob (xCoord, yCoord) in vecPoints liegt
/// @param vecPoints Vektor von assPoints, der umgekehrt lexikographisch sortiert ist und mindestens ein Element enthält
/// @param xCoord x-Koordinate des gesuchten Punktes
/// @param yCoord y-Koordinate des gesuchten Punktes
/// @return Gibt zurück, ob der Punkt (xCoord, yCoord) in vecPoints liegt
bool binarySearch(std::vector<K::Point_3> &vecPoints, double xCoord, double yCoord){

  int low = 0;
  int high = vecPoints.size()-1;

  while(low <= high){
    // Mittelwert finden
    int mid = low + (high - low)/2;

    // Zielwert gefunden 
    if(vecPoints[mid].x() == xCoord && vecPoints[mid].y() == yCoord){
        return true;
    }

    // Wert ist größer als der gesuchte Wert
    else if ((vecPoints[mid].x() == xCoord && vecPoints[mid].y() >= yCoord) || (vecPoints[mid].x() > xCoord)){
      low = mid + 1;        
    }
        
    // Wert ist kleiner als der gesuchte Wert
    else{
      high = mid - 1;
    }
  }

  // Falls das Element nicht gefunden wurde, gebe false zurück
  return false;
}



/// @brief Gebe den Index des minimalen Punktes unter allen Punkten, die größer als (xCoord, yCoord) sind, zurück.
/// Laut Voraussetzung ist (xCoord, yCoord) in vecPoints enthalten, oder kleiner als der größte Punkte in vecPoints
/// @param vecPoints Vektor von assPoints, der umgekehrt lexikographisch sortiert ist und mindestens ein Element enthält
/// @param xCoord x-Koordinate des zu vergleichenden Punktes
/// @param yCoord y-Koordinate des zu vergleichenden Punktes
/// @return Index an dessen Position der minimalen Punkts unter den größeren Punkten als (xCoord, yCoord) in vecPoints liegt  
int minBinarySearch(std::vector<K::Point_3> &vecPoints, double xCoord, double yCoord){

    int low = 1;
    int high = vecPoints.size()-1;

      while(low <= high){
        // Mittelwert finden
        int mid = low + (high - low)/2;

        // Zielwert gefunden
        if(((vecPoints[mid-1].x() == xCoord && vecPoints[mid-1].y() > yCoord) || (vecPoints[mid-1].x() > xCoord)) && 
          ((vecPoints[mid].x() == xCoord && vecPoints[mid].y() <= yCoord) || (vecPoints[mid].x() < xCoord))){
            return mid - 1;
        }

        // Wert ist kleiner als der gesuchte Wert
        else if ((vecPoints[mid-1].x() == xCoord && vecPoints[mid-1].y() <= yCoord) || (vecPoints[mid-1].x() < xCoord))
        {
          high = mid - 1;
        }
        
        // Wert ist größer als der gesuchte Wert
        else{
          low = mid + 1;
        }
      }

      // Falls das Element nicht gefunden wurde, muss es das letzte Element in vecPoints sein
      return vecPoints.size()-1;
    
}



/// @brief Gebe den Index des maximalen Punktes unter allen Punkten, die kleiner als (xCoord, yCoord) sind, zurück.
/// Laut Voraussetzung ist (xCoord, yCoord) in vecPoints enthalten oder größer als der kleinste Punkt in vecPoints
/// @param vecPoints Vektor von assPoints, der umgekehrt lexikographisch sortiert ist und mindestens ein Element enthält
/// @param xCoord x-Koordinate des zu vergleichenden Punktes
/// @param yCoord y-Koordinate des zu vergleichenden Punktes
/// @return Index an dessen Position der maximale Punkt unter den kleineren Punkten als (xCoord, yCoord) in vecPoints liegt  
int maxBinarySearch(std::vector<K::Point_3> &vecPoints, double xCoord, double yCoord){

  int low = 0;
  int high = vecPoints.size()-2;

  while(low <= high){
    // Mittelwert finden
    int mid = low + (high - low)/2;

    // Zielwert gefunden 
    if(((vecPoints[mid+1].x() == xCoord && vecPoints[mid+1].y() < yCoord) || (vecPoints[mid+1].x() < xCoord)) && 
      ((vecPoints[mid].x() == xCoord && vecPoints[mid].y() >= yCoord) || (vecPoints[mid].x() > xCoord))){
        return mid + 1;
    }

    // Wert ist größer als der gesuchte Wert
    else if ((vecPoints[mid+1].x() == xCoord && vecPoints[mid+1].y() >= yCoord) || (vecPoints[mid+1].x() > xCoord)){
      low = mid + 1;        
    }
    
    // Wert ist kleiner als der gesuchte Wert
    else{
      high = mid - 1;
    }
  }

  // Falls das Element nicht gefunden wurde, muss es das erste Element in vecPoints sein
  return 0;
}


/// @brief Berechnet für einen Vektor an Kanten den Median
/// @param vec Vektor an Kanten
/// @return Die Kante, die dem Median in vec entspricht
  Edge findMedian(std::vector<Edge> vec){
    Edge median;
    std::sort(vec.begin(), vec.end());
    int size = vec.size();
    median = vec[(size/2)];
    return median;
  }

/// @brief Berechnet für einen Vektor von Vektoren an Kanten den Median der Mediane
/// @param values Vektor der an jeder Position einen Vektor aus 5 Kanten enthält
/// @return Kante, die dem Median der Mediane der übergebenen Kanten entspricht
  Edge findMedianOfMedians(std::vector<std::vector<Edge>> values){
    std::vector<Edge> medians;

    for(unsigned int i = 0; i < values.size(); i++){
      Edge m = findMedian(values[i]);
      medians.push_back(m);
    }
    return findMedian(medians);
  }


  /// @brief Berechnet das k-te Element des Vektors temp
  /// @param temp Vektor an Kanten
  /// @param k Die k-te größte Kante ist gesucht
  /// @return Die k-te größte Kante aus dem Vektor temp
  Edge selectKthElement(const std::vector<Edge>& values, int k){
    // Teile den Vektor in Vektoren der Größe 5 auf
    std::vector<std::vector<Edge>> vecOfSubsets;

    int count = 0;
    while(count != (int) values.size()){
      int countRow = 0;
      std::vector<Edge> subset;

      while((countRow < 5) && (count < (int) values.size())){
        subset.push_back(values[count]);
        count++;
        countRow++;
      }
      vecOfSubsets.push_back(subset);
    }

    // Berechne ein neues Pivot Element für die Teilung
    Edge m = findMedianOfMedians(vecOfSubsets);

    // Teile die Elemente in zwei Gruppen ein. Die mit kleinerem und die mit größerem Wert als das Pivot Element
    std::vector<Edge> L1;
    std::vector<Edge> L2;
    
    // allgemeine Lage sorgt dafür, dass nicht mehrere Kanten die gleiche Länge haben
    for (int i = 0; i < (int) vecOfSubsets.size(); i++) {
        for (int j = 0; j < (int) vecOfSubsets[i].size(); j++) {
            if (vecOfSubsets[i][j] < m) {
                L1.push_back(vecOfSubsets[i][j]);
            }else if (vecOfSubsets[i][j] > m){
                L2.push_back(vecOfSubsets[i][j]);
            }
        }
    }

  // Rekursive Aufrufe der Methode
    if ((k - 1) == (int) L1.size()) {
        return m;
    }
    else if (k <= (int) L1.size()) {
      return selectKthElement(L1, k);
    }
    else if (k > (int) (L1.size() + 1)){
      return selectKthElement(L2, k-((int)L1.size())-1);
    }

    // Dead Code, um keine Warnung zu erhalten
    exit(-1);
  }

  
  /// @brief Bildet die Vereinigung der zwei Punktmengen Q und R
  /// @param Q erste Punktmenge
  /// @param R zweite Punktmenge
  /// @return Gibt die Vereinigung der Punktmengen zurück
  std::set<Point> unionOfSets(const std::set<Point>& Q, const std::set<Point>& R){
    std::set<Point> temp{Q};
    temp.insert(R.begin(), R.end());
    return temp;
  }


/// @brief Bildet die Vereinigung der drei Punktmengen P, Q und R
/// @param Q erste Punktmenge
/// @param R zweite Punktmenge
/// @param N dritte Punktmenge
/// @return Gibt die Vereinigung der Punktmengen zurück
  std::set<Point> unionOfSets(const std::set<Point>& Q, const std::set<Point>& R, const std::set<Point>& N){
    std::set<Point> temp{Q};
    temp.insert(R.begin(), R.end());
    temp.insert(N.begin(), N.end());
    return temp;
  }