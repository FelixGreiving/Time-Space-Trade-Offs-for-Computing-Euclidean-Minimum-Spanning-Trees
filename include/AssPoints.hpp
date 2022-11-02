#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


/// @brief Die Struktur AssPoints besteht aus einem (rotierten) Punkt p und einem assoziierten/ursprünglichen Punkt associatedPoint.
typedef struct AssPoints{
  K::Point_3 p;
  K::Point_3 associatedPoint;
  AssPoints() = default;
  /// @brief Konstruktor zum Erzeugen einer Instanz von AssPoints mit den Punkten p und associatedPoint
  /// @param p Der gedrehte Punkt des zu erzeugenden AssPoints
  /// @param associatedPoint Der ursprüngliche Punkt des zu erzeugenden AssPoints
  AssPoints(K::Point_3 p, K::Point_3 associatedPoint) : p{p}, associatedPoint{associatedPoint}{}
}AssPoints;

/// @brief Überlade den Einfügeoperator, sodass dieser die Koordinaten der Punkte eines AssPoints enthält
std::ostream& operator<<(std::ostream& os, const AssPoints& point);

/// @brief Überlade den "<" Operator, sodass ein AssPoints p1 kleiner als ein AssPoints p2 ist, wenn sein rotierter Punkt p lexikografisch kleiner
/// als der rotierte Punkt von p2 ist
bool operator<(const AssPoints& p1, const AssPoints& p2);

/// @brief Überlade den "==" Operator, sodass ein AssPoints p1 gleich einem AssPoints p2 ist, wenn sein rotierter Punkt p gleich dem rotierten Punkt von p2 ist
bool operator==(const AssPoints& p1, const AssPoints& p2);

/// @brief Berechne für 3 AssPoints v, p1, p2, ob v im Inneren des Schnitts der Kreise um p1, bzw. p2 mit dem Radius |p1,p2| liegt
/// @param v Punkt v, der getestet wird
/// @param p1 AssPoints bestehend aus einem rotierten Punkt p und dem (assoziierten) ursprünglichen Punkt
/// @param p2 AssPoints bestehend aus einem rotierten Punkt p und dem (assoziierten) ursprünglichen Punkt
/// @return Gibt zurück, ob v in der lune von p1 und p2 liegt
bool lune(const AssPoints& v, const AssPoints& p1, const AssPoints& p2);