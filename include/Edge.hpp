#pragma once
#include "Point.hpp"
#include <vector>



/// @brief Die Struktur Edge repräsentiert eine gerichtete Kante vom Punkt tail zu head. Jede Kante hat einen Pointer auf den Vorgänger und Nachfolger in ihrem 
/// face-cycle. Damit diese nur einmal betrachtet werden, wird eine boolesche Variable visited eingeführt. Eine Edge kann gleichzeitig eine gewöhnliche Kante 
/// der Länge comprLength=1 sein, oder eine compressedEdge der Länge comprLength>1. Da in dem Hilfsgraphen G eine gerichtete Kante bis zu zweimal vorkommen 
/// kann und eine Ordnung darüber definiert werden soll, wird das Set von Edges in G mit dem Attribut again aus Edge als Multiset simuliert.
typedef struct Edge{
  Point tail;
  Point head;
  mutable Edge const * previous;
  mutable Edge const * next;
  mutable bool visited;
  int comprLength;
  bool again;

  double calcLength() const;

  /// @brief Default-Konstruktor für eine Dummy-Edge ((0,0),(0,0)) zur Ausnahmebehandlung von nicht validen Kanten
  constexpr Edge():tail{}, head{}, previous{nullptr}, next{nullptr}, visited{0}, comprLength{1}, again{0}{}

  /// @brief Konstruktor zum Erzeugen einer Edge mit den zwei Endpunkten, der Anzahl an Kanten, die diese aktuell repräsentiert und der
  /// Angabe, ob die Kante bereits existiert
  /// @param p1 tail der zu erzeugenden Kante
  /// @param p2 head der zu erzeugenden Kante
  /// @param comprLength Anzahl an Kanten, die diese (compressed edge) in ihrem face-cycle repräsentiert. Default ist 1 für eine gewöhnliche Kante
  /// @param again Angabe, ob diese (compressed) edge bereits erzeugt wurde
  Edge(Point p1, Point p2, int comprLength=1, bool again=0): tail{p1}, head{p2}, previous{nullptr}, next{nullptr}, visited{0}, comprLength{comprLength}, again{again}{}
}Edge;


/// @brief Überschreibe den Einfügeoperator, sodass eine Kante über ihre Endpunkte als (tail, head) ausgegeben wird
std::ostream& operator<<(std::ostream& os, const Edge e);

/// @brief Überschreibe den "==" Operator. Zwei Kanten sind genau dann identisch, wenn sie den gleichen tail, head und die gleiche Anzahl comprLength an Kanten
/// in ihrem face-cycle haben
bool operator==(const Edge& e1, const Edge& e2);


/// @brief Überschreibe den "<" Operator, sodass eine Kante e1 kleiner ist als eine Kante e2, wenn diese kürzer ist, oder bei Gleichheit von dem kleineren Punkt
/// aus gerichtet ist. Sind diese Werte auch gleich, ist eine Kante kleiner, wenn sie eine kürzere komprimierte Länge hat. Ansonsten wird über again verglichen.
bool operator<(const Edge& e1, const Edge& e2);


/// @brief Überschreibe den ">" Operator gemäß des "<" Operators, wobei e1 > e2 mit e2 < e1 umgesetzt wird 
bool operator>(const Edge& e1, const Edge& e2);

/// @brief Prüfe, ob die Kante valide ist, also ob die Länge != 0 ist
/// @param edge Kante
/// @return Gibt zurück, ob die Edge eine valide Kante aus disjunkten Punkten ist
bool isValidEdge(Edge& edge);

/// @brief Berechne alle Kanten aus actEdges, die länger als upperLength sind
/// @param actEdges Vektor an zu prüfenden Kanten
/// @param upperLength Die Länge der Kante bezüglich der verglichen wird
/// @return gebe alle Kanten aus actEdges in einem Vektor zurück, die länger als upperLength sind
std::vector<Edge> chooseLongerEdges(const std::vector<Edge>& actEdges, double upperLength);


/// @brief Berechne die nächste Kante von e_j auf dem face-cycle von e_j, wobei nur die adjazenten Punkte aus RNG_i in Frage kommen. Diese werden aus
/// adjacentPoints extrahiert, indem diese mit upperLength verglichen werden
/// @param upperLength Länge der längsten Kante des aktuellen RNG_i
/// @param ej Kante im RNG_i, für die die nächste Kante gesucht ist
/// @param adjacentPoints Vektor an adjazenten Punkten zum head von e_j im RNG
/// @return die nächste Kante von e_j im RNG_i
Edge nextEdge(double upperLength, const Edge ej, const std::vector<Point>& adjacentPoints);


/// @brief Berechne die im Uhrzeigersinn nächste Kante zu e_j, wobei nur die adjazenten Punkte aus RNG_i in Frage kommen. Diese werden aus
/// adjacentPoints extrahiert, indem diese mit upperLength verglichen werden
/// @param upperLength Länge der längsten Kante des aktuellen RNG_i
/// @param ej Kante, die nicht im RNG_i liegt, für die der Nachfolger im RNG_i gesucht ist
/// @param adjacentPoints Vektor an adjazenten Punkten zum head von e_j im RNG
/// @return die nachfolgende Kante von e_j im RNG_i
Edge succEdge(double upperLength, const Edge ej, const std::vector<Point>& adjacentPoints);