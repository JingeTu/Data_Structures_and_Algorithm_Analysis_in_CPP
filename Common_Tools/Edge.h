//
// Created by 涂金戈 on 25/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_EDGE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_EDGE_H

class Vertex;

struct Edge {
    Vertex *vertex;
    int weight;
    std::string name;

    Edge(Vertex *to, const int &weight, const std::string &name = "") : vertex{to}, weight{weight}, name{} {}
};

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_EDGE_H
