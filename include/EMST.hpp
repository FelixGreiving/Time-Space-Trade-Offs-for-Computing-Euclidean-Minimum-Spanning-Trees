#pragma once
#include "Graph.hpp"
#include <fstream>
#include "RNG.hpp"
#include "Config.h"

// Gibt an, ob der Hilfsgraph G, dessen face-cycles und das S-Netz zu allen Durchläufen in die korrespondierenden Dateien geschrieben werden
#define WRITE_INTO_ALL_FILES 1

// Forward declaration, um include-Konflikte zu vermeiden
class EMSTTest;

/// @brief Die Klasse EMST dient zur Berechnung und Ausgabe eines EMSTs zu einer Eingabepunktmenge. Im Konstruktor wird dabei der Algorithmus gemäß der Idee 
/// des Time Space Trade-Offs von Banyassadi implementiert, der auf O(s) Speicherzellen und in einer Laufzeit von O(n³/s²*log(s)) den EMST berechnet. Zudem 
/// werden die Delaunay Triangulation, der Relative Nachbarschaftsgraph, das S-Netz, der Hilfsgraph G für den jeweiligen partiellen Relativen Nachbarschaftsgraphen
/// RNG_i und dessen face-cycles in eine Datei geschrieben
class EMST{

  // Deklariere Test Fixture EMSTTest als friend, um private Methoden der Klasse RNG zu testen
  friend EMSTTest;

  private:

  // Der Default-Konstruktor muss für das Text-Fixture implementiert sein, wird ansonsten aber nicht gebraucht
  EMST(){};

  // Default-Zuweisungsoperator nur zum Testen definiert
  EMST& operator=(EMST&) = default;


  // Der Algorithmus darf O(s) viele Speicherzellen nutzen
  int s;

  // Ausgabestreams
  std::fstream file_out_Delaunay;
  std::fstream file_out_RNG;
  std::fstream file_out_EMST;
  std::fstream file_out_G;
  std::fstream file_out_Face_Cycles_G;
  std::fstream file_out_SNet;


  /// @brief Initialisiere und öffne die Dateien zur Speicherung der Delaunay Triangulation, des RNGs, des EMSTs und der anderen Hilfsstrukturen
  void openFiles();

  /// @brief Gebe für alle Punkte aus der Menge Q alle adjazenten Punkte (Nachbarn) im Graphen G zurück
  /// @param Q Menge aller Punkte, zu der die Nachbarn im Graphen G gesucht sind
  /// @param G Graph G, der mit Adjazenzlisten repräsentiert wird
  /// @return eine Menge von Punkten, die adjazent zu Punkten aus Q und in G sind
  std::set<Point> calcNeighbors(const std::set<Point>& Q, const Graph& G);

  /// @brief Lese aus dem Graphen G alle Kanten aus, zu denen Punkt(e) aus potEdges inzident sind und speichere diese in potEdges
  /// @param G Graph G, der mit Adjazenzlisten gespeichert wird
  /// @param potEdges Menge an Adjazenzlisten zu einer Teilmenge von Punkten aus G aus dem RNG
  void calcPotEdges(const Graph& G, std::set<struct AdjList>& potEdges);

  /// @brief Gibt ein Set von Punkten aus G zurück, die adjazent zu Punkten, die eine Adjazenzliste in potEdges definieren, sind
  /// Dabei werden alle Kanten aus den Adjazenzlisten von potEdges gelöscht, die nicht mehr in G vorkommen
  /// @param G Graph G, der mit Adjazenzlisten repräsentiert wird
  /// @param potEdges Menge an Adjazenzlisten zu einer Teilmenge von Punkten aus G aus dem RNG
  /// @return Menge mit allen Punkten aus G, die adjazent zu den Punkten aus potEdges sind
  std::set<Point> calcRemainingNeighbors(const Graph& G, std::set<struct AdjList>& potEdges);  

  /// @brief Gebe zu jedem Punkt aus subset alle adjazenten Punkte im RNG, durch potEdges repräsentiert, zurück
  /// @param potEdges Menge an Adjazenzlisten zu einer Teilmenge von Punkten aus G aus dem RNG
  /// @param subset Menge an Punkten, zu denen alle adjazenten Punkte im RNG gesucht sind
  /// @return Vektor von Vektoren, der zu jedem Punkt aus subset alle adjazenten Punkte des RNGs enthält
  std::vector<std::vector<Point>> extractAllNeighbors(const std::set<struct AdjList>& potEdges, const std::vector<Point>& subset);

  /// @brief Berechnet für jeden Punkt des subset alle Punkte aus S, sodass die beiden Punkte eine Kante im RNG(S) definieren 
  /// Punkten eine Kante im RNG(S) bilden
  /// @param S Eingabepunktmenge
  /// @param subset Teilmenge von S
  /// @return Vektor, der zu jedem Punkt q des subsets einen Vektor mit allen Punkten aus S enthält, sodass jeder dieser Punkte mit q 
  /// eine Kante im RNG(S) definiert
  std::vector<std::vector<Point>> calcAdjacentPointsInRNG(const std::vector<Point>& input, const std::vector<Point>& subset);

  /// @brief Berechne für alle Elemente aus {S[first],..., S[last-1]} der Eingabemenge S alle Kanten (p_i, p_j), die zum RNG(S) gehören, 
  /// wobei p_i < p_j und p_i aus {S[first],..., S[last-1]} kommt, also inzident zu diesen ist. Das erspart später Arbeit bei der Betrachtung der Kanten,
  /// da keine entgegengesetzten Kanten separat betrachtet werden müssen.
  /// @param S Eingabepunktmenge S
  /// @param first Index, um das Element S[first] zu finden
  /// @param last Index, um das Element S[last] zu finden
  /// @return alle Kanten (p_i, p_j) des RNGs mit p_i < p_j und p_i kommt aus der Menge {S[first],..., S[last-1]}
  std::vector<Edge> calcBatchOfEdges(const std::vector<Point>& S, int first, int last);

  /// @brief Berechnet die s nächstgrößeren Kanten des RNGs zu der Eingabepunktmenge S in aufsteigender Reihenfolge, die länger als die Kante upperLength sind
  /// @param S Eingabepunktmenge
  /// @param upperLength Die Länge der längsten Kante des vorherigen RNG_i
  /// @param s Anzahl an weiteren, zu findenden Kanten aus dem RNG
  /// @return Vektor der die s größten Kanten des RNG_i+s in aufsteigender Reihenfolge enthält
  std::vector<Edge> calcBatchOfSortedEdges(const std::vector<Point>& input, double upperLength);


  /// @brief calculateH berechnet eine Menge von Kanten, die die Kanten des S-Netzes und die nachfolgenden Kanten der batchEdges im aktuellen RNG_i enthält
  /// @param inputPoints Eingabepunktmenge
  /// @param sNet S-Netz, das den aktuellen RNG_i(inputPoints) repräsentiert
  /// @param batchEdges Menge von Kanten des RNG_i+s, die später eingefügt werden sollen
  /// @param upperLength Länge der längsten Kante des RNG_i(S)
  /// @return Vektor von Kanten des S-Netzes und der Nachfolger der batch edges
  std::vector<Edge> calculateH(const std::vector<Point>& input, const std::vector<Edge>& sNet, const std::vector<Edge>& batchEdges, double upperLength);

  /// @brief Berechnet mit Hilfe einer binären Suche, ob die Kante e in der Repräsentation des Hilfsgraphen H enthalten ist
  /// @param e gesuchte Kante
  /// @param H Vektor von Kanten, die H repräsentieren
  /// @return Gibt zurück, ob e im Vektor H ist
  bool edgeIsHEdge(const Edge& e, const std::vector<Edge>& H);

  /// @brief Berechnet den Hilfsgraphen G, der den aktuellen RNG_i kompakt mit O(s) Speicher repräsentiert
  /// @param inputPoints Eingabepunktmenge, zu der der EMST gesucht ist
  /// @param H Menge an relevanten Kanten zur Erstellung von G
  /// @param batchEdges Vektor mit den in den RNG_i einzufügenden batch edges
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return Hilfsgraph G
  Graph calculateG(const std::vector<Point>& input, const std::vector<Edge>& H, const std::vector<Edge>& batchEdges, double upperLength);

  /// @brief Schreibe den Hilfsgraphen G in eine Datei
  /// @param G Hilfsgraph G
  void writeGToFile(Graph& G);

  /// @brief Schreibe alle face-cycles des Hilfsgraphen G in eine Datei
  /// @param G Hilfsgraph G
  void writeFaceCyclesOfGToFile(Graph& G);

  /// @brief Fügt die Kante batchEdge über zwei gerichtete Kanten in G ein, sodass die Face-Cycles korrekt angepasst werden
  /// @param G Hilfsgraph G, in den die Batch Edge eingefügt wird
  /// @param batchEdge k-te Kante der einzufügenden Batch Edges. Diese wird in den RNG_i+k eingefügt
  /// @param neighborsP1 alle Nachbarn des heads der Batch Edge im RNG
  /// @param neighborsP2 alle Nachbarn des tails der Batch Edge im RNG
  /// @param upperLength Länge der längsten Kante von RNG_i+k, wobei RNG_i der aktuelle Graph ist und bereits k-1 batchEdges eingefügt wurden
  void insertBatchEdge(Graph& G, const Edge& batchEdge, const std::vector<Point>& neighborsP1, const std::vector<Point>& neighborsP2, double upperLength);

  /// @brief Gebe für die einzufügenden Batch Edges des RNGs aus, ob diese auch zum EMST gehört und erstelle einen Hilfsgraphen, der die face-cycles des 
  /// aktuellen RNG_i während und nach dem Einfügen des s Kanten kompakt repräsentiert
  /// @param inputPoints Eingabepunktmenge zu der der EMST berechnet werden soll
  /// @param sNet Vektor an Kanten, die das S-Netz für den aktuellen RNG_i darstellen
  /// @param batchEdges Vektor an Kanten des RNGs, der Länge nach sortiert, die in den RNG_i eingefügt werden und die zum EMST gehören können
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return Graph, der die face-cycles von RNG_i+s repräsentiert
  Graph reportEdgesOfEMST(const std::vector<Point>& input, const std::vector<Edge>& sNet, const std::vector<Edge>& batchEdges, double upperLength);

  /// @brief Berechne für ausreichende Größen der Face-Cycles die gleichmäßig verteilten neuen Positionen, an denen die Net-Edges im RNG_i+s liegen. 
  /// Suche mit diesen Werten für jede Net-Edge eine Startkante der Länge 1 in G und berechne ausgehend von dieser die Anzahl an Schritten (O(n/s)), 
  /// die man von dieser aus im RNG_{i+s} bis zur Net-Edge (parallel) laufen muss
  /// @param G Hilfsgraph G
  /// @param remainingSteps gibt für eine startEdge nach der Berechnung an, wie viele Schritte man laufen muss, um die dazu korrespondierende net-Edge zu finden
  /// @param n Anzahl der Eingabepunkte
  /// @return Vektor an Kanten, der die Startkanten im Graph G zur Suche der Net-Edges in reminingSteps Schritten enhält
  std::vector<Edge> calculateStartValues(Graph& G, std::vector<int>& remainingSteps, int n);

  /// @brief Berechne ausgehend von den Startkanten mit enstprechend remainingSteps vielen parallel Läufen alle neuen net-Edges
  /// @param inputPoints Eingabepunkte, zu der der EMST gesucht ist
  /// @param startEdges Kanten, die als Ausgangspunkt zur Suche der net-edges dienen
  /// @param remainingSteps Vektor von ints zur Angabe, wie viele Schritte man von welcher H-Edge machen muss, um die gesuchte net-edge zu finden
  /// @param upperLength Länge, die größer ist als die längste Kante des aktuellen RNG_i+s und kleiner als die längste von RNG_i+s+1
  /// @return Vektor, der die neuen net-edges zur Repräsentation des RNG_i+s enthält
  std::vector<Edge> calculateNewSNet(const std::vector<Point>& input, const std::vector<Edge>& startEdges, std::vector<int>& remainingSteps, double upperLength);

  /// @brief Berechne nachdem die s nächstgrgößeren Kanten des RNGs in den aktuellen RNG_i eingefügt wurden das S-Netz für den RNG_i+s
  /// @param inputPoints Eingabepunktmenge zu der der EMST gesucht ist
  /// @param run gibt an, zum wievielten Mal s Kanten hinzugefügt wurden
  /// @param G Hilfsgraph G, der die face-cycles von RNG_i+s repräsentiert
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return S-Netz als Vektor von Kanten 
  std::vector<Edge> maintainSNet(const std::vector<Point>& input, int run, Graph& G, double upperLength);


  public:

  /// @brief Der Konstruktor der Klasse EMST berechnet unter Nutzung von O(s) Speicherzellen den Euklidischen minimalen Spannbaum zun den Eingabepunkten.
  /// Dies wird mit einer Laufzeit von O(n³/s²*log(s)) realisiert
  /// @param inputPoints Vektor von Eingabepunkten in allgemeiner Lage
  /// @param s O(s) Speicherzellen dürfen zur Berechnung genutzt werden
  EMST(const std::vector<Point> input, int s);

  /// @brief Schließe beim Destruieren alle geöffneten Dateien
  virtual ~EMST();
};