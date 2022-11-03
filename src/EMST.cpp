#include "EMST.hpp"


  /// @brief Initialisiere und öffne die Dateien zur Speicherung der Delaunay Triangulation, des RNGs, des EMSTs und ggfs. der anderen Hilfsstrukturen
  void EMST::openFiles(){

    std::string filenameDelaunay(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/Delaunay_Triangulation.txt"});
    file_out_Delaunay.open(filenameDelaunay, std::ios_base::out);
    if(!file_out_Delaunay.is_open()){
      std::cerr << "Exception: failed to open " << filenameDelaunay << "\n";
      exit(-1);
    }

    std::string filenameRNG(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/Relativer_Nachbarschaftsgraph.txt"});
    file_out_RNG.open(filenameRNG, std::ios_base::out);
    if(!file_out_RNG.is_open()){
      std::cerr << "Exception: failed to open " << filenameRNG << "\n";
      exit(-1);
    }

    std::string filename(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/Euklidischer_Minimaler_Spannbaum.txt"});
    file_out_EMST.open(filename, std::ios_base::out);
    if(!file_out_EMST.is_open()){
      std::cerr << "Exception: failed to open " << filename << "\n";
      exit(-1);
    }

    #if WRITE_INTO_ALL_FILES == 1
    std::string filenameG(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/Hilfsgraph_G.txt"});
    file_out_G.open(filenameG, std::ios_base::out);
    if(!file_out_G.is_open()){
      std::cerr << "Exception: failed to open " << filenameG << "\n";
      exit(-1);
    }

    std::string filenameFaceCyclesG(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/face_cycles_G.txt"});
    file_out_Face_Cycles_G.open(filenameFaceCyclesG, std::ios_base::out);
    if(!file_out_Face_Cycles_G.is_open()){
      std::cerr << "Exception: failed to open " << filenameFaceCyclesG << "\n";
      exit(-1);
    }

    std::string filenameSNet(ROOTPATH + std::string{"data/Aktuelle_Ergebnisse/s-Netz.txt"});
    file_out_SNet.open(filenameSNet, std::ios_base::out);
    if(!file_out_SNet.is_open()){
      std::cerr << "Exception: failed to open " << filenameSNet << "\n";
      exit(-1);
    }
    #endif
  }


  /// @brief Gebe für alle Punkte aus der Menge Q alle adjazenten Punkte (Nachbarn) im Graphen G zurück
  /// @param Q Menge aller Punkte, zu der die Nachbarn im Graphen G gesucht sind
  /// @param G Graph G, der mit Adjazenzlisten repräsentiert wird
  /// @return eine Menge von Punkten in G, die adjazent zu Punkten aus Q sind
  std::set<Point> EMST::calcNeighbors(const std::set<Point>& Q, const Graph& G){
    std::set<Point> neighbors{};

    for(auto points:Q){
      auto it = G.setOfAdjLists.find(points);
      assert(it != G.setOfAdjLists.end());
      for(auto edge:it->e){
        neighbors.insert(edge.head);
      }
    }

    return neighbors;
  }


  /// @brief Lese aus dem Graphen G alle Kanten aus, zu denen Punkt(e) aus potEdges inzident sind und speichere diese in potEdges
  /// @param G Graph G, der mit Adjazenzlisten gespeichert wird
  /// @param potEdges Menge an Adjazenzlisten zu einer Teilmenge von Punkten aus G aus dem RNG
  void EMST::calcPotEdges(const Graph& G, std::set<struct AdjList>& potEdges){

    for(auto& adjList:potEdges){
      auto it = G.setOfAdjLists.find(adjList.p);
      assert(it != G.setOfAdjLists.end());
      adjList.e.insert(it->e.begin(), it->e.end());
    }
  }



  /// @brief Gibt ein Set von Punkten aus G zurück, die adjazent zu Punkten, die eine Adjazenzliste in potEdges definieren, sind
  /// Dabei werden alle Kanten aus den Adjazenzlisten von potEdges gelöscht, die nicht mehr in G vorkommen
  /// @param G Graph G, der mit Adjazenzlisten repräsentiert wird
  /// @param potEdges Menge an Adjazenzlisten zu einer Teilmenge von Punkten aus G aus dem RNG
  /// @return Menge mit allen Punkten aus G, die adjazent zu den Punkten aus potEdges sind
  std::set<Point> EMST::calcRemainingNeighbors(const Graph& G, std::set<struct AdjList>& potEdges){
    std::set<Point> neighbors{};

    // Lösche die Kanten aus potEdges, die nicht mehr im Graphen sind. Kanten, die in G sind, aber nicht in potEdges, werden ignoriert
    for(auto& adjList:potEdges){
      auto adjList_it = G.setOfAdjLists.find(adjList.p);
      assert(adjList_it != G.setOfAdjLists.end());

      for(auto edgePotEdges_it = adjList.e.begin(); edgePotEdges_it != adjList.e.end();){
        auto edgeG_it = adjList_it->e.find(*edgePotEdges_it);
        
        if(edgeG_it == adjList_it->e.end()){
          edgePotEdges_it = adjList.e.erase(edgePotEdges_it);
        }

        else{
          edgePotEdges_it++;
        }
      }
    }

    // Schreibe alle zu Punkten aus potEdges adjazenten Punkte aus G
    for(auto& adjList:potEdges){
      auto adjList_it = G.setOfAdjLists.find(adjList.p);
      assert(adjList_it != G.setOfAdjLists.end());
      for(auto& edge:adjList_it->e){
        neighbors.insert(edge.head);
      }
    }

    return neighbors;
  }


  /// @brief Gebe zu jedem Punkt aus subset alle adjazenten Punkte im RNG, durch potEdges repräsentiert, zurück
  /// @param potEdges Menge an Adjazenzlisten zu einer Teilmenge von Punkten aus G aus dem RNG
  /// @param subset Menge an Punkten, zu denen alle adjazenten Punkte im RNG gesucht sind
  /// @return Vektor von Vektoren, der zu jedem Punkt aus subset alle adjazenten Punkte des RNGs enthält
  std::vector<std::vector<Point>> EMST::extractAllNeighbors(const std::set<struct AdjList>& potEdges, const std::vector<Point>& subset){

    std::vector<std::vector<Point>> result(subset.size());

    int j = 0;
    for(auto point:subset){
      struct AdjList set{point};
      auto it = potEdges.find(set);
      assert(it != potEdges.end());

      std::vector<Point> temp(it->e.size());
      int i = 0;
      for(auto edge:it->e){
        temp[i] = edge.head;
        i++;
      }
      result[j] = temp;
      j++;
    }
    return result;
  }



  /// @brief Berechnet für jeden Punkt des subsets alle adjazenten Punkte im RNG(S)
  /// @param S Eingabepunktmenge
  /// @param subset Teilmenge von S
  /// @return Vektor, der zu jedem Punkt q des subsets einen Vektor mit allen Punkten aus S enthält, die adjazent zu q im RNG(S) sind
  std::vector<std::vector<Point>> EMST::calcAdjacentPointsInRNG(const std::vector<Point>& S, const std::vector<Point>& subset){
    std::vector<std::vector<Point>> result{};

    // Definiere Punktmenge Q, zu der alle Kanten (p_i, p_j), wobei p_i oder p_j aus subset kommt, im RNG(S) gefunden werden sollen
    std::set<Point> Q{};

    // Zu jedem p aus Q werden zunächst alle potenziellen Kanten berechnet und anschließend die überflüssigen gelöscht
    std::set<struct AdjList> potEdges{};

    // Initialisiere Q und potEdges
    for(auto point:subset){
      Q.insert(point);
      potEdges.insert(AdjList{point});
    }

    /*    
    // Schritt 1: Berechne alle potenziellen Nachbarn von Q in RNG(S)
    */

    // Wird immer initialisiert, da S.size() >=1 ist, und somit eine Iteration durchgeführt wird
    Graph G;
    std::set<Point> N{};

    for(int j = 0; j < ceil(S.size()/s); j++){

      // R_j := {S[j*s], ..., S[(j+1)*s-1]}
      std::set<Point> R{};

      int boundary = (j < ceil(S.size()/s)-1) ? (j+1)*s : S.size();

      R.insert(S.begin()+j*s, S.begin()+boundary);


      // P_j := Q vereinigt R_j vereinigt N_{j-1}
      std::set<Point> P = unionOfSets(Q, R, N);

      // RNG_j := RNG(P_j)
      G = RNG{P, 0}.calculateRNG().createUndirectedGraph();

      // N_j := neighbors(Q, RNG_j)
      N = calcNeighbors(Q, G);
    }

    // Speichere die verbleibenden potenziellen Kanten in potEdges
    calcPotEdges(G, potEdges);


    /*
    // Schritt 2: Berechne die tatsächlichen Nachbarn aller Punkte aus Q in RNG(S)
    */

    for(int j = 0; j < ceil(S.size()/s); j++){

      // R'_j := {S[j*s], ..., S[(j+1)*s-1]}
      std::set<Point> R{};

      int boundary = (j < ceil(S.size()/s)-1) ? (j+1)*s : S.size();
      
      R.insert(S.begin()+j*s, S.begin()+boundary);

      // P'_j := Q vereinigt R'_j vereinigt N_{ceil(n/s)-1}, bzw. N'_j
      std::set<Point> P = unionOfSets(Q, R, N);

      // RNG'_j := RNG(P'_j)
      G = RNG{P, 0}.calculateRNG().createUndirectedGraph();

      // N'_j := neighbors(Q, RNG'_j)
      N = calcRemainingNeighbors(G, potEdges);
    }

    result = extractAllNeighbors(potEdges, subset);
    return result;
  }


  /// @brief Berechne für alle Elemente aus {S[first],..., S[last-1]} der Eingabemenge S alle Kanten (p_i, p_j), die zum RNG(S) gehören, 
  /// wobei p_i < p_j und p_i aus {S[first],..., S[last-1]} kommt, also inzident zu diesen ist. Das erspart später Arbeit bei der Betrachtung der Kanten,
  /// da keine entgegengesetzten Kanten separat betrachtet werden müssen.
  /// @param S Eingabepunktmenge S
  /// @param first Index, um das Element S[first] zu finden
  /// @param last Index, um das Element S[last] zu finden
  /// @return alle Kanten (p_i, p_j) des RNGs mit p_i < p_j und p_i kommt aus der Menge {S[first],..., S[last-1]}
  std::vector<Edge> EMST::calcBatchOfEdges(const std::vector<Point>& S, int first, int last){
    
    std::vector<Edge> result{};

    std::vector<Point> subset{S.begin()+first, S.begin()+(last+1)};

    // Berechne alle adjazenten Punkte im RNG(S) für jeden Punkt des subsets
    std::vector<std::vector<Point>> neighborsOfPointsInSubset = calcAdjacentPointsInRNG(S, subset);

    // Gebe alle Kanten der Form (S[i], p_j) aus, wobei S[i] < p_j ist
    for(unsigned int i=0; i<neighborsOfPointsInSubset.size(); i++){
      Point p{subset[i].x, subset[i].y};
      for(unsigned int j=0; j<neighborsOfPointsInSubset[i].size(); j++){
        if(p < neighborsOfPointsInSubset[i][j]){
          Edge e{p, neighborsOfPointsInSubset[i][j]};
          result.push_back(e);
        }
      }
    }
    return result;
  }

  

  /// @brief Berechnet die s nächstgrößeren Kanten des RNGs zu der Eingabepunktmenge S in aufsteigender Reihenfolge, die länger als die Kante upperLength sind
  /// @param S Eingabepunktmenge
  /// @param upperLength Die Länge der längsten Kante des vorherigen RNG_i
  /// @param s Anzahl an weiteren, zu findenden Kanten aus dem RNG
  /// @return Vektor der die s größten Kanten des RNG_i+s in aufsteigender Reihenfolge enthält
  std::vector<Edge> EMST::calcBatchOfSortedEdges(const std::vector<Point>& S, double upperLength){

    std::vector<Edge> result{};
    result.reserve(s);

    for(int i=0; i < ceil(S.size()/s); i++){

      // Enthält alle Kanten (p_i,p_j) des RNGs, wobei p_i < p_j und p_i aus {S[i*s],..., S[(i+1)*s-1]} kommt
      std::vector<Edge> actEdges{};

      int boundary = (i < ceil(S.size()/s)-1) ? (i+1)*s-1 : S.size()-1;

      // Berechne alle wie zuvor beschriebenen Kanten des RNGs zu denen ein Punkt aus {S[i*s],..., boundary} inzident ist
      actEdges = calcBatchOfEdges(S, i*s, boundary);
      

      // potEdges enthält alle Kanten aus actEdges, die länger als die längste Kante des vorherigen RNG_i sind
      std::vector<Edge> potEdges = chooseLongerEdges(actEdges, upperLength);

      // Sind noch mindestens potEdges.size() freie Einträge in dem Ausgabevektor vorhanden, füge alle potenziellen Kanten ein
      if(static_cast<int>(result.size() + potEdges.size()) <= s){
        result.insert(result.end(), potEdges.begin(), potEdges.end());
      }
      
      // Sind keine potEdges.size() freien Einträge in dem Ausgabevektor vorhanden, müssen aus actEdges und potEdges die s kürzesten ausgewählt werden
      else{
        std::vector<Edge> temp{};

        // Füge die verbliebenen potenziellen Kanten aus der letzten Iteration ein
        temp.insert(temp.end(), result.begin(), result.end());

        // Füge die neuen potenziellen Kanten ein
        temp.insert(temp.end(), potEdges.begin(), potEdges.end());

        // Finde das s-tgrößte Element in temp und berechne dessen Länge
        Edge sElement = selectKthElement(temp, s);
        double length = sElement.calcLength();

        // Füge alle Kanten ein, deren Länge kleiner gleich der Länge des s-ten Elements sind
        result.resize(0);
        for(unsigned int j=0; j < temp.size(); j++){
          if(temp[j].calcLength() <= length){
            result.push_back(temp[j]);
          }
        }
      }
    }

    // Sortiere die Kanten in dem Ausgabearray nach ihrer Länge
    std::sort(result.begin(), result.end());

    // Schreibe die bis zu s Kanten des RNGs in eine Datei
    for(auto &edge: result){
      file_out_RNG << edge << std::endl;
    }

    return result;
  }



  /// @brief calculateH berechnet eine Menge von Kanten, die die Kanten des S-Netzes und die nachfolgenden Kanten der batchEdges im aktuellen RNG_i enthält
  /// @param inputPoints Eingabepunktmenge
  /// @param sNet S-Netz, das den aktuellen RNG_i(inputPoints) repräsentiert
  /// @param batchEdges Menge von Kanten des RNG_i+s, die später eingefügt werden sollen
  /// @param upperLength Länge der längsten Kante des RNG_i(S)
  /// @return Vektor von Kanten des S-Netzes und der Nachfolger der batch edges
  std::vector<Edge> EMST::calculateH(const std::vector<Point>& inputPoints, const std::vector<Edge>& sNet, const std::vector<Edge>& batchEdges, double upperLength){

    // Füge alle Kanten aus dem S-Netz in H ein
    std::vector<Edge> hStructure{sNet};

    std::vector<Point> endpointsOfBatchEdges{};

    // Füge alle Endpunkte der batch edges in endpointsOfbatchEdges ein
    for(auto& e:batchEdges){
      endpointsOfBatchEdges.push_back(e.head);
      endpointsOfBatchEdges.push_back(e.tail);
    }

    // Berechne alle Nachbarn von Punkten aus endpointsOfbatchEdges
    std::vector<std::vector<Point>> neighbors = calcAdjacentPointsInRNG(inputPoints, endpointsOfBatchEdges);

    // Füge für alle batch edges die nachfolgenden Kanten ein, die im RNG_i(inputPoints) enthalten sind
    int count = 0;
    for(auto& edge: batchEdges){
      Edge succ1 = succEdge(upperLength, edge, neighbors[count]);
      if(isValidEdge(succ1)){
        hStructure.push_back(succ1);
      }
      count++;

      Edge opposite{edge.head, edge.tail};
      Edge succ2 = succEdge(upperLength, opposite, neighbors[count]);
      if(isValidEdge(succ2)){  
        hStructure.push_back(succ2);
      }
      count++;
    }

    return hStructure;
  }


  /// @brief Berechnet mit Hilfe einer binären Suche, ob die Kante e in der Repräsentation des Hilfsgraphen H enthalten ist
  /// @param e gesuchte Kante
  /// @param H Vektor von Kanten, die H repräsentieren
  /// @return Gibt zurück, ob e im Vektor H ist
  bool EMST::edgeIsHEdge(const Edge& e, const std::vector<Edge>& H){

    int low = 0;
    int high = H.size()-1;

    while(low <= high){
      int mid = low + (high -low)/2;

      if(e == H[mid]){
        return true;
      }
      else if(e > H[mid]){
        low = mid + 1;
      }
      else{
        high = mid - 1;
      }
    }

    return false;
  }


  /// @brief Berechnet den Hilfsgraphen G, der den aktuellen RNG_i kompakt mit O(s) Speicher repräsentiert
  /// @param inputPoints Eingabepunktmenge, zu der der EMST gesucht ist
  /// @param H Menge an relevanten Kanten zur Erstellung von G
  /// @param batchEdges Vektor mit den in den RNG_i einzufügenden batch edges
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return Hilfsgraph G
  Graph EMST::calculateG(const std::vector<Point>& inputPoints, const std::vector<Edge>& H, const std::vector<Edge>& batchEdges, double upperLength){

    Graph G{};

    // Füge alle Punkte und Kanten aus H in G ein
    for(auto& edge:H){
      G.setOfAdjLists.insert(edge.tail);
      G.setOfAdjLists.insert(edge.head);
      auto it = G.setOfAdjLists.find(edge.tail);
      assert(it!=G.setOfAdjLists.end());
      it->e.insert(edge);
    }

    // Füge alle Ednpunkte der batch edges ein, die oben nicht einsortiert wurden, da sie keine Nachfolgerkante definiert hatten
    for(auto& edge:batchEdges){
      G.setOfAdjLists.insert(edge.tail);
      G.setOfAdjLists.insert(edge.head);
    }

    // Sortiere die Kanten aus H bezüglich ihrer Länge, um in edgeIsHEdge eine binäre Suche zu ermöglichen.
    // Mache das für eine Kopie von H, da dessen Sortierung erhalten bleiben soll
    std::vector<Edge> sortedH = H;
    std::sort(sortedH.begin(), sortedH.end());

    /*
      Performe parallel walks für jede Kante aus H und passe G an
    */

    // finishedWalk beinhaltet zu jedem Endpunkt einer Kante aus H einen Boolean, um zu schauen, wann die parallelen Läufe vorbei sind
    std::vector<bool> finishedWalk{};

    // Speichere alle Heads der zuletzt betrachteten Kanten aus H in headPreviousEdges, um alle Nachfolgerkanten zu berechnen
    std::vector<Point> headPreviousEdges{};

    // Speicher alle Heads der als nächstes betrachteten Kanten in headNextEdges ab
    std::vector<Point> headNextEdges(H.size());

    // previous edges enthält alle vorherigen Kanten
    std::vector<Edge> previousEdges = H;

    // Initialisiere die Knoten, von denen initial die Walks losgehen, also die ausgehenden Kanten betrachtet werden
    for(auto& e:H){
      headPreviousEdges.push_back(e.head);
      finishedWalk.push_back(false);
    }


    // Berechne alle Nachbarn zu den Knoten aus headPreviousEdges im RNG, wobei die Sortierung der Knoten in calcAdjacentPointsInRNG erhalten bleibt
    std::vector<std::vector<Point>> neighbors = calcAdjacentPointsInRNG(inputPoints, headPreviousEdges);


    // Berechne der Reihe nach alle Nachfolger der Punkte aus headPreviousEdges
    for(long unsigned int pos=0; pos < headPreviousEdges.size(); pos++){
      Edge succ = nextEdge(upperLength, previousEdges[pos], neighbors[pos]);

      // Wenn 0 Kante eingefügt wird, wird der entsprechende Boolean auf true gesetzt und headNextEdges bleibt der alte Knoten, 
      // setze Kante später nicht neu, damit bereits beendete Läufe durch die Länge 0 der Kante (headPrevEdge, headNextEdges) abgefangen werden
      if(!isValidEdge(succ)){
        finishedWalk[pos] = true;
        headNextEdges[pos] = headPreviousEdges[pos];
      }
      else{
        headNextEdges[pos] = succ.head;
      }
    }


    // Prüfe, ob die sich ergebenden Kanten in H liegen, falls ja, setze den boolean auf true und füge für laenge > 0 eine Kanten von Q zu predecessor Point mit der Länge count ein
    for(long unsigned int pos = 0; pos < headNextEdges.size(); pos++){
      
      Edge e{headPreviousEdges[pos], headNextEdges[pos]};

      // Für den initialen Fall müssen noch keine compressed Edges in G eingefügt werden, da laenge = 0 ist. Es muss nur previous und next angepasst werden
      if(edgeIsHEdge(e, sortedH) && finishedWalk[pos]==false){
        finishedWalk[pos] = 1;
        
        // Suche die vorherige H-Edge in G
        auto prevSetOfEdges_it = G.setOfAdjLists.find(AdjList(previousEdges[pos].tail));
        assert(prevSetOfEdges_it != G.setOfAdjLists.end());
        auto prevEdge_it = prevSetOfEdges_it->e.find(previousEdges[pos]);
        assert(prevEdge_it != prevSetOfEdges_it->e.end());

        // Suche die erreichte H-Kante in G
        auto actualSetOfEdges_it = G.setOfAdjLists.find(AdjList(e.tail));
        assert(actualSetOfEdges_it != G.setOfAdjLists.end());
        auto actualEdge_it = actualSetOfEdges_it->e.find(e);
        assert(actualEdge_it != actualSetOfEdges_it->e.end());

        // Passe next von vorheriger Kante und previous von gefundener Kante an
        prevEdge_it->next = &(*actualEdge_it);
        actualEdge_it->previous = &(*prevEdge_it);
      }
      // Passe die previousEdge und die headPreviousEdges an, falls die neue Kante valide war. In for-Schleife darüber wird der alte Wert erneut gesetzt
      // Damit ist die Länge 0 und man weiß, dass die Kante keine Rolle mehr spielt
      if(isValidEdge(e)){
        previousEdges[pos] = e;
        headPreviousEdges[pos] = headNextEdges[pos];
      }
    }

    /*
      Nun werden compressed Edges (der Länge laenge) eingefügt
    */

    int laenge = 1;

    // So lange nicht alle Walks eine H-Edge erreicht haben, laufe weiter
    while(std::find(finishedWalk.begin(), finishedWalk.end(),false) != finishedWalk.end()){

      // Berechne alle Nachbarn von headPreviousEdges
      neighbors = calcAdjacentPointsInRNG(inputPoints, headPreviousEdges);

      // Berechne der Reihe nach alle Nachfolger der Punkte aus headPreviousEdges
      for(long unsigned int pos = 0; pos < headPreviousEdges.size(); pos++){
        Edge succ = nextEdge(upperLength, previousEdges[pos], neighbors[pos]);

        // Wenn 0 Kante eingefügt wird, wird der entsprechende Boolean auf true gesetzt und headNextEdges bleibt der alte Knoten
        if(!isValidEdge(succ)){
          finishedWalk[pos] = true;
          headNextEdges[pos] = headPreviousEdges[pos];
        }
        else{
          headNextEdges[pos] = succ.head;
        }
      }

      // Prüfe, ob die sich ergebenden Kanten in H liegen, falls ja, setze den boolean auf true und füge für laenge > 0 eine Kanten von dem head der initialen H-Edge
      // zum Head der vorherigen Kante (headNextEdges wurde zu dem Zeitpunkt noch nicht aktualisiert) mit der Länge count ein
      for(long unsigned int pos = 0; pos < headNextEdges.size(); pos++){

        Edge e{headPreviousEdges[pos], headNextEdges[pos]};

        if(edgeIsHEdge(e, sortedH) && finishedWalk[pos]==false){

          finishedWalk[pos] = 1;

          // Da laenge > 0 ist, muss nun eine compressed Edge der Länge laenge in G eingefügt werden. Für laenge=1 ist dies eine gewöhnliche Kante
          auto comprSetOfEdges_it = G.setOfAdjLists.find(H[pos].head);
          assert(comprSetOfEdges_it != G.setOfAdjLists.end());
          Edge comprEdge{H[pos].head, Point{headPreviousEdges[pos].x, headPreviousEdges[pos].y}, laenge};
          
          // Prüfe, ob das Element schon vorhanden ist und modifiziere die Kante ggfs, so wird ein Multiset mit maximaler Größe von 2 pro Knoten simuliert!
          auto comprEdge_it = comprSetOfEdges_it->e.find(comprEdge);
          if(comprEdge_it == comprSetOfEdges_it->e.end()){
            comprSetOfEdges_it->e.insert(comprEdge);
          }
          else if(*comprEdge_it->previous == H[pos]){
            comprSetOfEdges_it->e.insert(comprEdge);
          }
          else{
            comprEdge = Edge{H[pos].head, Point{headPreviousEdges[pos].x, headPreviousEdges[pos].y}, laenge, 1};
            comprSetOfEdges_it->e.insert(comprEdge);
          }
          
          // Suche Iterator, der auf die eingefügte compressedEdge zeigt
          comprEdge_it = comprSetOfEdges_it->e.find(comprEdge);
          assert(comprEdge_it != comprSetOfEdges_it->e.end());

          // Suche Iterator, der auf die ausgehende H-Edge in G zeigt
          auto prevSetOfEdges_it = G.setOfAdjLists.find(AdjList(H[pos].tail));
          assert(prevSetOfEdges_it != G.setOfAdjLists.end());
          auto prevEdge_it = prevSetOfEdges_it->e.find(H[pos]);
          assert(prevEdge_it != prevSetOfEdges_it->e.end());

          // Suche Iterator, der auf die gefundene H-Edge in G zeigt
          auto actualSetOfEdges_it = G.setOfAdjLists.find(AdjList(e.tail));
          assert(actualSetOfEdges_it != G.setOfAdjLists.end());
          auto actualEdge_it = actualSetOfEdges_it->e.find(e);
          assert(actualEdge_it != actualSetOfEdges_it->e.end());

          // Passe next von der initialen H-Edge an
          prevEdge_it->next = &(*comprEdge_it);

          // Passe previous von der gefundenen H-Edge an
          actualEdge_it->previous = &(*comprEdge_it);

          // Passe previous und next von der eingefügten compressedEdge an
          comprEdge_it->previous = &(*prevEdge_it);
          comprEdge_it->next = &(*actualEdge_it);
        }
        // Passe previousEdges und headPreviousEdges an, falls die neue Kante valide war
        if(isValidEdge(e)){
          previousEdges[pos] = e;
          headPreviousEdges[pos] = headNextEdges[pos];
        }
      }
      laenge++;
    }

    return G;
  }

  /// @brief Schreibe den Hilfsgraphen G in eine Datei
  /// @param G Hilfsgraph G
  void EMST::writeGToFile(Graph& G){
    for(auto& adjList: G.setOfAdjLists){
      file_out_G << adjList.p << std::endl;
      for(auto& edge: adjList.e){
        file_out_G << edge << " ; komprimierteLänge: " << edge.comprLength << " ; " << edge.again << std::endl;
      }
    }
  }

  /// @brief Schreibe alle face-cycles des Hilfsgraphen G in eine Datei
  /// @param G Hilfsgraph G
  void EMST::writeFaceCyclesOfGToFile(Graph& G){
    int i = 0;
    for(auto& point: G.setOfAdjLists){
      for(auto& edge: point.e){
        if(!edge.visited){
          file_out_Face_Cycles_G << "Face-Cycle " << i << " : " << std::endl;
          file_out_Face_Cycles_G << edge << " ; komprimierteLänge: " << edge.comprLength << " ; " << edge.again << std::endl;
          edge.visited = true;
          auto next = edge.next;
          while(!(next->tail == edge.tail && next->head == edge.head)){
            file_out_Face_Cycles_G << *next << " ; komprimierteLänge: " << next->comprLength << " ; " << next->again << std::endl;
            next->visited = true;
            next = next->next;
          }
          i++;
        }
      }
    }
  }
  
  /// @brief Fügt die Kante batchEdge über zwei gerichtete Kanten in G ein, sodass die Face-Cycles korrekt angepasst werden
  /// @param G Hilfsgraph G, in den die Batch Edge eingefügt wird
  /// @param batchEdge k-te Kante der einzufügenden Batch Edges. Diese wird in den RNG_i+k eingefügt
  /// @param neighborsP1 alle Nachbarn des heads der Batch Edge im RNG
  /// @param neighborsP2 alle Nachbarn des tails der Batch Edge im RNG
  /// @param upperLength Länge der längsten Kante von RNG_i+k, wobei RNG_i der aktuelle Graph ist und bereits k-1 batchEdges eingefügt wurden
  void EMST::insertBatchEdge(Graph& G, const Edge& batchEdge, const std::vector<Point>& neighborsP1, const std::vector<Point>& neighborsP2, double upperLength){

    // Suche für beide Halbkanten die Nachfolger in RNG_i
    Edge sucHalfEdge = succEdge(upperLength, batchEdge, neighborsP1);
    Edge sucOppositeHalfEdge = succEdge(upperLength, Edge{batchEdge.head, batchEdge.tail}, neighborsP2);

    // Füge die zwei Halbkanten in G ein und suche die eingefügten Halbkanten, die angepasst werden müssen
    auto adjList_it = G.setOfAdjLists.find(batchEdge.tail);
    assert(adjList_it!=G.setOfAdjLists.end());
    adjList_it->e.insert(batchEdge);
    auto batchEdge_it = adjList_it->e.find(batchEdge);

    adjList_it = G.setOfAdjLists.find(batchEdge.head);
    assert(adjList_it!=G.setOfAdjLists.end());
    adjList_it->e.insert(Edge{batchEdge.head, batchEdge.tail});
    auto oppBatchEdge_it = adjList_it->e.find(Edge{batchEdge.head, batchEdge.tail});


    // Passe die Vorgänger und Nachfolger der eingefügten und ggfs. vorherigen und/oder nachfolgenden Kanten ein


    // Fall 1. Beide Halbkanten haben keinen Nachfolger in RNG_i. Damit ist die andere Halbkante jeweil Vor- und Nachgänger der einen Halbkante.
    if(!isValidEdge(sucHalfEdge) && !isValidEdge(sucOppositeHalfEdge)){

      batchEdge_it->previous = &(*oppBatchEdge_it);
      batchEdge_it->next = &(*oppBatchEdge_it);
      oppBatchEdge_it->previous = &(*batchEdge_it);
      oppBatchEdge_it->next = &(*batchEdge_it);
    }
    
    // Fall 2. Die erste Halbkante hat keinen Nachfolger in RNG_i und die andere schon. Berechne 
    else if(!isValidEdge(sucHalfEdge)){

      // Finde den Nachfolger und Vogänger der entgegengesetzten Halbkante in RNG_i+k
      adjList_it = G.setOfAdjLists.find(sucOppositeHalfEdge.tail);
      assert(adjList_it != G.setOfAdjLists.end());
      auto sucOppEdge_it = adjList_it->e.find(sucOppositeHalfEdge);
      assert(sucOppEdge_it != adjList_it->e.end());
      auto prevOppEdge_it = sucOppEdge_it->previous;

      prevOppEdge_it->next = &(*batchEdge_it);
      batchEdge_it->previous = prevOppEdge_it;
      batchEdge_it->next = &(*oppBatchEdge_it);
      oppBatchEdge_it->previous = &(*batchEdge_it);
      oppBatchEdge_it->next = &(*sucOppEdge_it);
      sucOppEdge_it->previous = &(*oppBatchEdge_it);
    }

    // Fall 3. Die andere Halbkante hat keinen Nachfolger in RNG_i. Gehe ähnlich wie in Fall 2 vor.
    else if(!isValidEdge(sucOppositeHalfEdge)){

      // Finde den Nachfolger und Vorgänger von der batchEdge in RNG_i+k
      adjList_it = G.setOfAdjLists.find(sucHalfEdge.tail);
      assert(adjList_it != G.setOfAdjLists.end());
      auto succ_it = adjList_it->e.find(sucHalfEdge);
      assert(succ_it != adjList_it->e.end());
      auto prevEdge_it = succ_it->previous;

      prevEdge_it->next = &(*oppBatchEdge_it);
      oppBatchEdge_it->previous = prevEdge_it;
      oppBatchEdge_it->next = &(*batchEdge_it);
      batchEdge_it->previous = &(*oppBatchEdge_it);
      batchEdge_it->next = &(*succ_it);
      succ_it->previous = &(*batchEdge_it);
    }

    // Fall 4. Beide Halbkanten haben in RNG_i einen Nachfolger. Berechner nun alle Vor- und Nachgänger und passe alle Kanten an
    else{

      // Finde den Nachfolger und Vorgänger von der batchEdge in RNG_i+k
      adjList_it = G.setOfAdjLists.find(sucHalfEdge.tail);
      assert(adjList_it != G.setOfAdjLists.end());
      auto succ_it = adjList_it->e.find(sucHalfEdge);
      assert(succ_it != adjList_it->e.end());
      auto prevEdge_it = succ_it->previous;

      // Finde den Nachfolger und Vorgänger der entgegengesetzten Halbkante in RNG_i+k
      adjList_it = G.setOfAdjLists.find(sucOppositeHalfEdge.tail);
      assert(adjList_it != G.setOfAdjLists.end());
      auto sucOppEdge_it = adjList_it->e.find(sucOppositeHalfEdge);
      assert(sucOppEdge_it != adjList_it->e.end());
      auto prevOppEdge_it = sucOppEdge_it->previous;


      prevOppEdge_it->next = &(*batchEdge_it);
      batchEdge_it->previous = prevOppEdge_it;
      batchEdge_it->next = &(*succ_it);
      succ_it->previous = &(*batchEdge_it);
      prevEdge_it->next = &(*oppBatchEdge_it);
      oppBatchEdge_it->previous = prevEdge_it;
      oppBatchEdge_it->next = &(*sucOppEdge_it);
      sucOppEdge_it->previous = &(*oppBatchEdge_it);
    }
  }


  
  /// @brief Berechne für ausreichende Größen der Face-Cycles die gleichmäßig verteilten neuen Positionen, an denen die Net-Edges im RNG_i+s liegen. 
  /// Suche mit diesen Werten für jede Net-Edge eine Startkante der Länge 1 in G und berechne ausgehend von dieser die Anzahl an Schritten (O(n/s)), 
  /// die man von dieser aus im RNG_{i+s} bis zur Net-Edge (parallel) laufen muss
  /// @param G Hilfsgraph G
  /// @param remainingSteps gibt für eine startEdge nach der Berechnung an, wie viele Schritte man laufen muss, um die dazu korrespondierende net-Edge zu finden
  /// @param n Anzahl der Eingabepunkte
  /// @return Vektor an Kanten, der die Startkanten im Graph G zur Suche der Net-Edges in reminingSteps Schritten enhält
  std::vector<Edge> EMST::calculateStartValues(Graph& G, std::vector<int>& remainingSteps, int n){

    std::vector<Edge> startEdges{};

    resetVisitedFaceCycles(G);

    int i = 0;
    for(auto& point: G.setOfAdjLists){
      for(auto& edge: point.e){
        if(!edge.visited){

          // durchlaufe jeden Face-Cycle und berechne die Summe an enthaltenden Kanten
          int lengthOfFaceCycle = edge.comprLength;
          auto next = edge.next;
          while(!(next->tail == edge.tail && next->head == edge.head)){
            lengthOfFaceCycle += next->comprLength;
            next = next->next;
          }
          i++;

          // Bestimme die Positionen der neuen net-Edges, falls die Länge eines face-cycles größer gleich n/s + 1 ist. Die Positionen starten bei 1
          std::vector<int> positions{};
          if(lengthOfFaceCycle >= (n/s + 1)){
            int numberNetEdges = lengthOfFaceCycle/(n/s+1);
            int remainingLength = lengthOfFaceCycle % (n/s+1);
            int restEveryEdge = remainingLength/numberNetEdges;
            int posOffset = remainingLength % numberNetEdges;

            positions.push_back(1);
            int last = 1;

            for(int i=1; i<numberNetEdges; i++){
              int offset = (i<= posOffset)? 1 : 0;
              positions.push_back(last + n/s+1 + restEveryEdge + offset);
              last += n/s+1 + restEveryEdge + offset;
            }
          }

          // durchlaufe den Face-Cycle erneut und finde die zur gesuchten Position vorherige H-Edge und speichere diese in startEdges
          // Bestimme dann die relative Distanz zur gesuchten Position und speichere diese in remainingSteps
          if(positions.size() != 0){
            // Suche eine H-Edge, bei der man anfangen kann zu suchen, diese ist direkt eine net-Edge
            while(next->comprLength != 1){
              next = next->next;
            }
            // Setze die Abbruchkante der Face-Cycles
            auto startEdge = next;
            auto lastHEdge = next;
            int actLengthOfFaceCycle = next->comprLength;
            int countLastH = next->comprLength;

            // Finde die Position im Vektor position mit allen Positionen der net-edges mithilfe der Variablen actPos
            long unsigned int actPos = 0;
            
            // Prüfe, ob die H-Edge die Startkante einer Kante an der gesuchten Position ist
            if(actLengthOfFaceCycle >= positions[actPos]){
              startEdges.push_back(*lastHEdge);
              remainingSteps.push_back(0);
              actPos++;
            }
            next->visited = true;

            // Prüfe nun für alle nachfolgenden Kanten des Zyklus, ob diese eine Startkante sind
            next = next->next;
            while(!(next->tail == startEdge->tail && next->head == startEdge->head)){
              next->visited = true;

              if(next->comprLength == 1){
                countLastH = actLengthOfFaceCycle + 1;
                lastHEdge = next;
              }
              actLengthOfFaceCycle += next->comprLength;


              // Füge die nächste H-Edge als Vorgänger der Position der neuen Kante ein
              if(actLengthOfFaceCycle >= positions[actPos] && actPos < positions.size()){
                
                do
                {
                  startEdges.push_back(*lastHEdge);
                  remainingSteps.push_back(positions[actPos]-countLastH);
                  actPos++;
                } while (actLengthOfFaceCycle >= positions[actPos] && actPos < positions.size());
                // Eine compressed edge kann in O(1) viele net edges zerlegt werden, somit kann eine H-Edge Vorgänger von mehreren Kanten sein
              }

              next = next->next;
            }
          }

          // Falls ein Face-Cycle zu kurz ist, um Net-Edges zu enthalten, markiere bloß alle Kanten als betrachtet
          else{
            edge.visited = true;
            next = edge.next;
            while(!(next->tail == edge.tail && next->head == edge.head)){
              next->visited = true;
              next = next->next;
            }
          }
        }
      }
    }
     
    #if WRITE_INTO_ALL_FILES == 1
    file_out_G << "\n G nach der Berechnung der neuen Startkanten und der Berechnung der relativen Läufe" << std::endl;
    writeGToFile(G);
    
    resetVisitedFaceCycles(G);

    file_out_Face_Cycles_G << "\n Face Cycles von G nach der Berechnung der neuen Startkanten und der Berechnung der relativen Läufe" << std::endl;
    writeFaceCyclesOfGToFile(G);
    #endif

    resetVisitedFaceCycles(G);

    return startEdges;
  }



  /// @brief Berechne ausgehend von den Startkanten mit enstprechend remainingSteps vielen parallel Läufen alle neuen net-Edges
  /// @param inputPoints Eingabepunkte, zu der der EMST gesucht ist
  /// @param startEdges Kanten, die als Ausgangspunkt zur Suche der net-edges dienen
  /// @param remainingSteps Vektor von ints zur Angabe, wie viele Schritte man von welcher startEdge machen muss, um die gesuchte net-edge zu finden
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return Vektor, der die neuen net-edges zur Repräsentation des RNG_i+s enthält
  std::vector<Edge> EMST::calculateNewSNet(const std::vector<Point>& inputPoints, const std::vector<Edge>& startEdges, std::vector<int>& remainingSteps, double upperLength){
    
    std::vector<Edge> sNet{};

    // Speichere alle Endpunkte der Kanten aus startEdges in headPreviousEdges, um alle Nachfolgerkanten zu berechnen
    std::vector<Point> headPreviousEdges{};

    // successor edges wird im nächsten Walk erneuert
    std::vector<Point> headNextEdges(startEdges.size());

    // previous edges enthält alle vorherigen Kanten
    std::vector<Edge> previousEdges = startEdges;


    // Initialisiere die Knoten, von denen initial die Walks losgehen, also die ausgehenden Kanten betrachtet werden
    
    // headPreviousEdges.insert(headPreviousEdges.end(), startEdges.begin(), startEdges.end());
    for(auto& e:startEdges){
      headPreviousEdges.push_back(e.head);
    }
    assert(startEdges.size() == headPreviousEdges.size());

    int actPos = 0;
    for(auto& edge: startEdges){
      if(remainingSteps[actPos] == 0){
        sNet.push_back(edge);
      }
      remainingSteps[actPos] -= 1;
      actPos++;
    }


    while (std::find_if(remainingSteps.begin(), remainingSteps.end(), [](int x){return x>=0;}) != remainingSteps.end()){
      // Berechne alle Nachbarn von den Knoten aus headPreviousEdges, wobei die Sortierung der Knoten erhalten bleibt
      std::vector<std::vector<Point>> neighbors = calcAdjacentPointsInRNG(inputPoints, headPreviousEdges);

      // Berechne der Reihe nach alle Nachfolger der Punkte aus headPreviousEdges
      for(long unsigned int actPos = 0; actPos < headPreviousEdges.size(); actPos++){
        Edge succ = nextEdge(upperLength, previousEdges[actPos], neighbors[actPos]);
        headNextEdges[actPos] = succ.head;
      }

      // Gehe remainingSteps viele Schritte und gebe dann die entsprechende net-edge (ist keine compressed edge) zurück
      for(long unsigned int actPos = 0; actPos < headNextEdges.size(); actPos++){
        Edge e{headPreviousEdges[actPos], headNextEdges[actPos]};
        previousEdges[actPos] = e;
        headPreviousEdges[actPos] = headNextEdges[actPos];

        if(remainingSteps[actPos] == 0){
          sNet.push_back(e);  
        }
        remainingSteps[actPos] -= 1;
      }
    }
    return sNet;
  }



  /// @brief Gebe für die einzufügenden Batch Edges des RNGs aus, ob diese auch zum EMST gehört und erstelle einen Hilfsgraphen, der die face-cycles des 
  /// aktuellen RNG_i während und nach dem Einfügen des s Kanten kompakt repräsentiert
  /// @param inputPoints Eingabepunktmenge zu der der EMST berechnet werden soll
  /// @param sNet Vektor an Kanten, die das S-Netz für den aktuellen RNG_i darstellen
  /// @param batchEdges Vektor an Kanten des RNGs, der Länge nach sortiert, die in den RNG_i eingefügt werden und die zum EMST gehören können
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return Graph, der die face-cycles von RNG_i+s repräsentiert
  Graph EMST::reportEdgesOfEMST(const std::vector<Point>& inputPoints, const std::vector<Edge>& sNet, const std::vector<Edge>& batchEdges, double upperLength){

    std::vector<Point> endpointsOfBatchEdges{};
    std::map<Point, int> map{};

    // Füge alle Endpunkte der batch edges in endpointsOfBatchEdges ein. Speichere zu jedem Punkt die Position in endpointsOfBatchEdges in einer Map, 
    // um die Nachbarn zu den Ednpunkte der batch edges nach dem Einfügen einer batch edge in O(log s) anpassen zu können
    int count = 0;
    for(auto& e:batchEdges){
      endpointsOfBatchEdges.push_back(e.head);
      map[e.head] = count;
      count ++;
      endpointsOfBatchEdges.push_back(e.tail);
      map[e.tail] = count;
      count++;
    }

    // Berechne alle Nachbarn der Endpunkte der batch edges entsprechend der Reihenfolge der Punkte in endpointsOfBatchEdges
    std::vector<std::vector<Point>> neighbors = calcAdjacentPointsInRNG(inputPoints, endpointsOfBatchEdges);

    // Berechne die Menge H an relevanten Kanten zur Erstellung des Hilfsgraphen G
    std::vector<Edge> H = calculateH(inputPoints, sNet, batchEdges, upperLength);

    #if WRITE_INTO_ALL_FILES == 1
    // Speichere H-Edges in Datei G.txt
    file_out_G << "\n H-Edges:" << std::endl;
    for(auto& edge: H){
      file_out_G << edge << std::endl;
    }
    #endif

    // Berechne den Hilfsgraphen G
    Graph G = calculateG(inputPoints, H, batchEdges, upperLength);

    #if WRITE_INTO_ALL_FILES == 1
    file_out_G << "\n G nach der Berechnung mit H" << std::endl;
    writeGToFile(G);

    file_out_Face_Cycles_G << "\n Face Cycles von G nach der Berechnung mit H" << std::endl;
    writeFaceCyclesOfGToFile(G);
    #endif

    resetVisitedFaceCycles(G);


    // Führe eine Tiefensuche auf G durch, um die Zusammenhangskomponenten zu kennzeichnen
    depthFirstSearch(G);

    double tempLength = upperLength;
    int pos = 0;

    // Füge der Reihe nach die batch edges in G ein, prüfe, ob diese ZHKs verbinden, gebe diese ggfs. aus und füge diese anschließend in G ein
    // achte dabei auf korrektes Einfügen bzgl. Winkel
    for(auto batchEdge: batchEdges){
      auto itTail = G.setOfAdjLists.find(batchEdge.tail);
      assert(itTail != G.setOfAdjLists.end());
      auto itHead = G.setOfAdjLists.find(batchEdge.head);
      assert(itHead != G.setOfAdjLists.end());

      // Nutzen const_cast, da Punkte geändert werden müssen, aber die Ordnung erhalten bleibt, da nur der rank geändert wird
      Point* tail = const_cast<Point*> (&itTail->p);
      Point* head = const_cast<Point*> (&itHead->p);

      if(!(findSet(*tail) == findSet(*head))){
         unionSets(*tail, *head);
         file_out_EMST << batchEdge << std::endl;
      }


      // Füge die Kante aus batchEdges so in G ein, dass auch die vorherige und nachfolgende Kante korrekt angepasst werden, damit die face-cycles korrekt bleiben
      insertBatchEdge(G, batchEdge, neighbors[pos], neighbors[pos+1], tempLength);


      // Passe die Nachbarn aller Endpunkte der Batch Edges an, da diese aktualisierten Versionen für weitere einzufügenden Batch Edges benötigt werden und eine 
      // Berechnung über calcAdjacentPointsInRNG zu teuer ist. Passe das neighbor Set nach dem Einfügen der Batch Edge an, indem in O(log(s)) in der Map gesucht wird
      bool found = false;
      auto mapIt = map.find(batchEdge.tail);
      int posTail = mapIt->second;

      for(auto neighbors: neighbors[posTail]){
        if(neighbors == batchEdge.head){
          found = true;
        }
      }
      if(!found){
        neighbors[posTail].push_back(batchEdge.head);
      }

      found = false;
      mapIt = map.find(batchEdge.head);
      int posHead = mapIt->second;

      for(auto neighbors: neighbors[posHead]){
        if(neighbors == batchEdge.tail){
          found = true;
        }
      }
      if(!found){
        neighbors[posHead].push_back(batchEdge.tail);
      }

      tempLength = batchEdge.calcLength();

      // Inkrementiere pos, um für die nächste Kante auf die richtigen Nachbarn zu kommen
      pos += 2;
    }

    // G sollte nun alle Kanten aus H, alle compressed edges und die neuen Batch Edges aus E_{i,s} enthalten.
    #if WRITE_INTO_ALL_FILES == 1
    // Betrachte G, um evtl. Unstimmigkeiten zu bemerken.
    file_out_G << "\n G nach dem Einfügen der Batch Edges" << std::endl;
    writeGToFile(G);

    resetVisitedFaceCycles(G);

    file_out_Face_Cycles_G << "\n Face Cycles von G nach dem Einfügen der Batch Edges" << std::endl;
    writeFaceCyclesOfGToFile(G);
    #endif

    resetVisitedFaceCycles(G);

    return G;
  }


  /// @brief Berechne nachdem die s nächstgrgößeren Kanten des RNGs in den aktuellen RNG_i eingefügt wurden das S-Netz für den RNG_i+s
  /// @param inputPoints Eingabepunktmenge zu der der EMST gesucht ist
  /// @param run gibt an, zum wievielten Mal s Kanten hinzugefügt wurden
  /// @param G Hilfsgraph G, der die face-cycles von RNG_i+s repräsentiert
  /// @param upperLength Länge der längsten Kante des aktuellen RNG_i
  /// @return S-Netz als Vektor von Kanten 
  std::vector<Edge> EMST::maintainSNet(const std::vector<Point>& inputPoints, int run, Graph& G, double upperLength){

    // Berechne Startkanten in G, von denen man mit remainingSteps vielen parallelen Läufe die jeweilige Net-Edge erreicht wird
    std::vector<int> remainingSteps{};
    std::vector<Edge> startEdges = calculateStartValues(G, remainingSteps, inputPoints.size());

    // Berechne ausgehend von allen Startkanten alle neuen, gleichmäßig verteilten net-Edges mit parallelen Läufen
    std::vector<Edge> sNet = calculateNewSNet(inputPoints, startEdges, remainingSteps, upperLength);

    #if WRITE_INTO_ALL_FILES == 1
    // Gebe das neue S-Netz aus, das für die nächste Iteration benötigt wird. Speichere es auch in der Datei zu den S-Netzen
    file_out_SNet << "\n S-Netz zu Lauf: " << run << "\n\n";
    for(auto& edge: sNet){
      file_out_SNet << edge << std::endl;
    }
    #endif

    return sNet;
  }


  /// @brief Der Konstruktor der Klasse EMST berechnet unter Nutzung von O(s) Speicherzellen den Euklidischen minimalen Spannbaum zun den Eingabepunkten.
  /// Dies wird mit einer Laufzeit von O(n³/s²*log(s)) realisiert
  /// @param inputPoints Vektor von Eingabepunkten in allgemeiner Lage
  /// @param s O(s) Speicherzellen dürfen zur Berechnung genutzt werden
  EMST::EMST(const std::vector<Point> inputPoints, int s):s{s}{

    // Teste, ob 1<=s<=n ist und passe die Werte gegebenenfalls auf die jeweils nächste Schranke an
    if(s < 1){s=1;}
    else if(s > static_cast<int>(inputPoints.size())){s=inputPoints.size();}

    // Teste, ob die Eingabepunktmenge > 2 ist
    if(inputPoints.size() < 3){
      std::cerr << "Die Punktmenge sollte aus mindestens drei Punkten bestehen." << std::endl;
      exit(-1);
    }

    // Initialisiere und öffne die Dateien, in die die Graphen und Hilfsstrukturen geschrieben werden
    openFiles();
    
    // Berechne und schreibe die Delaunay Triangulation zu den Eingabepunkten
    writeDelaunayTriangulationToFile(inputPoints, file_out_Delaunay);

    // S-Netz wird als Vektor von Edges ohne Sortierung gespeichert, da diese implizit gefunden wird
    std::vector<Edge> sNet{};

    std::vector<Edge> actRNGEdges{};

    // upperLength bezeichnet Länge der längsten Kante des aktuellen RNG_i
    double upperLength = 0;
    int run = 1;

    do
    {
      // Berechne die nächsten s Kanten des RNGs zu den Eingabepunkten
      actRNGEdges = calcBatchOfSortedEdges(inputPoints, upperLength);

      // Abfrage dient zur Vermeidung unnötiger Berechnungen, falls keine neuen Kanten des RNG(S) gefunden wurden.
      // Entfernt man diese, schlagen Tests fehl, da unter anderem Hilfsstrukturen H und G neu berechnet werden. Die drei anderen Graphen bleiben korrekt.
      // Außerdem ist die Betrachtung der Version zuvor zur Überprüfung der korrekten Berechnung von G und dessen face-cycles für >0 einzufügende Kanten sinnvoller! 
      if(actRNGEdges.size() != 0){
        // Gebe für das aktuelle S-Netz die Kanten von RNG_i+s in sortierter Reihenfolge aus, die auch zum EMST gehören
        Graph G = reportEdgesOfEMST(inputPoints, sNet, actRNGEdges, upperLength);

        upperLength = actRNGEdges[actRNGEdges.size()-1].calcLength();

        // Berechne das S-Netz für RNG_i+s
        sNet = maintainSNet(inputPoints, run, G, upperLength);
      }
      
      run++;
    } while (static_cast<int>(actRNGEdges.size()) == s); // So lange s weitere Kanten des RNGs gefunden werden, können in der nächsten Iteration weitere Kanten gefunden werden
    
  }


  /// @brief Schließe beim Destruieren alle geöffneten Dateien
  EMST::~EMST(){
    file_out_Delaunay.close();
    file_out_RNG.close();
    file_out_EMST.close();
    file_out_G.close();
    file_out_Face_Cycles_G.close();
    file_out_SNet.close();
  }