//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <list>
#include <vector>
#include <climits>
#include <queue>
#include <map>
#include "../Common_Tools/Graph.h"

void dijkstra(const Graph &graph, Vertex *s,
              std::map<std::string, int> &distance_map,
              std::map<std::string, std::string> &path_map) {
    const std::vector<Vertex *> &vertices = graph.GetVertices();
    const int vertex_num = vertices.size();

    std::map<std::string, bool> known_map;

    for (Vertex *v: vertices) {
        distance_map.insert(std::make_pair(v->GetName(), INT_MAX / 2));
        path_map.insert(std::make_pair(v->GetName(), ""));
        known_map.insert(std::make_pair(v->GetName(), false));
    }

    (*distance_map.find(s->GetName())).second = 0;
    int known_count = 0;

    while (known_count < vertex_num) {
        Vertex *the_minimum = nullptr;
        int dv_min = INT_MAX / 2;
        for (Vertex *v: vertices) {
            const bool &known = (*known_map.find(v->GetName())).second;
            if (!known) {
                const int &distance = (*distance_map.find(v->GetName())).second;
                if (distance <= dv_min) {
                    the_minimum = v;
                    dv_min = distance;
                }
            }
        }

        (*known_map.find(the_minimum->GetName())).second = true;
        ++known_count;

        const int &distance = (*distance_map.find(the_minimum->GetName())).second;

        const std::list<Edge> &to = the_minimum->GetTos();
        for (const Edge &x: to) {
            const int &x_distance = (*distance_map.find(x.vertex->GetName())).second;
            if (x_distance > distance + x.weight) {
                (*distance_map.find(x.vertex->GetName())).second = distance + x.weight;
                (*path_map.find(x.vertex->GetName())).second = the_minimum->GetName();
            }
        }
    }
}

void dijkstra_heap(const Graph &graph, Vertex *s,
                   std::map<std::string, int> &distance_map,
                   std::map<std::string, std::string> &path_map) {

}

int main() {

    Graph graph;

    Vertex *vertices = new Vertex[8];

    for (int i = 1; i <= 7; ++i) {
        vertices[i].SetName(std::string("v").append(std::to_string(i)));
        graph.AddVertex(&vertices[i]);
    }

    graph.AddEdge(&vertices[1], &vertices[2], 2);
    graph.AddEdge(&vertices[1], &vertices[4], 1);
    graph.AddEdge(&vertices[2], &vertices[4], 3);
    graph.AddEdge(&vertices[2], &vertices[5], 10);
    graph.AddEdge(&vertices[3], &vertices[1], 4);
    graph.AddEdge(&vertices[3], &vertices[6], 5);
    graph.AddEdge(&vertices[4], &vertices[3], 2);
    graph.AddEdge(&vertices[4], &vertices[5], 2);
    graph.AddEdge(&vertices[4], &vertices[6], 8);
    graph.AddEdge(&vertices[4], &vertices[7], 4);
    graph.AddEdge(&vertices[5], &vertices[7], 6);
    graph.AddEdge(&vertices[7], &vertices[6], 1);

    std::map<std::string, int> distance_map;
    std::map<std::string, std::string> path_map;
    dijkstra(graph, &vertices[1], distance_map, path_map);

    Graph::PrintPaths(graph, path_map);

    return 0;
}