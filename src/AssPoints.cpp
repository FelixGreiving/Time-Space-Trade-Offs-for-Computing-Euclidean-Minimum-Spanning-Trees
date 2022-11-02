#include "AssPoints.hpp"
#include <cassert>
#include <iostream>


/// @brief Überlade den Einfügeoperator, sodass dieser die Koordinaten der Punkte eines AssPoints ausgibt
std::ostream& operator<<(std::ostream& os, const AssPoints& point){
  os << "Punkt: (" << point.p.x() << ", " << point.p.y() << ") und assoziierter Punkt: (" << point.associatedPoint.x() << ", " << point.associatedPoint.y() << ")" << std::endl;
  return os;
}

/// @brief Überlade den "<" Operator, sodass ein AssPoints p1 kleiner als ein AssPoints p2 ist, wenn sein rotierter Punkt p lexikografisch kleiner
/// als der rotierte Punkt von p2 ist
bool operator<(const AssPoints& p1, const AssPoints& p2){
  return p1.p.x() < p2.p.x() || (p1.p.x()==p2.p.x() && p1.p.y() < p2.p.y());
}

/// @brief Überlade den "==" Operator, sodass ein AssPoints p1 gleich einem AssPoints p2 ist, wenn sein rotierter Punkt p gleich dem rotierten Punkt von p2 ist
bool operator==(const AssPoints& p1, const AssPoints& p2){
  return p1.p.x() == p2.p.x() && p1.p.y() == p2.p.y();
}


/// @brief Berechne für 3 Punkte v, p1, p2, ob v im Inneren des Schnitts der Kreise um p1, bzw. p2 mit dem Radius |p1,p2| liegt
/// @param v Punkt v, der getestet wird
/// @param p1 AssPoints bestehend aus einem rotierten Punkt p und dem (assoziierten) ursprünglichen Punkt
/// @param p2 AssPoints bestehend aus einem rotierten Punkt p und dem (assoziierten) ursprünglichen Punkt
/// @return Gibt zurück, ob v in der lune von p1 und p2 liegt
bool lune(const AssPoints& v, const AssPoints& p1, const AssPoints& p2){

  // Berechne das Quadrat der euklidischen Distanzen vp1, vp2 und p1p2.
  double vp1 = std::pow(v.associatedPoint.x()- p1.associatedPoint.x(), 2) + std::pow(v.associatedPoint.y() - p1.associatedPoint.y(), 2);
  double vp2 = std::pow(v.associatedPoint.x()- p2.associatedPoint.x(), 2) + std::pow(v.associatedPoint.y() - p2.associatedPoint.y(), 2);
  double p1p2 = std::pow(p1.associatedPoint.x()- p2.associatedPoint.x(), 2) + std::pow(p1.associatedPoint.y() - p2.associatedPoint.y(), 2);

  // Falls v im Innenbereich der Kreise um p1 und p2 liegt, ist die Distanz von v zu den beiden Punkten kleiner als der Abstand von p1 und p2
  return (vp1 < p1p2 && vp2 < p1p2);
}