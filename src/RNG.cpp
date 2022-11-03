#include "RNG.hpp"
  
  
  /// @brief Berechne die Delaunay Triangulation und schreibe diese in die Datei zur Delaunay Triangulation
  /// @param inputPoints 
  /// @param file_out_Delaunay 
  void writeDelaunayTriangulationToFile(const std::vector<Point>& inputPoints, std::fstream& file_out_Delaunay){
    std::set<K::Point_3> input{};
    for(auto point:inputPoints){
      K::Point_3 p{point.x, point.y, 1};
      input.insert(p);
    }
    Delaunay dt(input.begin(), input.end());
    std::for_each(dt.finite_edges_begin(), dt.finite_edges_end(),[&file_out_Delaunay, &dt](auto edge){
        K::Point_3 p1 = dt.segment(edge).point(0);
        K::Point_3 p2 = dt.segment(edge).point(1);
        file_out_Delaunay << "(" << p1.x() << ", " << p1.y() << "); (" << p2.x() << ", " << p2.y() << ")\n";
    });
  }



  /// @brief angle nimmt zwei AssEdges entgegen und bestimmt, ob die erste Kante einen kleineren Winkel zum y-Abschenabschnitt 
  /// ihres ersten Punktes einschließt als die andere. Voraussetzung ist, dass beide Kanten den gleichen ersten Punkt p1 haben und dass beide p2 der
  /// Kanten > p1 sind und dass die Eingabepunktmenge in allgemeiner Lage sind
  /// @param e1 erstes assoziiertes Kantenpaar
  /// @param e2 zweites assoziiertes Kantenpaar
  /// @return Gibt zurück, ob Kante e1 einen kleineren Winkel mit seinem y-Achsenabschnitt einschließt als e2 mit seinem (dem gleichen)
  const auto angle = [](const AssEdges& e1, const AssEdges& e2){
    
    // Prüfe Voraussetzung
    assert(e1.p1 == e2.p1 && e1.p1 < e1.p2 && e2.p1 < e2.p2);

    K::Point_3 leftPoint{e1.p1.p};
    double y1 = e1.p2.p.y();
    double y2 = e2.p2.p.y();

    // Passe die y-Werte an, damit alle Punkte mindestens die y-Koordinate wie der linke Punkt haben. 
    // So können die Winkel über die Determinante miteinander verglichen werden
    if(e1.p2.p.y() < leftPoint.y()){
      y1 = leftPoint.y() + (-e1.p2.p.y() + leftPoint.y());
    }
    if(e2.p2.p.y() < leftPoint.y()){
      y2 = leftPoint.y() + (-e2.p2.p.y() + leftPoint.y());
    }

    K::Point_3 firstPoint{e1.p2.p.x(), y1, 1};
    K::Point_3 secondPoint{e2.p2.p.x(), y2, 1};

    // Überprüfe auf Linksknick
    double determinant = firstPoint.x() * secondPoint.y() + leftPoint.x() * firstPoint.y() + secondPoint.x() * leftPoint.y() -
                          firstPoint.x() * leftPoint.y() - leftPoint.x() * secondPoint.y() - secondPoint.x() * firstPoint.y();

    // Zwei Punkte mit dem gleichen eingeschlossenen Winkel sind untereinander nicht geordnet
    return determinant > 0;
  };



  /// @brief yOrder nimmt zwei assoziierte Punkte entgegen und bestimmt, ob AssPoints p1 mit seinem Punkt p eine kleinere y-Koordinate, 
  /// oder bei Gleichheit eine kleinere x-Koordinate als Punkt p von dem AssPoint p2 hat 
  /// @param p1 erstes Paar von assoziierten Punkten
  /// @param p2 zweites Paar von assoziierten Punkten
  /// @return Gibt zurück, ob der erste Punkt von p1 bzgl. der y-Koordinate kleiner ist als der erste Punkt von p2
  const auto yOrder = [](const AssPoints& p1, const AssPoints& p2){
    return p1.p.y() < p2.p.y() || (p1.p.y() == p2.p.y() && p1.p.x() < p2.p.x());
  };


  /// @brief assOrder nimmt zwei assoziierte Punkte entgegen und bestimmt, ob das AssPoints p1 mit assoziiertem Punkt p eine kleinere 
  /// x-Koordinate, oder bei Gleichheit eine kleinere y-Koordinate als der assoziierte Punkt p von dem AssPoint p2 hat 
  /// @param p1 erstes Paar von assoziierten Punkten
  /// @param p2 zweites Paar von assoziierten Punkten
  /// @return Gibt zurück, ob der assoziierte Punkt in p1 bzgl. der lexikografischen Ordnung kleiner ist als der assoziierte Punkt in p2
  const auto assOrder = [](const AssPoints& p1, const AssPoints& p2){
    return p1.associatedPoint.x() < p2.associatedPoint.x() || (p1.associatedPoint.x()==p2.associatedPoint.x() && p1.associatedPoint.y() < p2.associatedPoint.y());
  };


  /// @brief Konstruktor zum erzeugen einer OrientedAdjList mit einem AssPoint 
  /// @param p AssPoint, zu dem die partielle Adjazenzliste erzeugt werden soll
  OrientedAdjList::OrientedAdjList(AssPoints& p):e{angle}{
      this->p = p;
  }


  /// @brief Die ">" Relation ist auf entries gemäß der umgekehrt lexikografischen Ordnung auf dem ersten Punkt seiner assoziierten Punkte definiert
  /// @param orientedAdjList1 Referenz auf ersten zu vergleichenden OrientedAdjList
  /// @param orientedAdjList2 Referenz auf zweiten zu vergleichenden OrientedAdjList
  /// @return Gibt zurück, ob das erste OrientedAdjList kleiner ist als das zweite OrientedAdjList
  bool operator>(const struct OrientedAdjList& orientedAdjList1, const struct OrientedAdjList& orientedAdjList2){
    return orientedAdjList1.p.p.x() > orientedAdjList2.p.p.x() || (orientedAdjList1.p.p.x() == orientedAdjList2.p.p.x() && orientedAdjList1.p.p.y() > orientedAdjList2.p.p.y());
  }


  /// @brief Die "==" Relation ist auf entries gemäß der Gleichheit der ersten beiden Punkte zu den assozierten Punkt der beiden entries definiert
  /// @param orientedAdjList1 Referenz auf ersten zu vergleichenden OrientedAdjList
  /// @param orientedAdjList2 Referenz auf zweiten zu vergleichenden OrientedAdjList
  /// @return Gibt zurück, ob die entries gleich sind
  bool operator==(const struct OrientedAdjList& orientedAdjList1, const struct OrientedAdjList& orientedAdjList2){
    return (orientedAdjList1.p.p.x() == orientedAdjList2.p.p.x()) && (orientedAdjList1.p.p.y() == orientedAdjList2.p.p.y());
  }


  /// @brief Erzeuge alle AssPoints mit den Punkten der Eingabemenge und dem k*60° gedrehten Punkt und speichere diese in dem Set associatedPoints
  /// @param transformer Objekt zum Drehen der Punkte um 60°
  /// @param associatedPoints Punktmenge, die nach der Methode die neu erzeugten assoziierten Punkte enthält
  void RNG::initAssPoints(Transformer& transformer, assPointsSet& associatedPoints){
    std::transform(input.begin(), input.end(), std::inserter(associatedPoints, associatedPoints.begin()),
    [&transformer](const K::Point_3 &p) -> AssPoints {

      return AssPoints{transformer.rotate(p), p};
    });
  }



  /// @brief Berechne zu allen Delaunay Kanten die assoziierten Kanten und speichere diese gemäß der umgekehrt lexikografischen Ordnung auf 
  /// ihrem ersten Punkt in der Struktur von assoziierten Punkten in dem Set delaunayEdges.
  /// @param dt Referenz auf Delaunay Objekt
  /// @param delaunayEdges Referenz auf die Menge, die alle assoziierten Kanten gemäß der obigen Ordnung am Ende enthält
  /// @param umgAssociatedPoints Referenz auf Menge von assoziierten Punkten, mit denen die zu den Delaunay Kanten korrespondierenden Kanten 
  /// gefunden werden
  void RNG::sortAssEdges(const Delaunay& dt, std::set<AssEdges>& delaunayEdges, const assPointsSet& umgAssociatedPoints){

    std::transform(dt.finite_edges_begin(), dt.finite_edges_end(), std::inserter(delaunayEdges, delaunayEdges.begin()), 
      [&dt, &umgAssociatedPoints](auto edge)->AssEdges{

        // Lese Punkte der Delauney Triangulation für Eingabemenge aus
        K::Point_3 p1 = dt.segment(edge).point(0);
        K::Point_3 p2 = dt.segment(edge).point(1);

        // Finde diese Punkte in der Menge aller umgekehrt assoziierten Punkte
        auto p1_it = umgAssociatedPoints.find(AssPoints{p1, p1});
        assert(p1_it != umgAssociatedPoints.end());

        auto p2_it = umgAssociatedPoints.find(AssPoints{p2, p2});
        assert(p2_it != umgAssociatedPoints.end());

        // Suche die minimalen, gedrehten Punkte (lexikografisch) und auch die assoziierten Punktee
        K::Point_3 min = (p1_it->p < p2_it->p)? p1_it->p : p2_it->p;
        K::Point_3 max = (p2_it->p < p1_it->p)? p1_it->p : p2_it->p;

        K::Point_3 assMin = (p1_it->p < p2_it->p)? p1_it->associatedPoint : p2_it->associatedPoint;
        K::Point_3 assMax = (p2_it->p < p1_it->p)? p1_it->associatedPoint : p2_it->associatedPoint;

        // Gebe eine Kante von AssPoints zurück, wobei min < min 2 ist und somit die Kanten eine Voraussetzung in angle einhalten
        return {AssPoints{min, assMin}, AssPoints{max, assMax}};
      });
  }



  /// @brief initSearchInT gibt zurück, ob nachfolgend auf- oder absteigend in T gesucht werden soll
  // Außerdem passt es den aktuellen Iterator in T an, falls dieses erlaubt ist. Falls nicht, setzt es den Bool nextPointNotFound auf true
  /// @param actEdge_it Referenz auf Iterator zur aktuell betrachteten Kante. Zu dieser sollen die Punkte zwischen den y-Werten der Punkte in 
  /// auf-, oder absteigender Reihenfolge betrachtet werden
  /// @param actPoint_it Referenz auf Iterator zum aktuellen Element in T. Der Iterator wird gegebenenfalls angepasst
  /// @param nextPointNotFound Referenz auf Boolean wird auf true gesetzt, falls der nächste Wert gefunden wurde
  /// @return Gibt zurück, ob nachfolgend auf- oder absteigend in T gesucht werden soll
  bool RNG::initSearchInT(const std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdge_it, assPointsSet::iterator& actPoint_it, bool& nextPointNotFound){
      
    // Berechne den Nachfolger von p_i in T bzgl. y, wenn y(p_j) > y(p_i), als nächstes Element
    if(actEdge_it->p1.p.y() <= actEdge_it->p2.p.y()){
      if(actPoint_it != T.end()){
        actPoint_it++;
        if(actPoint_it == T.end()){
          nextPointNotFound = true;
        }
      }
      else{
        nextPointNotFound = true;
      }
      return true;
    }
    // Berechne ansonsten den Vorgänger von p_i in T bzgl. y als nächstes Element
    else{
      if(actPoint_it != T.begin()){
        actPoint_it--;
      }
      else{
        // Ansonsten würde ein Dekrementieren von actPoint_it erneut T.begin() ergeben
        nextPointNotFound = true;
      }
      return false;
    }
  }


  /// @brief findAssEdges findet zu einem gegebenen Iterator actEdge_it die assoziierte Kante AssEdges aus der assoziierten Struktur
  /// @param actEdge_it Referenz auf Iterator zur aktuell betrachteten Kante, für die die assozierte Kante gesucht ist
  /// @return liefert die assoziierte Kante zu *actEdge_it zurück
  AssEdges RNG::findAssEdges(const std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdge_it){

    K::Point_3 min = !(actEdge_it->p1.associatedPoint.x() > actEdge_it->p2.associatedPoint.x() || 
          (actEdge_it->p1.associatedPoint.x() == actEdge_it->p2.associatedPoint.x() && actEdge_it->p1.associatedPoint.y() > actEdge_it->p2.associatedPoint.y()))?
          actEdge_it->p1.associatedPoint : actEdge_it->p2.associatedPoint;

    K::Point_3 max = (actEdge_it->p1.associatedPoint.x() > actEdge_it->p2.associatedPoint.x() || 
          (actEdge_it->p1.associatedPoint.x() == actEdge_it->p2.associatedPoint.x() && actEdge_it->p1.associatedPoint.y() > actEdge_it->p2.associatedPoint.y()))?
          actEdge_it->p1.associatedPoint : actEdge_it->p2.associatedPoint;

    AssPoints actAssPointsEdge1{min, min};
    AssPoints actAssPointsEdge2{max, max};

    return AssEdges{actAssPointsEdge1, actAssPointsEdge2};
  }


  /// @brief Lösche die Kante actEdge mit Hilfe des Iterators actEdge_it aus der Adjazenzliste, repräsentiert durch actOrientedAdjList_it.
  /// Dazu wird die Kante aus der aktuellen Adjazenzliste zum Iterator actOrientedAdjList_it gelöscht.
  /// @param actEdge Kopie der zu löschenden Kante
  /// @param actEdge_it Referenz auf Iterator zu der gefundenen zu löschenden Kante. Wegen des Multisets müssen actEdge und *actEdge_it nicht identisch sein
  /// @param actOrientedAdjList_it Referenz auf Iterator zur aktuellen Adjazenzliste aus dem assoziierten Graphen, der die Kante actEdge enthält
  void RNG::deleteAssociatedEdge(AssEdges actEdge, std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdge_it,
    std::set<OrientedAdjList, std::greater<OrientedAdjList>>::iterator& actOrientedAdjList_it){
    
    // Falss die aktuelle assoziierte Kante nicht bereits aus der assoziierten Struktur gelöscht wurde:
    if(actEdge_it != actOrientedAdjList_it->e.end()){

      // Nach der Ordnung der Kanten über den Winkel ist möglich, dass eine Kante gefunden wird, die den gleichen Winkel hat, aber andere Koordinaten
      if(!(actEdge_it->p1.p.x() == actEdge.p1.p.x() && actEdge_it->p1.p.y() == actEdge.p1.p.y() && actEdge_it->p2.p.x() == actEdge.p2.p.x()
        && actEdge_it->p2.p.y() == actEdge.p2.p.y())){

        // actEdge_it ist Iterator zu einer Kante mit dem gleichem Winkel wie actEdge
        AssEdges wrongEdge = *actEdge_it;
        actOrientedAdjList_it->e.erase(actEdge_it);

        // Finde andere Kante mit gleichem Winkel
        auto actEdgeSameAngle = actOrientedAdjList_it->e.find(actEdge);

        // Falls die gesuchte Kante noch nicht in einer vorherigen Ausführung gelöscht wurde
        if(actEdgeSameAngle != actOrientedAdjList_it->e.end()){
          // Lösche gesuchte Kante, die den gleichen Winkel hat
          actOrientedAdjList_it->e.erase(actEdgeSameAngle);
        }

        // Füge die andere Kante wieder ein.
        actOrientedAdjList_it->e.insert(wrongEdge);
      }

      else{
        // Lösche die assoziierte Kante in dem assozierten Graphen
        actOrientedAdjList_it->e.erase(actEdge_it);
      }
    }
  }


  /// @brief nextElementInT berechnet ausgehend vom Iterator actPoint_it zum aktuellen Punkt in T und entsprechend der Suchrichtung forward den nächsten Punkt
  /// in T
  /// @param actPoint_it Referenz auf Iterator zum aktuell betrachteten Element im Baum T
  /// @param forward gibt an, ob auf- oder absteigend in T gesucht werden soll
  /// @return Gibt zurück, ein nächster Punkt in T existiert
  bool RNG::nextElementInT(assPointsSet::iterator& actPoint_it, bool forward){
    if(actPoint_it == T.end()){
      if(!forward){
        // Der Iterator zum aktuellen Punkt war T.end(). Dekrementieren ist erlaubt
        --actPoint_it;
      }
      else{
        //Der aktuelle Punkt war T.end()
        return false; 
      }
    }
    else if(actPoint_it == T.begin()){
      if(forward){
        // Der aktuelle Punkt war T.begin()
        ++actPoint_it;
      }
      else{
        //Der aktuelle Punkt war T.begin(). Dekrementieren ist nicht erlaubt. Das würde den selben Wert liefern.
        return false;
      }
    }
    else{
      // Nach dem Löschen muss nur fortgeschaltet werden, wenn dekrementiert werden soll
      if(!forward){
        --actPoint_it;
      }
    }
    // Ist actPoint_it nach dem Anpassen T.end(), so konnte auch kein neuer Punkt in T gefunden werden
    return actPoint_it != T.end();
  }



  /// @brief Der Konstruktor nimmt die Eingabepunkte entgegen und den Winkel k, um den diese Punkte gedreht werden sollen.
  /// Er dient zur Initialisierung der Eingabepunkte, der nach y-Koordinaten sortierten Baumstruktur T, den rotatedInputPoints und zum Einfügen
  /// aller Delaunay Kanten inklusive der assozierten Delaunay Kanten als AssEdges in die Adjazenzliste.
  /// @param inputPoints Eingabepunkte, zu denen der Relative Nachbarschaftsgraph gesucht ist
  /// @param k Winkel k*60°, um den die Punkte rotiert werden sollen und mit denen gerechnet wird
  RNG::RNG(const std::set<Point> inputPoints, int k):T{yOrder}, rotatedInputPoints{}{

    // Initialisiere cgal Punkte
    for(auto point:inputPoints){
      K::Point_3 p{point.x, point.y, 1};
      input.insert(p);
    }

    // Initialisiere die Drehmatrix mit dem Winkel k*60°
    Transformer transformer{k};

    // Rotiere die Eingabepunkte mit dem Transformer um k*60° und speichere diese in rotatedInputPoints
    rotatePoints(input, transformer, rotatedInputPoints);

    // Sortiere die gedrehten Punkte umgekehrt lexikografisch
    std::sort(rotatedInputPoints.begin(), rotatedInputPoints.end(), std::greater<K::Point_3>());


    // Erzeuge Set von assoziierten Punkten
    assPointsSet associatedPoints{std::less<AssPoints>{}};

    // Initialisiere die Menge von Strukturen aus assoziierten Punkten
    // Ein assoziierter Punkt besteht aus seiner Drehung um k*60° und einem Eingabepunkt
    initAssPoints(transformer, associatedPoints);


    // Erzeuge weiteres Set von assoziierten Punkten, das allerdings nach den associatedPoints der Struktur AssPoints geordnet ist
    assPointsSet umgAssociatedPoints{assOrder};

    // Initialisiere die Menge von Strukturen aus assoziierten Punkten
    initAssPoints(transformer, umgAssociatedPoints);


    // Erstelle für jede Instanz der Struktur associatedPoints eine Adjazenzliste
    for(auto i: associatedPoints){
      struct OrientedAdjList e{i};
      setOfOrientedAdjLists.insert(e);
    }

    // Berechne die Delauney Triangulation zu der Eingabemenge
    Delaunay dt(input.begin(), input.end());

    std::set<AssEdges> delaunayEdges;

    // Sortiere die Delaunaykanten umgekehrt lexikografisch gemäß AssEdges in das Set delaunayEdges ein
    sortAssEdges(dt, delaunayEdges, umgAssociatedPoints);


    // Füge alle Delaunaykanten in die Adjazenzliste ein
    for(auto i: delaunayEdges){

      struct OrientedAdjList ent{i.p1};
      auto it = setOfOrientedAdjLists.find(ent);
      assert(it != setOfOrientedAdjLists.end());
      it->e.insert(i);
    }  
  }



  /// @brief Vorverarbeitungsschritt, Lösche eine Kante aus assGraph, falls ein Punkt aus assGraph existiert, der strikt in der Projektion der Kante liegt
  /// @param assGraph assGraph ist Referenz auf assoziierten Graph, aus dem die korrespondierenden Kanten entfernt werden sollen
  void RNG::eliminateWithProjection(RNG& assGraph){ 

    for(auto orientedAdjList:setOfOrientedAdjLists){
      for(auto setOfEdges_it = orientedAdjList.e.begin(); setOfEdges_it != orientedAdjList.e.end();){

        // Bestimmte die definierenden Punkte und speichere den x- und y-Wert des linken Punktes und den y-Wert der Projektion
        double xCoord = setOfEdges_it->p1.p.x();
        double yCoord = setOfEdges_it->p1.p.y();
        double projection = setOfEdges_it->p2.p.y();

        // Tausche sodass yCoord < projection, um min- und maxBinarySearch passend zur unteren Abfrage zu erhalten
        if(yCoord > projection){
          double temp = yCoord;
          yCoord = projection;
          projection = temp;
        }

        // Falls die Projektion gleich dem ursprünglichen Punkt ist, kann kein Punkt strikt zwischen den beiden liegen
        if(yCoord == projection){
          setOfEdges_it++;
          continue;
        }

        // Führe zwei binäre Suchen auf dem Vektor durch und erhalte zwei Indizes. 
        // Eine für das erste Element, das größer ist als der kleinere y-Wert und eine Index für das Element, das kleiner ist als der größere y-Wert
        int min = minBinarySearch(rotatedInputPoints, xCoord, yCoord);
        int max = maxBinarySearch(rotatedInputPoints, xCoord, projection);

        // ist der Abstand max-min > 3, so existiert ein Punkt, der den gleichen x-Wert hat und zwischen den y-Werten liegt. Markiere die Kante
        // Ist der Abstand max-min == 3, so existiert ein Punkt dazwischen, wenn (x,y) exklusiv oder (x,projection) in rotatedInputPoints liegen
        if(max-min > 3 || (max-min == 3 && !(binarySearch(rotatedInputPoints, xCoord, yCoord) || binarySearch(rotatedInputPoints, xCoord, projection)) )){
          
          // Finde die assoziierte Kante zur aktuellen Kante
          AssEdges actEdge = findAssEdges(setOfEdges_it);

          // Finde die aktuelle Kante in der Menge aller ausgehenden Kanten zum Punkt, um sie löschen zu können
          // Hier kann die falsche Kante gefunden werden, da diese nach dem Winkel sortiert sind und der gleiche zweimal auftreten kann
          struct OrientedAdjList actOrientedAdjList{actEdge.p1};                      
          auto actOrientedAdjList_it = assGraph.setOfOrientedAdjLists.find(actOrientedAdjList);
          assert(actOrientedAdjList_it != assGraph.setOfOrientedAdjLists.end());
          auto actEdge_it = actOrientedAdjList_it->e.find(actEdge);

          // Deshalb nutzt man die Methode deleteAssociatedEdge zum Löschen der aktuellen Kante actEdge
          deleteAssociatedEdge(actEdge, actEdge_it, actOrientedAdjList_it);

          // Lösche die Kante in der aktuellen Struktur
          setOfEdges_it = orientedAdjList.e.erase(setOfEdges_it);
          // Nach dem Löschen muss die Iterator nicht mehr explizit fortgeschaltet werden
        }

        else{
          // Andernfalls muss die aktuelle Kante nicht gelöscht werden
          setOfEdges_it++;
        }

      }
    }
  }


  /// @brief CalculateRNG koordiniert die Berechnung der zu löschenden Kanten für alle 6 Richtungen im Abstand von 60°
  /// Dazu wird die Berechnung für jeden Winkel einmal auf einem temporären Graphen ausgeführt und gleichzeitig die korrespondierenden
  /// Kanten im übergebenen Graphen gelöscht. Nach 6 Iterationen sind alle Richtungen betrachtet worden und die aktuelle Instanz enthält
  /// die gesuchten Kanten des RNGs
  /// @return Instanz der Klasse RNG, die den berechneten RNG durch das Attribut setOfOrientedAdjLists repräsentiert
  RNG RNG::calculateRNG(){

    std::set<Point> inputPoints{};
    for(auto point: input){
      Point p{point.x(), point.y()};
      inputPoints.insert(p);
    }

    // Nutze das aktuelle RNG-Objekt in allen 6 Durchläufen als assoziierten Graphen.
    // So werden alle Löschungen auch in diesem durchgeführt, um entsprechend aller Rotationen die Kanten darin zu löschen
    for(int i=0; i<6; i++){
      // Erzeuge einen RNG zu jedem Winkel im Abstand von 60°
      RNG graph{inputPoints, i};
    
      // Führe eine Vorverarbeitung durch und lösche die assoziierten Kanten im assoziierten Graphen this
      graph.eliminateWithProjection(*this);
    
      // Führe eine Iteration des Algorithmus von Supovit durch. Löschen die korrespondierenden Kanten im assoziierten Graphen this
      graph.calculateRNG(*this);
    }

    std::string filenameRNG(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/Supovit_RNG.txt"});
    std::fstream file_out_RNG;
    file_out_RNG.open(filenameRNG, std::ios_base::out);

    // Gebe alle Punkte und Kanten mit den assoziierten Punkte und Kanten aus
    for(auto i: setOfOrientedAdjLists){
      file_out_RNG << i.p << std::endl;
      for(auto j: i.e){
        file_out_RNG << "(" << j.p1.p.x() << ", " << j.p1.p.y() << "); (" << j.p2.p.x() << ", " << j.p2.p.y() << ")\n";
      }
    }
    return *this;
  }



  /// @brief Führe einen der sechs Schritte des Algorithmus für die aktuell gedrehten Punkte durch.
  /// Lösche dabei auch die korrespondierenden Kanten im assoziierten Graph assGraph
  /// @param assGraph Referenz auf den Graph, in dem die assoziierten Kanten ebenfalls gelöscht werden sollen
  void RNG::calculateRNG(RNG& assGraph){
  
    for(auto orientedAdjList:setOfOrientedAdjLists){

      // Füge die Punkte absteigend nach ihren x-Koordinaten in T ein
      T.insert(orientedAdjList.p);

      // Betrachte nacheinander alle ausgehenden Kante aus orientedAdjList.p in augsteigender Reihenfolge gemäß ihres Winkels (Im Konstruktor geregelt)
      for(auto setOfEdges_it = orientedAdjList.e.begin(); setOfEdges_it != orientedAdjList.e.end();){
      
        // Wird gefunden, da erst oben eingefügt
        auto actPoint_it = T.find(orientedAdjList.p);
        assert(actPoint_it != T.end());

        bool nextPointNotFound = false;

        // Initialisiere die Suche im Baum T. Forward gibt an, ob aufsteigend, oder absteigend gesucht werden soll
        bool forward = initSearchInT(setOfEdges_it, actPoint_it, nextPointNotFound);

        // Wird kein nächster Punkt in T gefunden, so wird die nächste Kante betrachtet
        if(nextPointNotFound){
          setOfEdges_it++;
          continue;
        }

        // Wird dazu benutzt, dass genau einmal setOfEdges_it pro Durchlauf erhöht wird, bzw. richtig angepasst wird, falls diese Kante entfernt wird
        bool edgeItInkremented = false;


        // next ist ein zulässiger Punkt, da actPoint_it != T.end()
        AssPoints next = *(actPoint_it);

        // So lange der y-Wert des nächsten Punktes strikt zwischen denen von p_i und p_j liegt, 
        // prüfe ob die Kanten entfernt oder der Punkt nicht weiter betrachtet werden muss
        while(((setOfEdges_it->p1.p.y() <= next.p.y() && next.p.y() < setOfEdges_it->p2.p.y()) || (setOfEdges_it->p2.p.y() < next.p.y() && next.p.y() <= setOfEdges_it->p1.p.y()))){
          
          // Falls next in lun(p1, p2) ist, lösche Kante (p1,p2) und betrachte die nächste Kante
          if(lune(next, setOfEdges_it->p1, setOfEdges_it->p2)){

            // Finde die assoziierte Kante
            AssEdges actEdge = findAssEdges(setOfEdges_it);

            // Finde den orientedAdjList zur assoziierten Kante im assoziierten Graphen
            struct OrientedAdjList actOrientedAdjList{actEdge.p1};         
            auto actOrientedAdjList_it = assGraph.setOfOrientedAdjLists.find(actOrientedAdjList);
            assert(actOrientedAdjList_it != assGraph.setOfOrientedAdjLists.end());

            // Finde die assoziierte Kante in der Liste der Kanten zum assoziierten orientedAdjList, wenn vorhanden
            auto actEdge_it = actOrientedAdjList_it->e.find(actEdge);

            // Lösche die assoziierte Kante aus der assoziierten Struktur
            deleteAssociatedEdge(actEdge, actEdge_it, actOrientedAdjList_it);             

            // Lösche die Kante aus der aktuellen Struktur
            setOfEdges_it = orientedAdjList.e.erase(setOfEdges_it);

            // setOfEdges_it wurde nach der Löschung des alten Eintrages auf den nächsten Eintrag gesetzt
            edgeItInkremented = true;
            break;
          }

          // Lösche andernfalls den Punkt next aus T und wähle den nächsten Punkt aus, prüfe dabei, ob dieser != T.end() ist
          else{

            // Lösche Punkt v aus T
            actPoint_it = T.erase(actPoint_it);

            // Schalte actPoint_it fort. Wegen des Löschens wird actPoint_it!=T.end() zu Beginn erneut überprüft
            bool nextPointFound = nextElementInT(actPoint_it, forward);

            // Wird kein nächster Punkt gefunden, ist die Betrachtung für die aktuelle Kante zuende
            if(!nextPointFound){break;}

            // Aktualisiere andernfalls den nächsten Wert in T
            next = *(actPoint_it);

          }
        }

        // Schalte setOfEdges_it fort, wenn dieser noch nicht fortgeschaltet wurde
        if(!edgeItInkremented){
          setOfEdges_it++;
        }
      }
    }
  }


  /// @brief Berechnet aus den Adjazenzlisten zur Repräsentation eines RNGs eine Repräsentation über alle Kanten des RNG mithilfe von Adjazenzlisten, die
  /// nicht über CGAL-Punkte definiert sind
  /// @return gericheteter Graph zur Repräsentation des ungerichteten RNGs
  Graph RNG::createUndirectedGraph(){
    Graph G{};

    // Erzeuge die Liste von Kanten zu allen assoziierten/ursprünglichen Punkten der entries
    for(auto orientedAdjList: setOfOrientedAdjLists){
      AssPoints assP = orientedAdjList.p;
      Point p{assP.associatedPoint.x(), assP.associatedPoint.y()};
      G.setOfAdjLists.insert(AdjList{p});
    }

    // Kopiere alle Kanten aus dem RNG nach G
    for(auto orientedAdjList: setOfOrientedAdjLists){
      for(auto edge: orientedAdjList.e){
        AssPoints assPBegin = edge.p1;
        AssPoints assPEnd = edge.p2;
        Point p1{assPEnd.associatedPoint.x(), assPEnd.associatedPoint.y()};
        Point p2{assPBegin.associatedPoint.x(), assPBegin.associatedPoint.y()};

        auto it = G.setOfAdjLists.find(p1);
        assert(it != G.setOfAdjLists.end());
        it->e.insert(Edge{p1,p2});
        
        it = G.setOfAdjLists.find(p2);
        assert(it != G.setOfAdjLists.end());
        it->e.insert(Edge{p2,p1});
      }
    }
    return G;
  }


  /// @brief Naiver Algorithmus zur Berechnung eines RNGs. Berechne RNG in Laufzeit von O(n²)
  void RNG::calculateRNGTrivial(){

    // Für jede Kante überprüfen, ob ein Punkt diese destruiert
    for(auto &orientedAdjList:setOfOrientedAdjLists){
      for(auto edge=orientedAdjList.e.begin(); edge != orientedAdjList.e.end();){
        bool inside = false;
        for(auto orientedAdjList1:setOfOrientedAdjLists){
          // Falls der aktuelle Punkt ungleich einem Eckpunkt ist
          if((!(orientedAdjList1.p.p.x() == edge->p1.p.x() && orientedAdjList1.p.p.y() == edge->p1.p.y())) && (!(orientedAdjList1.p.p.x() == edge->p2.p.x() && orientedAdjList1.p.p.y() == edge->p2.p.y()))){
            if(lune(orientedAdjList1.p, edge->p1, edge->p2)){
              inside = true;
              edge = orientedAdjList.e.erase(edge);
              break;
            }
          }
        }
        if(!inside){
          edge++;
        }
      }
    }
  }