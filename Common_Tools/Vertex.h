//
// Created by 涂金戈 on 25/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VERTEX_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VERTEX_H

#include "Edge.h"

class Vertex {
public:

    Vertex() {}

    Vertex(std::string name) : name_{name} {}

    std::string GetName() { return name_; }

    bool SetName(std::string name) {
        name_ = name;
        return true;
    }

    void AddTo(const Edge &to_edge) {
        std::list<Edge>::iterator it = to_.begin();
        std::list<Edge>::const_iterator end = to_.end();
        while (it != end) {
            if ((*it++).vertex == to_edge.vertex)
                return;
        }
        to_.push_back(to_edge);
        to_edge.vertex->AddFrom(Edge(this, to_edge.weight));
    }

    const std::list<Edge> &GetTos() {
        return to_;
    }

    const std::list<Edge> &GetFroms() {
        return from_;
    }

    void PrintAdjs() {
        std::list<Edge>::iterator it = to_.begin();
        std::list<Edge>::const_iterator end = to_.end();
        while (it != end) {
            std::cout << (*it++).vertex->GetName() << " ";
        }
        std::cout << "\n";
    }

private:

    // Add from edge for this vertex, outside class, user can only add to edges.
    void AddFrom(const Edge &from_edge) {
        std::list<Edge>::iterator it = from_.begin();
        std::list<Edge>::const_iterator end = from_.end();
        while (it != end) {
            if ((*it++).vertex == from_edge.vertex)
                return;
        }
        from_.push_back(from_edge);
    }

    std::string name_;

    // From this vertex to other vertices' edges.
    std::list<Edge> to_;
    // From other vertex to this vertices's edges.
    std::list<Edge> from_;
};

#include "Vertex.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VERTEX_H
