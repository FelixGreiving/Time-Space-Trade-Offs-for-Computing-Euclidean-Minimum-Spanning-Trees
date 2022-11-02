#pragma once

#include "AssPoints.hpp"

/// @brief Die Struktur AssEdges besteht aus zwei AssPoints und repräsentiert über (p1.p, p2.p) die aktuell betrachtete Kante und über 
/// (p1.associatedPoint, p2.associatedPoint) die assoziierte/ursprüngliche Kante
typedef struct AssEdges{
  AssPoints p1;
  AssPoints p2;

  /// @brief Konstruktor zum Erzeugen einer Instanz von AssEdges mit den zwei AssPoints p1 und p2
  /// @param p1 Erster Endpunkt der zu erzeugenden AssEdge
  /// @param p2 Zweiter Endpunkt der zu erzeugenden AssEdge
  AssEdges(AssPoints p1, AssPoints p2){
    this->p1 = p1;
    this->p2 = p2;
  }
}AssEdges;

/// @brief Überschreiben des Einfügeoperators, sodass dieser die aktuelle Kante und die assoziierte Kante des AssEdges enthält 
std::ostream& operator<<(std::ostream& os, const AssEdges& e);

/// @brief Überschreibe den "<" Operator, sodass eine Instanz von AssEdges kleiner ist als eine andere, wenn sie bzgl. des kleinsten Punktes der AssEdges 
/// umgekehrt lexikografisch kleiner ist als der kleinste Punkt der anderen Instanz
bool operator<(const AssEdges& e1, const AssEdges& e2);

/// @brief überschreibe den "==" Operator, sodass zwei Instanzen von AssEdges gleich sind, wenn die Koordinaten beider Punkte einer Instanz mit denen der
/// anderen Instanz übereinstimmen
bool operator==(const AssEdges& e1, const AssEdges& e2);