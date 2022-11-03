#pragma once
#include <gtest/gtest.h>
#include "EMST.hpp"
#include "Config.h"

// Test Fixture, um (private) Methoden der Klasse RNG testen zu können
class EMSTTest : public ::testing::Test{

    protected:

        EMST *emst;

        void init(const std::vector<Point> input, int s){
            emst = new EMST{input, s};
        }

        void openFiles(){
            emst->openFiles();
        }
       
        std::set<Point> calcNeighbors(const std::set<Point>& Q, const Graph& G){
            return emst->calcNeighbors(Q, G);
        }

        void calcPotEdges(const Graph& G, std::set<struct AdjList>& potEdges){
            emst->calcPotEdges(G, potEdges);
        }

        std::set<Point> calcRemainingNeighbors(const Graph& G, std::set<struct AdjList>& potEdges){
            return emst->calcRemainingNeighbors(G, potEdges);
        }  

        std::vector<std::vector<Point>> extractAllNeighbors(const std::set<struct AdjList>& potEdges, const std::vector<Point>& subset){
            return emst->extractAllNeighbors(potEdges, subset);
        }

        std::vector<std::vector<Point>> calcAdjacentPointsInRNG(const std::vector<Point>& input, const std::vector<Point>& subset){
            return emst->calcAdjacentPointsInRNG(input, subset);
        }

        std::vector<Edge> calcBatchOfEdges(const std::vector<Point>& S, int first, int last){
            return emst->calcBatchOfEdges(S, first, last);
        }

        std::vector<Edge> calcBatchOfSortedEdges(const std::vector<Point>& input, double upperLength){
            return emst->calcBatchOfSortedEdges(input, upperLength);
        }

        std::vector<Edge> calculateH(const std::vector<Point>& input, const std::vector<Edge>& sNet, const std::vector<Edge>& Eis, double length){
            return emst->calculateH(input, sNet, Eis, length);
        }

        bool edgeIsHEdge(const Edge& e, const std::vector<Edge>& H){
            return emst->edgeIsHEdge(e, H);
        }

        Graph calculateG(const std::vector<Point>& input, const std::vector<Edge>& H, const std::vector<Edge>& Eis, double length){
            return emst->calculateG(input, H, Eis, length);
        }

        void writeGToFile(Graph& G){
            emst->writeGToFile(G);
        }

        void writeFaceCyclesOfGToFile(Graph& G){
            emst->writeFaceCyclesOfGToFile(G);
        }

        void insertBatchEdge(Graph& G, const Edge& batchEdge, const std::vector<Point>& neighborsP1, const std::vector<Point>& neighborsP2, double length){
            emst->insertBatchEdge(G, batchEdge, neighborsP1, neighborsP2, length);
        }

        Graph reportEdgesOfEMST(const std::vector<Point>& input, const std::vector<Edge>& sNet, const std::vector<Edge>& Eis, double length){
            return emst->reportEdgesOfEMST(input, sNet, Eis, length);
        }

        std::vector<Edge> calculateStartValues(Graph& G, std::vector<int>& remainingSteps, int n){
            return emst->calculateStartValues(G, remainingSteps, n);
        }

        std::vector<Edge> calculateNewSNet(const std::vector<Point>& input, const std::vector<Edge>& startEdges, std::vector<int>& remainingSteps, double length){
            return emst->calculateNewSNet(input, startEdges, remainingSteps, length);
        }

        std::vector<Edge> maintainSNet(const std::vector<Point>& input, int run, Graph& G, double length){
            return emst->maintainSNet(input, run, G, length);
        }

    public:
        ~EMSTTest(){
            delete emst;
        }    

};


    /// @brief Gebe den Absatz nach dem letzten Zeilenumbruch in "in" als stringstream zurück
    /// @param in input file stream
    /// @return Absatz nach dem letzten Zeilenumbruch in "in"
    std::stringstream lastBlock(std::ifstream &in){
        std::stringstream buffer;
        std::string line;
        while(std::getline(in, line)){    
            if(line.empty()){
                buffer.str(std::string());
            }else{
            buffer << line << "\n";
            }
        }
        return buffer;
    }

    /// @brief Erzeuge den korrespondierende Punkt für einen String der Form (a, b)
    /// @param point Punkt als String
    /// @return Point Objekt, das (a, b) repräsentiert
    Point parsePoint(std::string &point){
        point.erase(remove_if(point.begin(), point.end(), isspace), point.end());

        double x = std::stod(point.substr(1, point.find(",")));
        double y = std::stod(point.substr(point.find(",") + 1, point.size() - 1));

        Point p{x, y};
        return p;
    }

    /// @brief Erzeuge die korrespondierende Kante für einen String der Form (a, b); (c, d)
    /// @param line Kante als String
    /// @return Edge Objekt, das die Kante (a, b); (c, d) repräsentiert
    Edge parseEdge(std::string &line){
        auto pos = line.find(";");
        assert(pos != std::string::npos);

        auto p1 = line.substr(0, pos);
        auto p2 = line.substr(pos + 1);

        Edge edge{parsePoint(p1), parsePoint(p2)};
        return edge;
    }

    /// @brief Erzeuge die korrespondierende Kante für einen String der Form (a, b); (c, d) ; komprimierte Länge: x ; 0/1
    /// @param line Kante als String
    /// @return Edge Objekt, das die Kante (a, b); (c, d) mit der comprimierten Länge x Kanten repräsentiert
    Edge parseComprEdge(std::string &line){
        auto pos = line.find(";");
        assert(pos != std::string::npos);

        auto p1 = line.substr(0, pos);
        auto p2 = line.substr(pos + 1);

        auto pos2 = p2.find(";");

        auto p3 = p2.substr(0, pos2);
        auto p4 = p2.substr(pos2 + 1);

        auto pos3 = p4.find(":");

        auto p5 = p4.substr(pos3);
        p5.erase(remove_if(p5.begin(), p5.end(), isspace), p5.end());

        auto pos4 = p5.find(";");

        int comprLength = std::stoi(p5.substr(1, pos4));
        bool again = static_cast<bool>(std::stoi(p5.substr(pos4+1)));

        Edge edge{parsePoint(p1), parsePoint(p3), comprLength, again};
        return edge;
    }

    
    /// @brief Parse die Kanten und füge diese entsprechend ihres Auftretens dem Ausgabevektor hinzu
    /// @param inputFile Bezeichner der auszulesenden Datei (, die alle Kanten enthält)
    /// @return Vektor an Kanten der Eingabedatei (des EMSTs oder RNS)
    std::vector<Edge> parseEdgeFile(std::string inputFile) {
        std::vector<Edge> edges;
        std::string line;
        std::ifstream stream(inputFile);

        while (std::getline(stream, line)) {
            edges.push_back(parseEdge(line));
        }
        
        return edges;
    }


    /// @brief Parse die Kanten zum letzten S-Netz und speichere diese in der Reihenfolge ihres Auftretens
    /// @param inputFile Bezeichner der auszulesenden Datei
    /// @return Vektor an Kanten des S-Netzes
    std::vector<Edge> parseSNetBlock(std::string inputFile){
        std::vector<Edge> res;
        std::string line;

        std::ifstream sNet(inputFile);
        std::stringstream ss = lastBlock(sNet);

        while(std::getline(ss, line)){
            res.push_back(parseEdge(line));
        }

        return res;
    }

    /// @brief Parse den Graphen zum letzten Hilfsgraphen der Berechnung
    /// @param inputFile Bezeichner der auszulesenden Datei
    /// @return Zur Eingabedatei korrespondierender Graph
    Graph parseGBlock(std::string inputFile){
        Graph G{};
        std::string line;

        std::ifstream stream_G(inputFile);
        std::stringstream ss_G = lastBlock(stream_G);

        while(std::getline(ss_G, line)){
            if(!line.empty() && line.find("G") == std::string::npos){
                bool point = line.find("Punkt") != std::string::npos;
                if(point){
                    auto pos = line.find("(");
                    assert(pos != std::string::npos);

                    auto p = line.substr(pos);

                    G.setOfAdjLists.insert(AdjList{parsePoint(p)});
                }
                else{
                    auto pos = line.find(";");
                    assert(pos != std::string::npos);

                    auto p = line.substr(0, pos);

                    auto actList = G.setOfAdjLists.find(parsePoint(p));
                    actList->e.insert(parseComprEdge(line));
                }
            }
        }
        return G;
    }

    /// @brief Parse die Kanten jedes Face-Cycles und speichere diese gemäß der Auftrittsreihenfolge in einem Vektor
    /// @param inputFile Bezeichner der auszulesenden Datei
    /// @return Gebe alle Face-Cycles als Vektor von Vektoren der nachfolgenden Kanten zurück
    std::vector<std::vector<Edge>> parseFaceCyclesOfG(std::string inputFile){
        std::vector<std::vector<Edge>> result{};
        std::vector<Edge> temp{};
        std::string line;

        std::ifstream faceCyclesOfG_30(inputFile);
        std::stringstream ss_cyclesG_30 = lastBlock(faceCyclesOfG_30);

        while(std::getline(ss_cyclesG_30, line)){
            if(!line.empty() && line.find("Face Cycles von G") == std::string::npos && line.find("Face-Cycle 0") == std::string::npos){
                
                if(line.find("Face-Cycle") != std::string::npos){
                    result.push_back(temp);
                    temp.resize(0);
                }
                else{
                    temp.push_back(parseComprEdge(line));
                }
            }
        }
        result.push_back(temp);
        temp.resize(0);
        return result;
    }