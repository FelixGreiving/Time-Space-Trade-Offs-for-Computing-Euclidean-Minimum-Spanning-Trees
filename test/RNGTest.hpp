#pragma once
#include <gtest/gtest.h>
#include "RNG.hpp"
#include "Config.h"


// Test Fixture, um (private) Methoden der Klasse RNG testen zu können
class RNGTest : public ::testing::Test{

  protected:

    RNG graphRNG;

    void init(const std::set<Point> inputPoints, int k){
        graphRNG = RNG{inputPoints, k};
    }

    void initAssPoints(Transformer& transformer, assPointsSet& associatedPoints){
        graphRNG.initAssPoints(transformer, associatedPoints);
    }

    void sortAssEdges(Delaunay& dt, std::set<AssEdges>& allEdges, assPointsSet& umgAssociatedPoints){
        graphRNG.sortAssEdges(dt, allEdges, umgAssociatedPoints);
    }

    bool initSearchInT(std::multiset<AssEdges, orderTypeAssEdges>::iterator& edgeIt, assPointsSet::iterator& it, bool& nextPointNotFound){
        return graphRNG.initSearchInT(edgeIt, it, nextPointNotFound);
    }

    AssEdges findAssEdges(std::multiset<AssEdges, orderTypeAssEdges>::iterator& edgeIt){
        return graphRNG.findAssEdges(edgeIt);
    }

    void deleteAssociatedEdge(AssEdges actEdge, std::multiset<AssEdges, orderTypeAssEdges>::iterator& actEdgeIt, std::set<OrientedAdjList, std::greater<OrientedAdjList>>::iterator& actorientedAdjListIt){
        graphRNG.deleteAssociatedEdge(actEdge, actEdgeIt, actorientedAdjListIt);
    }

    bool nextElementInT(assPointsSet::iterator& it, bool forward){
        return graphRNG.nextElementInT(it, forward);
    }

    void eliminateWithProjection(RNG& assGraph){
        graphRNG.eliminateWithProjection(assGraph);
    }

    void calculateRNG(RNG& assGraph){
        graphRNG.calculateRNG(assGraph);
    }

    RNG calculateRNG(){
        return graphRNG.calculateRNG();
    }

    void calculateRNGTrivial(){
        graphRNG.calculateRNGTrivial();
    }

    // Annahme: std::set arbeitet korrekt
    bool compareGraphs(std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> adjListOtherGraph){
      // Ist die Adjazenzliste von graphRNG eine Teilmenge von adjListOtherGraph
      for(auto OrientedAdjList:graphRNG.setOfOrientedAdjLists){
        auto correspOrientedAdjList = adjListOtherGraph.find(OrientedAdjList);
        if(correspOrientedAdjList == adjListOtherGraph.end()){
          return false;
        }
        for(auto edge:OrientedAdjList.e){
          // Prüfe, ob alle Kanten zu einem Eintrag auch in dem Eintrag zum assGraph enthalten sind
          if(correspOrientedAdjList->e.find(edge) == correspOrientedAdjList->e.end()){
            return false;
          }
        }
      }
      // Ist adjListOtherGraph von graphRNG eine Teilmenge von Adjazenzliste
      for(auto OrientedAdjList:adjListOtherGraph){
          auto correspOrientedAdjList = graphRNG.setOfOrientedAdjLists.find(OrientedAdjList);
          if(correspOrientedAdjList == graphRNG.setOfOrientedAdjLists.end()){
            return false;
          }
          for(auto edge:OrientedAdjList.e){
            // Prüfe, ob alle Kanten zu einem Eintrag auch in dem Eintrag zum assGraph enthalten sind
            if(correspOrientedAdjList->e.find(edge) == correspOrientedAdjList->e.end()){
              return false;
            }
          }
      }

      return true;
      }

};


/// @brief Parse einen String, der eine Adjazenzliste repräsentiert und berechne diese
/// @param input String, der Adjazenzlister repräsentiert
/// @return Adjazenzliste, die zu input korrespondiert
std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> parseAdjList(std::string input) {
  std::vector<AssPoints> points;
  std::vector<struct OrientedAdjList> orientedAdjLists;
  std::vector<AssEdges> edges;

  std::string line;
  std::istringstream stream(input);

  std::getline(stream, line);
  // Parse Punkte und erstelle damit die orientedAdjLists
  while (std::getline(stream, line)) {
    if (line.find("//") == std::string::npos) {
      if (!line.empty()) {
        line = line.substr(line.find("p"));
        line = line.substr(line.find(" "));

        auto pos = line.find(")");
        assert(pos != std::string::npos);

        auto p1 = line.substr(0, pos);
        auto p2 = line.substr(pos + 1);

        p1.erase(remove_if(p1.begin(), p1.end(), isspace), p1.end());
        p2.erase(remove_if(p2.begin(), p2.end(), isspace), p2.end());

        int p1_x = std::stoi(p1.substr(1, p1.find(",")));
        int p1_y = std::stoi(p1.substr(p1.find(",") + 1, p1.size() - 1));
        int p2_x = std::stoi(p2.substr(1, p2.find(",")));
        int p2_y = std::stoi(p2.substr(p2.find(",") + 1, p2.size() - 1));

        points.emplace_back(K::Point_3{p1_x, p1_y, 1},
                            K::Point_3{p2_x, p2_y, 1});
        orientedAdjLists.emplace_back(points.back());
      } else {
        break;
      }
    }
  }

  // Parse die einzufügenden Kanten
  while (std::getline(stream, line)) {
    if (line.find("//") == std::string::npos) {
      if (!line.empty()) {
        line = line.substr(line.find("e"));
        line = line.substr(line.find(" ") + 1);

        auto pos = line.find(" ");
        assert(pos != std::string::npos);

        auto p1 = line.substr(0, pos);
        auto p2 = line.substr(pos + 1);

        int p1_i = std::stoi(p1.substr(1)) - 1;
        int p2_i = std::stoi(p2.substr(1)) - 1;

        assert(p1_i < static_cast<int>(points.size()));
        assert(p2_i < static_cast<int>(points.size()));

        edges.emplace_back(points[p1_i], points[p2_i]);
      } else {
        break;
      }
    }
  }

  // Parse Kanten und den jeweiligen OrientedAdjList, in den sie einsortiert werden sollen
  while (std::getline(stream, line)) {
    if (line.find("//") == std::string::npos) {
      if (line.find("p") != std::string::npos) {
        line = line.substr(line.find("p"));

        auto pos = line.find(" ");
        assert(pos != std::string::npos);

        auto p = line.substr(0, pos);
        auto e = line.substr(pos + 1);

        int p_i = std::stoi(p.substr(1)) - 1;
        int e_i = std::stoi(e.substr(1)) - 1;

        assert(p_i < static_cast<int>(points.size()));
        assert(e_i < static_cast<int>(edges.size()));

        orientedAdjLists[p_i].e.insert(edges[e_i]);
      } else {
        break;
      }
    }
  }

  std::set<struct OrientedAdjList, std::greater<struct OrientedAdjList>> adjList;
  adjList.insert(orientedAdjLists.begin(), orientedAdjLists.end());

  return adjList;
}