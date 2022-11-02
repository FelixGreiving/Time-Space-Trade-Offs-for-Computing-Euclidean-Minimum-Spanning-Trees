#pragma once
#include <iostream>
#include <cassert>

/// @brief Enum Klasse zur Durchführung der Tiefensuche
enum class Color{WHITE, GRAY, BLACK};


/// @brief Das Struct Point beschreibt einen Punkt durch zwei Variablen x, y, einem Pointer auf den parent Knoten, einem Rang, um eine union-find
/// Struktur auf diesem zu definieren, und einer Color, um die Knoten während des Traversierens der face-cycles, auf denen Punkte liegen, zu färben
typedef struct Point{
  double x;
  double y;
  Point* parent;
  int rank;
  Color color;

  /// @brief Default-Konstruktor, der den Punkt (0,0) erzeugt
  constexpr Point():x{0}, y{0}, parent{this}, rank{0}, color{Color::WHITE}{}

  /// @brief Konstruktor, der einen Punkt (x,y) erzeugt, sich selbst als parent initialisiert und den Knoten Weiß markiert
  /// @param x x-Koordinate des zu erzeugenden Points
  /// @param y y-Koordinate des zu erzeugenden Points
  Point(double x, double y):x{x}, y{y}, parent{this}, rank{0}, color{Color::WHITE}{}
}Point;

/// @brief Überschreibe den Ausleseoperator, um Punkte gemäß des Inhalts des Streams zu erzeugen
std::istream& operator>>(std::istream& stream, Point& p);

/// @brief Überschreibe den Einfügeoperator, sodass zu einem Punkt die x und y Koordinate ausgegeben wird 
std::ostream& operator<<(std::ostream& os, const Point point);

/// @brief Überschreibe den "<" Operator, sodass ein Punkt p1 kleiner als ein Punkt p2 ist, wenn er lexikografisch kleiner ist
bool operator<(const Point& p1, const Point& p2);

/// @brief Überschreibe den "==" Operator, sodass ein Punkt p1 gleich einem Punkt p2 ist, wenn die Koordinaten paarweise gleich sind
bool operator==(const Point& p1, const Point& p2);


/// @brief Prüfe, ob der Punkt r links neben der Kante von p nach q liegt
/// @param p Punkt p
/// @param q Punkt q
/// @param r Punkt r
/// @return Gibt zurück, ob r links neben der Strecke pq liegt
bool leftTurn(const Point& p, const Point& q, const Point& r);


/// @brief Finde die Wurzel bzgl. der parents zu Punkt x, über den eine Zusammenhangskomponente repräsentiert wird
/// @param x Punkt x
/// @return Zeiger auf einen Punkt, der dem Wurzel parent von x ist
Point& findSet(Point& x);

/// @brief Führe die zwei Zusammenhangskomponenten zusammen, indem beide Punkte den selben parent erhalten
/// @param x Punkt x
/// @param y Punkt y
void linkSets(Point& x, Point& y);

/// @brief Verknüpfe die zwei Zusammenhangskomponenten zu den Punkten x und y, indem die Wurzeln bzgl. der parents gesucht und aktualisiert werden
/// @param x Punkt x
/// @param y Punkt y
void unionSets(Point& x, Point& y);