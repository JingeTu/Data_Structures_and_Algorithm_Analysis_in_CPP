//
// Created by 涂金戈 on 25/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_GRAPH_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_GRAPH_H

#include "Edge.h"
#include "Vertex.h"

class Graph {
public:

    Graph();

    bool AddVertex(Vertex * vertex);

    bool AddEdge(Vertex * start, Vertex * end, const int & weight);

    const std::vector<Vertex *> GetVertices() const ;

    static void PrintPaths(const Graph &graph,
                           const std::map<std::string, std::string> &path_map);

    static void PrintPathsHelper(const Graph &graph, Vertex *v,
                                 const std::map<std::string, std::string> &path_map,
                                 const std::vector<Vertex *> &vertices);
private:

    bool CheckVertexIn(Vertex * vertex);

    std::vector<Vertex *> vertices;
};

#include "Graph.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_GRAPH_H
