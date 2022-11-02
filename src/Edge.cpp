#include "Edge.hpp"
#include <algorithm>

  /// @brief Berechnet die Länge einer Kante als das Quadrat des euklidischen Abstands
  /// @return Länge der Kante
  double Edge::calcLength() const{
    return (tail.x-head.x)*(tail.x-head.x) + (tail.y-head.y)*(tail.y-head.y);
  }

  /// @brief Überschreibe den "==" Operator. Zwei Kanten sind genau dann identisch, wenn sie den gleichen tail, head und die gleiche comprLength haben
  bool operator==(const Edge& e1, const Edge& e2){
    return e1.calcLength() == e2.calcLength() && e1.tail == e2.tail && e1.head == e2.head && e1.comprLength == e2.comprLength && e1.again == e2.again;
  }

  /// @brief Überschreibe den "<" Operator, sodass eine Kante e1 kleiner ist als eine Kante e2, wenn diese kürzer ist, oder bei Gleichheit von dem kleineren Punkt
  /// aus gerichtet ist. Sind diese Werte auch gleich, ist eine Kante kleiner, wenn sie eine kürzere komprimierte Länge hat. Ansonsten wird über again verglichen
  bool operator<(const Edge& e1, const Edge& e2){
    return e1.calcLength() < e2.calcLength() || (e1.calcLength() == e2.calcLength() && e1.tail < e2.tail) 
      || (e1.calcLength() == e2.calcLength() && e1.tail == e2.tail && e1.comprLength < e2.comprLength) 
      || (e1.calcLength() == e2.calcLength() && e1.tail == e2.tail && e1.comprLength == e2.comprLength && e1.again < e2.again);
  }

  /// @brief Überschreibe den ">" Operator gemäß des "<" Operators, wobei e1 > e2 mit e2 < e1 umgesetzt wird 
  bool operator>(const Edge& e1, const Edge& e2){
    return e2 < e1;
  }

  /// @brief Überschreibe den Einfügeoperator, sodass eine Kante über ihre Endpunkte als (tail, head) ausgegeben wird
  std::ostream& operator<<(std::ostream& os, const Edge e){
    os << "(" << e.tail.x << ", " << e.tail.y << "); (" << e.head.x << ", " << e.head.y << ")";
    return os;
  }


  /// @brief Prüfe, ob die Kante valide ist, also ob die Länge != 0 ist
  /// @param edge Kante
  /// @return Gibt zurück, ob die Edge eine valide Kante aus disjunkten Punkten ist
  bool isValidEdge(Edge& edge){
    return edge.calcLength() != 0;
  }

  /// @brief Berechne alle Kanten aus actEdges, die länger als upperLength sind
  /// @param actEdges Vektor an zu prüfenden Kanten
  /// @param upperLength Die Länge der Kante bezüglich der verglichen wird
  /// @return gebe alle Kanten aus actEdges in einem Vektor zurück, die länger als upperLength sind
  std::vector<Edge> chooseLongerEdges(const std::vector<Edge>& actEdges, double upperLength){

    std::vector<Edge> result{};
    result.reserve(actEdges.size());
    
    std::copy_if(actEdges.begin(), actEdges.end(), std::back_inserter(result), 
      [upperLength](const Edge& e){ return e.calcLength() > upperLength;});

    return result;
  }


  /// @brief Berechne die nächste Kante von e_j auf dem face-cycle von e_j, wobei nur die adjazenten Punkte aus RNG_i in Frage kommen. Diese werden aus
  /// adjacentPoints extrahiert, indem diese mit upperLength verglichen werden
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @param ej Kante im RNG_i, für die die nächste Kante gesucht ist
  /// @param adjacentPoints Vektor an adjazenten Punkten zum head von e_j im RNG
  /// @return die nächste Kante von e_j im RNG_i
  Edge nextEdge(double upperLength, const Edge ej, const std::vector<Point>& adjacentPoints){
    Edge actEdge{ej.head, ej.tail};
    for(auto& point: adjacentPoints){
      Edge temp{ej.head, point};
      // kleiner für Vgl. mit e_i und <= für Vgl. mit e_(i-1); kann int 4 < double 4 sein?
      if(temp.calcLength() <= upperLength){
        // Falls actEdge rechts von oder auf ej liegt
        if(!leftTurn(ej.tail, ej.head, actEdge.head)){
          // Falls temp links von ej oder actEdge liegt, setze actEdge auf temp
          if(leftTurn(ej.tail, ej.head, point) || leftTurn(actEdge.tail, actEdge.head, point)){
            actEdge = temp;
          }
        }
        // Ansonsten: Also falls actEdge links von ej liegt
        else{
          // Falls temp links von ej und links von actEdge liegt, setze actEdge auf temp
          if(leftTurn(ej.tail, ej.head, point) && leftTurn(actEdge.tail, actEdge.head, point)){
            actEdge = temp;
          }
        }
      }
    }
    return actEdge;
  }


  /// @brief Berechne die im Uhrzeigersinn nächste Kante zu e_j, wobei nur die adjazenten Punkte aus RNG_i in Frage kommen. Diese werden aus
  /// adjacentPoints extrahiert, indem diese mit upperLength verglichen werden
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @param ej Kante, die nicht im RNG_i liegt, für die der Nachfolger im RNG_i gesucht ist
  /// @param adjacentPoints Vektor an adjazenten Punkten zum head von e_j im RNG
  /// @return die nachfolgende Kante von e_j im RNG_i
  Edge succEdge(double upperLength, const Edge ej, const std::vector<Point>& adjacentPoints){
    
    Edge actEdge = nextEdge(upperLength, ej, adjacentPoints);

    // Falls actEdge noch (ej.head, ej.tail) ist, gebe (0,0) Kante als Default Kante zurück
    if(actEdge.tail == ej.head && actEdge.head == ej.tail){
      actEdge = Edge{};
    }
    return actEdge;
  }