//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include "../Common_Tools/Graph.h"

//class Vertex {
//public:
//    Vertex(std::string name) : name_{name}, path_{nullptr} {}
//
//    std::string GetName() { return name_; }
//
//    Vertex *GetPath() const {
//        return path_;
//    }
//
//    void SetPath(Vertex *path) {
//        this->path_ = path;
//    }
//
//    int GetDist() {
//        return dist_;
//    }
//
//    void SetDist(const int &dist) {
//        this->dist_ = dist;
//    }
//
//    bool GetKnown() {
//        return known_;
//    }
//
//    void SetKnown(const bool known) {
//        this->known_ = known;
//    }
//
//    void AddTo(Vertex *adjVertex) {
//        std::list<Vertex *>::iterator it = to_.begin();
//        std::list<Vertex *>::const_iterator end = to_.end();
//        while (it != end) {
//            if (*it++ == adjVertex)
//                return;
//        }
//        to_.push_back(adjVertex);
//    }
//
//    const std::list<Vertex *> &GetTos() {
//        return to_;
//    }
//
//    void PrintAdjs() {
//        std::list<Vertex *>::iterator it = to_.begin();
//        std::list<Vertex *>::const_iterator end = to_.end();
//        while (it != end) {
//            std::cout << (*it)->GetName() << " ";
//            ++it;
//        }
//        std::cout << "\n";
//    }
//
//private:
//
//    std::string name_;
//    std::list<Vertex *> to_;
//    int dist_;
//    bool known_;
//    Vertex *path_;
//};

//void unweighted(std::vector<Vertex *> &graph, Vertex *s) {
//    for (auto &v : graph) {
//        v->SetDist(INT_MAX);
//        v->SetKnown(false);
//    }
//
//    s->SetDist(0);
//
//    for (int curr_dist = 0; curr_dist < graph.size(); ++curr_dist)
//        for (auto &v : graph)
//            if (!v->GetKnown() && v->GetDist() == curr_dist) {
//                v->SetKnown(true);
//                auto &to = v->GetTos();
//
//                for (auto &w : to)
//                    if (w->GetDist() == INT_MAX) {
//                        w->SetDist(curr_dist + 1);
//                        w->SetPath(v);
//                    }
//            }
//}

void UnweightedShortestPaths(const Graph &graph, Vertex *s,
                             std::map<std::string, int> &distance_map,
                             std::map<std::string, std::string> &path_map) {
    const std::vector<Vertex *> &vertices = graph.GetVertices();

    std::map<std::string, bool> known_map;

    for (Vertex *v : vertices) {
        distance_map.insert(std::make_pair(v->GetName(), INT_MAX));
        path_map.insert(std::make_pair(v->GetName(), ""));
        known_map.insert(std::make_pair(v->GetName(), false));
    }

    (*distance_map.find(s->GetName())).second = 0;

    for (int curr_dist = 0; curr_dist < vertices.size(); ++curr_dist) {
        for (Vertex *v : vertices) {
            const bool &known = (*known_map.find(v->GetName())).second;
            if (!known) {
                const int &distance = (*distance_map.find(v->GetName())).second;
                if (distance == curr_dist) {
                    (*known_map.find(v->GetName())).second = true;
                    const std::list<Edge> &to = v->GetTos();

                    for (const Edge &w : to) {
                        const int &w_distance = (*distance_map.find(w.vertex->GetName())).second;
                        if (w_distance == INT_MAX) {
                            (*distance_map.find(w.vertex->GetName())).second = curr_dist + 1;
                            (*path_map.find(w.vertex->GetName())).second = v->GetName();
                        }
                    }
                }
            }
        }
    }
}

//void unweighted_queue(std::vector<Vertex *> &graph, Vertex *s) {
//    for (auto &v : graph) {
//        v->SetDist(INT_MAX);
//        v->SetKnown(false);
//    }
//
//    s->SetDist(0);
//    std::queue<Vertex *> q;
//    q.push(s);
//
//    while (!q.empty()) {
//        auto &v = q.front();
//        q.pop();
//        v->SetKnown(true);
//
//        auto &to = v->GetTos();
//        for (auto &w : to)
//            if (w->GetDist() == INT_MAX) {
//                w->SetDist(v->GetDist() + 1);
//                w->SetPath(v);
//                q.push(w);
//            }
//
//    }
//}

//void PrintPathsHelper(const std::vector<Vertex *> &graph, Vertex *v) {
//    if (v->GetPath() != nullptr) {
//        PrintPathsHelper(graph, v->GetPath());
//        std::cout << " to ";
//    }
//    std::cout << v->GetName();
//}

//void PrintPaths(const std::vector<Vertex *> &graph) {
//    for (auto &v : graph) {
//        if (v->GetPath() != nullptr) {
//            PrintPathsHelper(graph, v);
//            std::cout << "\tPath Length: " << v->GetDist();
//            std::cout << '\n';
//        } else {
//            std::cout << "No path from START to " << v->GetName() << ".\n";
//        }
//    }
//}

int main() {

    Graph graph;

    Vertex *vertices = new Vertex[8];

    // Add Vertices
    for (int i = 1; i <= 7; ++i) { // discard the first element
        vertices[i].SetName(std::to_string(i));
        graph.AddVertex(&vertices[i]);
    }

    Vertex *start_vertex = &vertices[3];

    graph.AddEdge(&vertices[1], &vertices[2], 1);
    graph.AddEdge(&vertices[1], &vertices[4], 1);
    graph.AddEdge(&vertices[2], &vertices[4], 1);
    graph.AddEdge(&vertices[2], &vertices[5], 1);
    graph.AddEdge(&vertices[3], &vertices[1], 1);
    graph.AddEdge(&vertices[3], &vertices[6], 1);
    graph.AddEdge(&vertices[4], &vertices[3], 1);
    graph.AddEdge(&vertices[4], &vertices[5], 1);
    graph.AddEdge(&vertices[4], &vertices[6], 1);
    graph.AddEdge(&vertices[4], &vertices[7], 1);
    graph.AddEdge(&vertices[5], &vertices[7], 1);
    graph.AddEdge(&vertices[7], &vertices[6], 1);

    std::map<std::string, int> distance_map;
    std::map<std::string, std::string> path_map;

    UnweightedShortestPaths(graph, start_vertex, distance_map, path_map);

    Graph::PrintPaths(graph, path_map);

    return 0;
}