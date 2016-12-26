//
// Created by 涂金戈 on 09/12/2016.
//

#include <iostream>
#include <queue>
#include <list>
#include <climits>
#include <vector>
#include <map>
#include "../Common_Tools/Graph.h"

void AcyclicDijkstra(const Graph &graph, Vertex *s,
                      std::map<std::string, int> &distance_map,
                      std::map<std::string, std::string> &path_map,
                      std::map<std::string, int> indegree_map) {
    const std::vector<Vertex *> &vertices = graph.GetVertices();
    std::queue<Vertex *> q;
    int counter = 0;

    std::map<std::string, bool> known_map;

    for (Vertex *v : vertices) {
        distance_map.insert(std::make_pair(v->GetName(), INT_MAX / 2));
        known_map.insert(std::make_pair(v->GetName(), false));
        path_map.insert(std::make_pair(v->GetName(), ""));
    }

    (*distance_map.find(s->GetName())).second = 0;
    q.push(s);

    for (Vertex *v : vertices) {
        const int &v_indegree = (*indegree_map.find(v->GetName())).second;
        if (v_indegree == 0 && v != s) // if the vertex has a indegree of 0, there is no path from start vertex to it
            q.push(v);
    }

    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        (*known_map.find(v->GetName())).second = true;

        const int &v_distance = (*distance_map.find(v->GetName())).second;

        const std::list<Edge> &to = v->GetTos();

        for (const Edge &w : to) {
            const int &w_distance = (*distance_map.find(w.vertex->GetName())).second;

            if (w_distance > v_distance + w.weight) {
                (*distance_map.find(w.vertex->GetName())).second = v_distance + w.weight;
                (*path_map.find(w.vertex->GetName())).second = v->GetName();
            }
            (*indegree_map.find(w.vertex->GetName())).second -= 1;

            if ((*indegree_map.find(w.vertex->GetName())).second == 0)
                q.push(w.vertex);
        }
    }
}

int main() {

    Graph graph;

    Vertex *vertices = new Vertex[8];
    std::map<std::string, int> indegree_map;

    for (int i = 1; i <= 7; ++i) {
        vertices[i].SetName(std::string("v").append(std::to_string(i)));
        graph.AddVertex(&vertices[i]);
        indegree_map.insert(std::make_pair(vertices[i].GetName(), 0));
    }

    graph.AddEdge(&vertices[1], &vertices[2], 2);
    graph.AddEdge(&vertices[1], &vertices[4], 1);
    graph.AddEdge(&vertices[1], &vertices[3], 1);
    graph.AddEdge(&vertices[2], &vertices[4], 3);
    graph.AddEdge(&vertices[2], &vertices[5], 10);
    graph.AddEdge(&vertices[3], &vertices[6], 5);
    graph.AddEdge(&vertices[4], &vertices[3], 2);
    graph.AddEdge(&vertices[4], &vertices[5], 2);
    graph.AddEdge(&vertices[4], &vertices[6], 8);
    graph.AddEdge(&vertices[4], &vertices[7], 4);
    graph.AddEdge(&vertices[5], &vertices[7], 6);
    graph.AddEdge(&vertices[7], &vertices[6], 1);

    (*indegree_map.find(vertices[2].GetName())).second = 1;
    (*indegree_map.find(vertices[3].GetName())).second = 2;
    (*indegree_map.find(vertices[4].GetName())).second = 2;
    (*indegree_map.find(vertices[5].GetName())).second = 2;
    (*indegree_map.find(vertices[6].GetName())).second = 3;
    (*indegree_map.find(vertices[7].GetName())).second = 2;

    std::map<std::string, int> distance_map;
    std::map<std::string, std::string> path_map;
    AcyclicDijkstra(graph, &vertices[1], distance_map, path_map, indegree_map);

    Graph::PrintPaths(graph, path_map);

    return 0;
}