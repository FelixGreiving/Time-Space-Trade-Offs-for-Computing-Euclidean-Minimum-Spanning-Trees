#include "Graph.hpp"


  /// @brief Überschreibe den "<" Operator, sodass ein AdjList kleiner als ein anderes ist, wenn der Punkt zu dem es erstellt wurde, kleiner als der des anderen ist
  bool operator<(const struct AdjList& s1, const struct AdjList& s2){
    return s1.p < s2.p;
  }

  /// @brief Überschreibe den "==" Operator, sodass ein AdjList gleich einem Anderen ist, wenn der Punkt zu dem es erstellt wurde, gleich dem des anderen ist
  bool operator==(const struct AdjList& s1, const struct AdjList& s2){
    return s1.p == s2.p;
  }

  /// @brief Überschreibe den "==" Operator, sodass zwei Graphen gleich sind, wenn die Adjazenzlisten gleich sind 
  bool operator==(const Graph& G1, const Graph& G2){
    for(auto& AdjList: G1.setOfAdjLists){
      auto it = G2.setOfAdjLists.find(AdjList.p);
      if(it == G2.setOfAdjLists.end()){
        return false;
      }
      for(auto& edge: AdjList.e){
        auto edge_it = it->e.find(edge);
        if(edge_it == it->e.end()){
          return false;
        }
      }
    }

    for(auto& AdjList: G2.setOfAdjLists){
      auto it = G1.setOfAdjLists.find(AdjList.p);
      if(it == G1.setOfAdjLists.end()){
        return false;
      }
      for(auto& edge: AdjList.e){
        auto edge_it = it->e.find(edge);
        if(edge_it == it->e.end()){
          return false;
        }
      }
    }
    return true;
  }



  /// @brief Setze alle Werte des Attributs visited jeder Kante aus G auf false zurück
  /// @param G Hilfsgraph G
  void resetVisitedFaceCycles(Graph& G){
    for(auto& point: G.setOfAdjLists){
      for(auto& edge: point.e){
        edge.visited = false;
      }
    }
  }



  /// @brief Subroutine von depthFirstSearch, um alle Zusammenhangskomponenten zu traversieren und die Wurzel anzupassen
  /// @param G Graph G
  /// @param s Menge an Kanten zu einem Punkt
  void dfsVisit(Graph& G, AdjList& s){
    s.p.color = Color::GRAY;

    for(auto& edge: s.e){
      auto it = G.setOfAdjLists.find(AdjList(edge.head));
      assert(it != G.setOfAdjLists.end());
      if(it->p.color == Color::WHITE){
        unionSets(s.p, const_cast<Point&> (it->p));
        dfsVisit(G, const_cast<AdjList&> (*it));
      }
    }
    s.p.color = Color::BLACK;
  }

  /// @brief Führt eine Tiefensuche auf dem Graphen G durch und ordne alle Zusammenhangskomponenten der gleichen Wurzel bzgl. parent zu
  /// @param G Graph G
  void depthFirstSearch(Graph& G){
    // Farben wieder auf WHITE setzen, bevor DFS startet
    for(auto& point: G.setOfAdjLists){
      auto points = const_cast<AdjList&> (point);
      // Initialisiere union-find Struktur, führe Make-Set für jeden Punkt durch
      Point* p = const_cast<Point*> (&point.p);
      p->parent = p;
      points.p.color = Color::WHITE;
    }
    for(auto& edges: G.setOfAdjLists){
      if(edges.p.color == Color::WHITE){
        dfsVisit(G, const_cast<AdjList&> (edges));
      }
    }
  }