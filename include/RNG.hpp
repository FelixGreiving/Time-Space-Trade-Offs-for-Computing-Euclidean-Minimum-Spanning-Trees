#pragma once
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_2.h>

#include <cmath>
#include <algorithm>
#include <functional>

#include "EMST.hpp"
#include "AssEdges.hpp"
#include "utils.hpp"
#include "Config.h"

  typedef CGAL::Delaunay_triangulation_2<CGAL::Projection_traits_xy_3<K>> Delaunay;


  /// @brief Definiere orderTypeAssEdges als Funktionssignatur für eine Ordnung auf AssEdges (Typ der angle Funktion)
  typedef std::function<bool (const AssEdges&, const AssEdges&) > orderTypeAssEdges; 

  /// @brief Definiere orderTypeAssPoints als Funktionssignatur für eine Ordnung auf AssPoints (Typ der yOrder und assOrder Funktion)
  typedef std::function<bool (const AssPoints&, const AssPoints&) > orderTypeAssPoints; 

  /// @brief Definiere assPointsSet als Menge von AssPoints gemäß einer Ordnung mit der Signatur orderTypeAssPoints
  typedef std::set<AssPoints, orderTypeAssPoints> assPointsSet;


  /// @brief Die Struktur OrientedAdjList besteht aus einem assPoint p und einem multiset an Kanten, die gemäß des eingeschlossenen Winkels mit dem 
  /// y-Achsenabschnitt des ersten Punktes p von p einsortiert werden. In dem multiset können genau zwei Kanten den gleichen Winkel einfschließen, 
  /// da nur Kanten (p.p,q.p) in e eingefügt werden, für die p.p < q.p gilt.
  struct OrientedAdjList{
    AssPoints p;

    // Die Ordnung auf orientedAdjLists ist über den assoziierten Punkten p definiert worden. Mutable erlaubt es, konstante Referenz zu bearbeiten.
    // Das birgt i. A. die Gefahr die Ordnung in dem Multiset zu ändern. Da die Ordnung vom struct OrientedAdjList unabhängig von Änderungen auf e ist,
    // darf mutable genutzt werden.
    mutable std::multiset<AssEdges, orderTypeAssEdges> e;

    /// @brief Konstruktor zum Erzeugen einer OrientedAdjList mit einem AssPoint 
    /// @param p AssPoint, zu dem die partielle Adjazenzliste erzeugt werden soll
    OrientedAdjList(AssPoints& p);
  };

  /// @brief Die ">" Relation ist auf entries gemäß der umgekehrt lexikografischen Ordnung auf dem ersten Punkt seiner assoziierten Punkte definiert
  /// @param orientedAdjList1 Referenz auf ersten zu vergleichenden OrientedAdjList
  /// @param orientedAdjList2 Referenz auf zweiten zu vergleichenden OrientedAdjList
  /// @return Gibt zurück, ob das erste OrientedAdjList kleiner ist als das zweite OrientedAdjList
  bool operator>(const struct OrientedAdjList& orientedAdjList1, const struct OrientedAdjList& orientedAdjList2);


  /// @brief Die "==" Relation ist auf entries gemäß der Gleichheit der ersten beiden Punkte zu den assozierten Punkt der beiden entries definiert
  /// @param orientedAdjList1 Referenz auf ersten zu vergleichenden OrientedAdjList
  /// @param orientedAdjList2 Referenz auf zweiten zu vergleichenden OrientedAdjList
  /// @return Gibt zurück, ob die entries gleich sind
  bool operator==(const struct OrientedAdjList& orientedAdjList1, const struct OrientedAdjList& orientedAdjList2);


  // Forward declaration, um include-Konflikte zu vermeiden
  class RNGTest;


  /// @brief Die Klasse RNG dient zur Berechnung und Speicherung eines Relativen Nachbarschaftsgraphen, der durch Adjazenzlisten repräsentiert wird. Dabei
  /// gilt für alle Kanten p_ip_j p_i < p_j. Zur Berechnung des relativen Nachbarschaftsgraphen wird der Algorithmus von Supovit mit der Methode calculateRNG()
  /// und ein naiver Algorithmus mit der Methode calcRNGTrivial() implementiert.
  class RNG{
  
  // Deklariere Test Fixture RNGTest als friend, um private Methoden der Klasse RNG zu testen
  friend RNGTest;

  private:
  
  // Default-Konstruktor dient nur zum Testen der im anderen Konstruktor aufgerufenen Methoden
  RNG(){};

  // setOfOrientedAdjList repräsentiert den Graphen durch ein Set von partiellen Adjazenzlisten
  std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> setOfOrientedAdjLists;

  // Der Baum T (wie im Pseudocode benannt) speichert die aktiven Punkte bzgl. der y-Koordinate. 
  assPointsSet T;

  // rotatedInputPoints speichert die gedrehten Eingabepunkte nach ihrer umgekehrt lexikografischen Reihenfolge
  std::vector<K::Point_3> rotatedInputPoints;

  // Eingabemenge an zufällig gewählten Punkten, für die der Relative Nachbarschaftsgraph berechnet werden soll
  std::set<K::Point_3> input;
  
  
  /// @brief Erzeuge alle AssPoints mit den Punkten der Eingabemenge und dem k*60° gedrehten Punkt und speichere diese in dem Set associatedPoints
  /// @param transformer Referenz auf Objekt zum Drehen der Punkte um 60°
  /// @param associatedPoints Referenz auf Punktmenge, die nach der Methode die neu erzeugten assoziierten Punkte enthält
  void initAssPoints(Transformer& transformer, assPointsSet& associatedPoints);


  /// @brief Berechne zu allen Delaunay Kanten die assoziierten Kanten und speichere diese gemäß der umgekehrt lexikografischen Ordnung auf 
  /// ihrem ersten Punkt in der Struktur von assoziierten Punkten in dem Set delaunayEdges.
  /// @param dt Referenz auf Delaunay Objekt
  /// @param delaunayEdges Referenz auf die Menge, die alle assoziierten Kanten gemäß der obigen Ordnung am Ende enthält
  /// @param umgAssociatedPoints Referenz auf Menge von assoziierten Punkten, mit denen die zu den Delaunay Kanten korrespondierenden Kanten 
  /// gefunden werden
  void sortAssEdges(const Delaunay& dt, std::set<AssEdges>& allEdges, const assPointsSet& umgAssociatedPoints);


  /// @brief initSearchInT gibt zurück, ob nachfolgend auf- oder absteigend in T gesucht werden soll
  // Außerdem passt es den aktuellen Iterator in T an, falls dieses erlaubt ist. Falls nicht, setzt es den Bool nextPointNotFound auf true
  /// @param actEdge_it Referenz auf Iterator zur aktuell betrachteten Kante. Zu dieser sollen die Punkte zwischen den y-Werten der Punkte in 
  /// auf-, oder absteigender Reihenfolge betrachtet werden
  /// @param actPoint_it Referenz auf Iterator zum aktuellen Element in T. Der Iterator wird gegebenenfalls angepasst
  /// @param nextPointNotFound Referenz auf Boolean wird auf true gesetzt, falls der nächste Wert gefunden wurde
  /// @return Gibt zurück, ob nachfolgend auf- oder absteigend in T gesucht werden soll
  bool initSearchInT(const std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdge_it, assPointsSet::iterator& actPoint_it, bool& nextPointNotFound);


  /// @brief findAssEdges findet zu einem gegebenen Iterator edgeIt die assoziierte Kante AssEdges aus der assoziierten Struktur
  /// @param actEdge_it Referenz auf Iterator zur aktuell betrachteten Kante, für die die assozierte Kante gesucht ist
  /// @return liefert die assoziierte Kante zu *edgeIt zurück
  AssEdges findAssEdges(const std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdge_it);

  
  /// @brief Lösche die Kante actEdge mit Hilfe des Iterators actEdge_it aus der Adjazenzliste, repräsentiert durch actOrientedAdjList_it.
  /// Dazu wird die Kante aus der aktuellen Adjazenzliste zum Iterator actOrientedAdjList_it gelöscht.
  /// @param actEdge Kopie der zu löschenden Kante
  /// @param actEdge_it Referenz auf Iterator zu der gefundenen zu löschenden Kante. Wegen des Multisets müssen actEdge und *actEdge_it nicht identisch sein
  /// @param actOrientedAdjList_it Referenz auf Iterator zur aktuellen Adjazenzliste aus dem assoziierten Graphen, der die Kante actEdge enthält
  void deleteAssociatedEdge(AssEdges actEdge, std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdge_it, std::set<OrientedAdjList, std::greater<OrientedAdjList>>::iterator& actEntry_it);


  /// @brief nextElementInT berechnet ausgehend vom Iterator actPoint_it zum aktuellen Punkt in T und entsprechend der Suchrichtung forward den nächsten Punkt
  /// in T
  /// @param actPoint_it Referenz auf Iterator zum aktuell betrachteten Element im Baum T
  /// @param forward gibt an, ob auf- oder absteigend in T gesucht werden soll
  /// @return Gibt zurück, ein nächster Punkt in T existiert
  bool nextElementInT(assPointsSet::iterator& actPoint_it, bool forward);


  /// @brief Vorverarbeitungsschritt, Lösche eine Kante aus assGraph, falls ein Punkt aus assGraph existiert, der strikt in der Projektion der Kante liegt
  /// @param assGraph assGraph ist Referenz auf assoziierten Graph, aus dem die korrespondierenden Kanten entfernt werden sollen
  void eliminateWithProjection(RNG& assGraph);


  /// @brief Führe einen der sechs Schritte des Algorithmus für die aktuell gedrehten Punkte durch.
  /// Lösche dabei auch die korrespondierenden Kanten im assoziierten Graph assGraph
  /// @param assGraph Referenz auf den Graph, in dem die assoziierten Kanten ebenfalls gelöscht werden sollen
  void calculateRNG(RNG& assGraph);


  public:

  /// @brief Der Konstruktor nimmt die Eingabepunkte entgegen und den Winkel k, um den diese Punkte gedreht werden sollen
  /// Dient zur Initialisierung der Eingabepunkte, der nach y-Koordinaten sortierten Baumstruktur T, den rotatedInputPoints und zum Einfügen
  /// aller Delaunay Kanten inklusive der assozierten Delaunay Kanten als AssEdges in die Adjazenzliste.
  /// @param inputPoints Eingabepunkte, zu denen der Relative Nachbarschaftsgraph gesucht ist
  /// @param k Winkel k*60°, um den die Punkte rotiert werden sollen und mit denen gerechnet wird
  RNG(const std::set<Point> inputPoints, int k);


  /// @brief calculateRNG() koordiniert die Berechnung der zu löschenden Kanten für alle 6 Richtungen im Abstand von 60°
  /// Dazu wird die Berechnung für jeden Winkel einmal auf einem temporären Graphen ausgeführt und gleichzeitig die korrespondierenden
  /// Kanten im übergebenen Graphen gelöscht. Nach 6 Iterationen sind alle Richtungen betrachtet worden und die aktuelle Instanz enthält
  /// die gesuchten Kanten des RNGs
  /// @return RNG, der den berechneten RNG mit dem Attribut setOfOrientedAdjLists repräsentiert
  RNG calculateRNG();


  /// @brief Berechnet aus den partiellen Adjazenzlisten zur Repräsentation eines RNGs eine Repräsentation des RNG mithilfe von vollständigen Adjazenzlisten, 
  /// die nicht über CGAL-Punkte definiert sind
  /// @return gericheteter Graph zur Repräsentation des ungerichteten RNGs
  Graph createUndirectedGraph();


  /// @brief Naiver Algorithmus zur Berechnung eines RNGs mit einer Laufzeit von O(n²)
  void calculateRNGTrivial();
};


  /// @brief Berechnet die Delaunay Triangulation zu der Punktmenge input und schreibt die Delaunay Kanten in eine Datei
  /// @param input Eingabepunktmenge
  /// @param file_out_Delaunay Datei, in der die Delaunay Kanten geschrieben werden
  void writeDelaunayTriangulationToFile(const std::vector<Point>& input, std::fstream& file_out_Delaunay);