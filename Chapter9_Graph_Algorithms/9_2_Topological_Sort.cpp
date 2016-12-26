//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include "../Common_Tools/Graph.h"

void TopoSort(const Graph &graph,
              std::vector<std::string> &topo_order,
              std::map<std::string, int> indegree_map) {
    const std::vector<Vertex *> &vertices = graph.GetVertices();

    std::queue<Vertex *> q;
    int counter = 0;

    for (Vertex *v : vertices) {
        const int &v_indegree =
                (*indegree_map.find(v->GetName())).second;
        if (v_indegree == 0)
            q.push(v);
    }


    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        topo_order.push_back(v->GetName());

        const std::list<Edge> &to = v->GetTos();

        for (const Edge &w : to) {
            const int &w_indegree
                    = (*indegree_map.find(w.vertex->GetName())).second -= 1;
            if (w_indegree == 0)
                q.push(w.vertex);
        }
    }
}

void TopoSortWithStack(const Graph &graph,
                       std::vector<std::string> &topo_order,
                       std::map<std::string, int> indegree_map) {
    const std::vector<Vertex *> &vertices = graph.GetVertices();

    std::stack<Vertex *> s;
    int counter = 0;

    for (Vertex *v : vertices) {
        const int &v_indegree = (*indegree_map.find(v->GetName())).second;
        if (v_indegree == 0)
            s.push(v);
    }

    while (!s.empty()) {
        Vertex *v = s.top();
        s.pop();
        topo_order.push_back(v->GetName());

        const std::list<Edge> &to = v->GetTos();

        for (const Edge &w : to) {
            const int &w_indegree =
                    (*indegree_map.find(w.vertex->GetName())).second -= 1;
            if (w_indegree == 0)
                s.push(w.vertex);
        }
    }
}

int main() {

    Graph graph;
    Vertex *vertices = new Vertex[8];
    std::map<std::string, int> indegree_map;

    // Add Vertices
    for (int i = 1; i <= 7; ++i) { // discard the first element
        vertices[i].SetName(std::to_string(i));
        graph.AddVertex(&vertices[i]);
        indegree_map.insert(std::make_pair(vertices[i].GetName(), 0));
    }
    Vertex *start_vertex = &vertices[3];

    graph.AddEdge(&vertices[1], &vertices[2], 1);
    graph.AddEdge(&vertices[1], &vertices[3], 1);
    graph.AddEdge(&vertices[1], &vertices[4], 1);
    graph.AddEdge(&vertices[2], &vertices[4], 1);
    graph.AddEdge(&vertices[2], &vertices[5], 1);
    graph.AddEdge(&vertices[3], &vertices[6], 1);
    graph.AddEdge(&vertices[4], &vertices[3], 1);
    graph.AddEdge(&vertices[4], &vertices[6], 1);
    graph.AddEdge(&vertices[4], &vertices[7], 1);
    graph.AddEdge(&vertices[5], &vertices[4], 1);
    graph.AddEdge(&vertices[5], &vertices[7], 1);
    graph.AddEdge(&vertices[7], &vertices[6], 1);

    (*indegree_map.find(vertices[1].GetName())).second = 0;
    (*indegree_map.find(vertices[2].GetName())).second = 1;
    (*indegree_map.find(vertices[3].GetName())).second = 2;
    (*indegree_map.find(vertices[4].GetName())).second = 3;
    (*indegree_map.find(vertices[5].GetName())).second = 1;
    (*indegree_map.find(vertices[6].GetName())).second = 3;
    (*indegree_map.find(vertices[7].GetName())).second = 2;

    std::vector<std::string> topo_order;
    TopoSort(graph, topo_order, indegree_map); // v1 v2 v5 v4 v7 v3 v6
//    TopoSortWithStack(graph, topo_order, indegree_map); // v1 v2 v5 v4 v7 v3 v6

    std::cout << "Topological Order: \n";
    for (int i = 0; i < topo_order.size(); ++i) {
        std::cout << topo_order[i] << std::endl;
    }

    return 0;
}