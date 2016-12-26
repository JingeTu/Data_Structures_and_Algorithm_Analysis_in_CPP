//
// Created by 涂金戈 on 25/12/2016.
//

#include "Graph.h"

Graph::Graph() {}

bool Graph::AddVertex(Vertex *vertex) {
    if (CheckVertexIn(vertex))
        return false;

    vertices.push_back(vertex);

    return true;
}

bool Graph::AddEdge(Vertex *start, Vertex *end, const int &weight) {
    // if start vertex and end vertex are the same vertex, just return false.
    if (start == end)
        return false;

    // Check if start vertex and end vertex are in the vertices.
    if (!CheckVertexIn(start) || !CheckVertexIn(end))
        return false;

    start->AddTo(Edge(end, weight));

    return true;
}

const std::vector<Vertex *> Graph::GetVertices() const {
    return vertices;
}

bool Graph::CheckVertexIn(Vertex *vertex) {
    for (Vertex *v : vertices)
        if (v == vertex)
            return true;

    return false;
}

void Graph::PrintPaths(const Graph &graph, const std::map <std::string, std::string> &path_map) {
    const std::vector<Vertex *> &vertices = graph.GetVertices();

    for (Vertex *v : vertices) {
        if ((*path_map.find(v->GetName())).second != "") {
            Graph::PrintPathsHelper(graph, v, path_map, vertices);
            std::cout << '\n';
        } else {
            std::cout << "No path from START to " << v->GetName() << ".\n";
        }
    }
}

void Graph::PrintPathsHelper(const Graph &graph, Vertex *v,
                             const std::map <std::string, std::string> &path_map,
                             const std::vector<Vertex *> &vertices) {
    std::string v_path_name = (*path_map.find(v->GetName())).second;
    if (v_path_name != "") {
        Vertex *v_path;
        for (Vertex *v_temp : vertices) {
            if (v_temp->GetName() == v_path_name) {
                v_path = v_temp;
                break;
            }
        }
        Graph::PrintPathsHelper(graph, v_path, path_map, vertices);
        std::cout << " to ";
    }
    std::cout << v->GetName();
}