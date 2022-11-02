#pragma once
#include "Edge.hpp"
#include <set>


/// @brief Die Struktur AdjList repräsentiert eine Adjazenzliste, wobei e die Menge an Kanten ist, zu denen Punkt p inzident ist
struct AdjList{
  Point p;
 
  mutable std::set<Edge> e;

  /// @brief Konstruktor zum Erzeugen einer AdjList mit einem Point p, zu dem alle Kanten in e gespeichert werden, zu denen p inzident ist
  /// @param p Point p der zu erzeugenden AdjList
  AdjList(Point p):e{}{
    this->p = p;
  }
};

/// @brief Überschreibe den "<" Operator, sodass ein AdjList kleiner als ein anderes ist, wenn der Punkt zu dem es erstellt wurde, kleiner als der des anderen ist
bool operator<(const struct AdjList& s1, const struct AdjList& s2);

/// @brief Überschreibe den "==" Operator, sodass ein AdjList gleich einem Anderen ist, wenn der Punkt zu dem es erstellt wurde, gleich dem des anderen ist
bool operator==(const struct AdjList& s1, const struct AdjList& s2);


/// @brief Die Struktur Graph besteht aus einer Liste von Adjazenzlisten zur Repräsentation eines Graphen
typedef struct Graph{
  std::set<struct AdjList> setOfAdjLists;

}Graph;

/// @brief Überschreibe den "==" Operator, sodass zwei Graphen gleich sind, wenn die Adjazenzlisten gleich sind 
bool operator==(const Graph& G1, const Graph& G2);

/// @brief Setze alle Werte des Attributs visited jeder Kante aus G auf false zurück
/// @param G Hilfsgraph G
void resetVisitedFaceCycles(Graph& G);


/// @brief Führt eine Tiefensuche auf dem Graphen G durch und ordne alle Zusammenhangskomponenten der gleichen Wurzel bzgl. parent zu
/// @param G Graph G
void depthFirstSearch(Graph& G);

/// @brief Subroutine von depthFirstSearch, um alle Zusammenhangskomponenten zu traversieren und die Wurzel anzupassen
/// @param G Graph G
/// @param s Menge an Kanten zu einem Punkt
void dfsVisit(Graph& G, AdjList& s);