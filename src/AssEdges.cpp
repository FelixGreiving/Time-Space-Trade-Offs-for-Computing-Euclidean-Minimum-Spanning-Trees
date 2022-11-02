#include "AssEdges.hpp"

/// @brief Überschreiben des Einfügeoperators, sodass dieser die aktuelle Kante und die assoziierte Kante des AssEdges enthält 
std::ostream& operator<<(std::ostream& os, const AssEdges& e){
  os << "Kante: " << "(" << e.p1.p.x() << ", " << e.p1.p.y() << "), (" << e.p2.p.x() << ", " << e.p2.p.y() << ") \n" << "assoziierte Kante: " << "(" << e.p1.associatedPoint.x() << ", " << e.p1.associatedPoint.y() << "), (" << e.p2.associatedPoint.x() << ", " << e.p2.associatedPoint.y() << ")" << std::endl;
  return os;
}


/// @brief Überschreibe den "<" Operator, sodass eine Instanz von AssEdges kleiner ist als eine andere, wenn sie bzgl. des kleinsten Punktes der AssEdges umgekehrt
/// lexikografisch kleiner ist als der kleinste Punkt der anderen Instanz
bool operator<(const AssEdges& e1, const AssEdges& e2){
  K::Point_3 minE1 = (e1.p1 < e1.p2)? e1.p1.p : e1.p2.p;
  K::Point_3 maxE1 = (e1.p1 < e1.p2)? e1.p2.p : e1.p1.p;
  K::Point_3 minE2 = (e2.p1 < e2.p2)? e2.p1.p : e2.p2.p;
  K::Point_3 maxE2 = (e2.p1 < e2.p2)? e2.p2.p : e2.p1.p;

  return (minE1 > minE2)? true : ((minE1 == minE2)?((maxE1 > maxE2)? true : false):false);
}


/// @brief überschreibe den "==" Operator, sodass zwei Instanzen von AssEdges gleich sind, wenn die Koordinaten beider Punkte einer Instanz mit denen der
/// anderen Instanz übereinstimmen
bool operator==(const AssEdges& e1, const AssEdges& e2){
  return e1.p1.p.x() == e2.p1.p.x() && e1.p1.p.y() == e2.p1.p.y() && e1.p2.p.x() == e2.p2.p.x() && e1.p2.p.y() == e2.p2.p.y();
}