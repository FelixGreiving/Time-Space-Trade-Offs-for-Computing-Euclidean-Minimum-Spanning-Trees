#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include "Edge.hpp"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


/// @brief Adapter für einen CGAL Transformer, um den Spezialfall k==0 zu berücksichtigen und Rundungsfehler vermeiden
class Transformer{
  private:
  int k;
  CGAL::Aff_transformation_3<K> transformer;

  public:
  Transformer(int k):k{k}, transformer{std::cos(k*M_PI/3), -std::sin(k*M_PI/3), 0, std::sin(k*M_PI/3), std::cos(k*M_PI/3), 0, 0, 0, 0}{}
  /// @brief Methode zum Drehen des Punktes point um den Winkel k*60°
  /// @param point zu drehender Punkt
  /// @return um k*60° gedrehten Punkt
  K::Point_3 rotate(K::Point_3 point){
    if(k==0){
      return point;
    }
    else{
      return transformer.transform(point);
    }
  }
};


/// @brief Drehe alle Eingabepunkte um den Winkel k*60° und speichere diese in dem Vektor vecPoints
/// @param inputPoint Menge an Eingabepunkten
/// @param transformer Transformationsobjekt zur Drehung der Eingabepunkte
/// @param vecPoints Referenz auf Vektor von Punkten, in den die gedrehten Punkte eingefügt werden können
void rotatePoints(std::set<K::Point_3>& inputPoints, Transformer& transformer, std::vector<K::Point_3>& vecPoints);


/// @brief Gebe zurück, ob (xCoord, yCoord) in vecPoints liegt
/// @param vecPoints Vektor von assPoints, der umgekehrt lexikographisch sortiert ist und mindestens ein Element enthält
/// @param xCoord x-Koordinate des gesuchten Punktes
/// @param yCoord y-Koordinate des gesuchten Punktes
/// @return Gibt zurück, ob der Punkt (xCoord, yCoord) in vecPoints liegt
bool binarySearch(std::vector<K::Point_3> &vecPoints, double xCoord, double yCoord);


/// @brief Gebe den Index des minimalen Punktes unter allen Punkten, die größer als (xCoord, yCoord) sind, zurück.
/// Laut Voraussetzung ist (xCoord, yCoord) in vecPoints enthalten, oder kleiner als der größte Punkte in vecPoints
/// @param vecPoints Vektor von assPoints, der umgekehrt lexikographisch sortiert ist und mindestens ein Element enthält
/// @param xCoord x-Koordinate des zu vergleichenden Punktes
/// @param yCoord y-Koordinate des zu vergleichenden Punktes
/// @return Index an dessen Position der minimalen Punkts unter den größeren Punkten als (xCoord, yCoord) in vecPoints liegt 
int minBinarySearch(std::vector<K::Point_3> &vecPoints, double xCoord, double yCoord);


/// @brief Gebe den Index des maximalen Punktes unter allen Punkten, die kleiner als (xCoord, yCoord) sind, zurück.
/// Laut Voraussetzung ist (xCoord, yCoord) in vecPoints enthalten oder größer als der kleinste Punkt in vecPoints
/// @param vecPoints Vektor von assPoints, der umgekehrt lexikographisch sortiert ist und mindestens ein Element enthält
/// @param xCoord x-Koordinate des zu vergleichenden Punktes
/// @param yCoord y-Koordinate des zu vergleichenden Punktes
/// @return Index an dessen Position der maximale Punkt unter den kleineren Punkten als (xCoord, yCoord) in vecPoints liegt 
int maxBinarySearch(std::vector<K::Point_3> &vecPoints, double xCoord, double yCoord);


/// @brief Berechnet für einen Vektor an Kanten den Median bzgl. der "<" Ordnung
/// @param vec Vektor an Kanten
/// @return Die Kante, die dem Median in vec entspricht
Edge findMedian(std::vector<Edge> vec);


/// @brief Berechnet für einen Vektor von Vektoren an Kanten den Median der Mediane bzgl. der "<" Ordnung
/// @param values Vektor der Vektoren mit je 5 Kanten enthält
/// @return Kante, die dem Median der Mediane der übergebenen Kanten entspricht
Edge findMedianOfMedians(std::vector<std::vector<Edge>> values);

  
/// @brief Berechnet das k-te Element bzgl. "<" des Vektors temp
/// @param temp Vektor an Kanten
/// @param k Die k-te größte Kante ist gesucht
/// @return Die k-te Kante aus dem nach "<" geordneten Vektor temp
Edge selectKthElement(const std::vector<Edge>& temp, int k);

  
/// @brief Bildet die Vereinigung der zwei Punktmengen Q und R
/// @param Q erste Punktmenge
/// @param R zweite Punktmenge
/// @return Gibt die Vereinigung der Punktmengen zurück
std::set<Point> unionOfSets(const std::set<Point>& Q, const std::set<Point>& R);


/// @brief Bildet die Vereinigung der drei Punktmengen P, Q und R
/// @param Q erste Punktmenge
/// @param R zweite Punktmenge
/// @param N dritte Punktmenge
/// @return Gibt die Vereinigung der Punktmengen zurück
std::set<Point> unionOfSets(const std::set<Point>& Q, const std::set<Point>& R, const std::set<Point>& N);