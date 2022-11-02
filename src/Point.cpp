  #include "Point.hpp"
  
  
  /// @brief Überschreibe den Ausleseoperator, um Punkte gemäß des Inhalts des Streams zu erzeugen
  std::istream& operator>>(std::istream& stream, Point& p){
    return stream >> p.x >> p.y;
  }

  /// @brief Überschreibe den Einfügeoperator, sodass zu einem Punkt die x und y Koordinate ausgegeben wird 
  std::ostream& operator<<(std::ostream& os, const Point point){
    os << "Punkt: (" << point.x << ", " << point.y << ")";
    return os;
  }

  /// @brief Überschreibe den "<" Operator, sodass ein Punkt p1 kleiner als ein Punkt p2 ist, wenn er lexikografisch kleiner ist
  bool operator<(const Point& p1, const Point& p2){
    return p1.x < p2.x || (p1.x==p2.x && p1.y < p2.y);
  }

  /// @brief Überschreibe den "==" Operator, sodass ein Punkt p1 gleich einem Punkt p2 ist, wenn die Koordinaten paarweise gleich sind
  bool operator==(const Point& p1, const Point& p2){
    return p1.x == p2.x && p1.y == p2.y;
  }


  /// @brief Prüfe, ob der Punkt r links neben der Kante von p nach q liegt
  /// @param p Punkt p
  /// @param q Punkt q
  /// @param r Punkt r
  /// @return Boolean, ob r links neben der Strecke pq liegt
  bool leftTurn(const Point& p, const Point& q, const Point& r){
    double flaecheninhalt = 0.5 * (q.x * r.y + r.x * p.y + p.x * q.y - q.x * p.y - p.x * r.y - r.x * q.y);
    return flaecheninhalt > 0;
  }

  /// @brief Finde die Wurzel bzgl. der parents zu Punkt x, über den eine Zusammenhangskomponente repräsentiert wird
  /// @param x Punkt x
  /// @return Zeiger auf einen Punkt, der der Wurzel Vater von x ist
  Point& findSet(Point& x){
    if(!(x == *x.parent)){
      return findSet(*x.parent);
    }
    return x;
  }

  /// @brief Führe die zwei Zusammenhangskomponenten zusammen, indem beide Punkte den selben parent erhalten
  /// @param x Punkt x
  /// @param y Punkt y
  void linkSets(Point& x, Point& y){
    if(x.rank > y.rank){
      y.parent = &x;
    }
    else{
      x.parent = &y;
    }
    if(x.rank == y.rank){
      y.rank += 1;
    }
  }
  
  /// @brief Verknüpfe die zwei Zusammenhangskomponenten zu den Punkten x und y, indem die Wurzeln gesucht und aktualisiert wird
  /// @param x Punkt x
  /// @param y Punkt y
  void unionSets(Point& x, Point& y){
    linkSets(findSet(x), findSet(y));
  }