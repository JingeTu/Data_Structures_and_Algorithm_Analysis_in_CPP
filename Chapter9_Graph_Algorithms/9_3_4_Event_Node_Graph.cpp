//
// Created by 涂金戈 on 09/12/2016.
//

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include "../Common_Tools/Graph.h"

int EarliestCompletionTime(const Graph &graph, Vertex *start, Vertex *end,
                           std::map<std::string, int> &earliest_completion_time_map) {
    auto &result_map = earliest_completion_time_map;
    const std::vector<Vertex *> &vertices = graph.GetVertices();
    const int vertex_num = vertices.size();

    std::map<std::string, bool> known_map;

    for (Vertex *v : vertices) {
        known_map.insert(std::make_pair(v->GetName(), false));
        result_map.insert(std::make_pair(v->GetName(), -INT_MAX / 2));
    }

    (*result_map.find(start->GetName())).second = 0;
    int known_count = 0;

    while (known_count < vertex_num) {
        Vertex *the_maximum = nullptr;
        int dv_max = -INT_MAX / 2;
        for (Vertex *v : vertices) {
            const bool &known = (*known_map.find(v->GetName())).second;
            const int &distance = (*result_map.find(v->GetName())).second;
            if (!known && distance > dv_max) {
                the_maximum = v;
                dv_max = distance;
            }
        }

        (*known_map.find(the_maximum->GetName())).second = true;
        ++known_count;

        const int &the_maximum_distance = (*result_map.find(the_maximum->GetName())).second;

        const auto to = the_maximum->GetTos();
        for (const Edge &e : to) {
            const bool &known = (*known_map.find(e.vertex->GetName())).second;
            int &distance = (*result_map.find(e.vertex->GetName())).second;
            if (!known && distance < the_maximum_distance + e.weight) {
                distance = the_maximum_distance + e.weight;
            }
        }
    }

    return (*result_map.find(end->GetName())).second;;
}

void LatestCompletionTime(const Graph &graph, Vertex *end,
                          const std::map<std::string, int> &earliest_completion_time_map,
                          std::map<std::string, int> &lastest_completion_time_map) {
    const auto &ect_map = earliest_completion_time_map;
    auto &result_map = lastest_completion_time_map;

    const std::vector<Vertex *> &vertices = graph.GetVertices();
    const int vertex_num = vertices.size();

    std::map<std::string, bool> known_map;

    for (Vertex *v: vertices) {
        known_map.insert(std::make_pair(v->GetName(), false));
        result_map.insert(std::make_pair(v->GetName(), -INT_MAX / 2));
    }

    (*result_map.find(end->GetName())).second = (*ect_map.find(end->GetName())).second;
    int known_count = 0;

    while (known_count < vertex_num) {
        Vertex *the_maximum = nullptr;
        int dv_max = -INT_MAX / 2;
        for (Vertex *v : vertices) {
            const bool &v_known = (*known_map.find(v->GetName())).second;
            const int &v_distance = (*result_map.find(v->GetName())).second;
            if (!v_known && v_distance > dv_max) {
                const auto to = v->GetTos();
                // The selected vertex should have all it's 'to vertices' known.
                bool all_known = true;
                for (const Edge &te : to) {
                    const bool &known = (*known_map.find(te.vertex->GetName())).second;
                    if (!known) {
                        all_known = false;
                        break;
                    }
                }
                if (all_known) {
                    the_maximum = v;
                    dv_max = (*result_map.find(v->GetName())).second;
                }
            }
        }

        (*known_map.find(the_maximum->GetName())).second = true;
        ++known_count;

        const auto from = the_maximum->GetFroms();
        for (const Edge &fe : from) {
            const bool fev_known = (*known_map.find(fe.vertex->GetName())).second;
            int &fev_distance = (*result_map.find(fe.vertex->GetName())).second;
            if (!fev_known) {
                const auto to = fe.vertex->GetTos();
                int dv_min = INT_MAX / 2;
                for (const Edge &te : to) {
                    const bool &tev_known = (*known_map.find(te.vertex->GetName())).second;
                    const int &tev_distance = (*result_map.find(te.vertex->GetName())).second;
                    if (tev_known && tev_distance - te.weight < dv_min)
                        dv_min = tev_distance - te.weight;
                }
                (*result_map.find(fe.vertex->GetName())).second = dv_min;
            }
        }
    }
}

template<typename T1, typename T2>
void PrintMap(const std::map<T1, T2> &the_map) {
    for (auto it : the_map) {
        std::cout << it.first << "\t" << it.second << "\n";
    }
}

int main() {

    Graph graph;

    Vertex *start_vertex;
    Vertex *end_vertex;
    Vertex *vertices = new Vertex[15];

    // Add Vertices
    for (int i = 1; i <= 10; ++i) { // discard the first element
        vertices[i].SetName(std::to_string(i));
        graph.AddVertex(&vertices[i]);

        if (i == 1)
            start_vertex = &vertices[i];
        if (i == 10)
            end_vertex = &vertices[i];
    }
    vertices[11].SetName("6'");
    vertices[12].SetName("7'");
    vertices[13].SetName("8'");
    vertices[14].SetName("10'");
    graph.AddVertex(&vertices[11]);
    graph.AddVertex(&vertices[12]);
    graph.AddVertex(&vertices[13]);
    graph.AddVertex(&vertices[14]);

    // Add Edges
    graph.AddEdge(&vertices[1], &vertices[2], 3);
    graph.AddEdge(&vertices[1], &vertices[3], 2);
    graph.AddEdge(&vertices[2], &vertices[11], 0);
    graph.AddEdge(&vertices[2], &vertices[4], 3);
    graph.AddEdge(&vertices[3], &vertices[11], 0);
    graph.AddEdge(&vertices[3], &vertices[5], 1);
    graph.AddEdge(&vertices[4], &vertices[12], 0);
    graph.AddEdge(&vertices[5], &vertices[13], 0);
    graph.AddEdge(&vertices[5], &vertices[9], 4);
    graph.AddEdge(&vertices[6], &vertices[12], 0);
    graph.AddEdge(&vertices[6], &vertices[13], 0);
    graph.AddEdge(&vertices[11], &vertices[6], 2);
    graph.AddEdge(&vertices[7], &vertices[14], 0);
    graph.AddEdge(&vertices[12], &vertices[7], 3);
    graph.AddEdge(&vertices[8], &vertices[14], 0);
    graph.AddEdge(&vertices[13], &vertices[8], 2);
    graph.AddEdge(&vertices[9], &vertices[14], 0);
    graph.AddEdge(&vertices[14], &vertices[10], 1);

    std::map<std::string, int> earliest_completion_time_map;
    EarliestCompletionTime(graph, start_vertex,
                           end_vertex, earliest_completion_time_map);

    std::map<std::string, int> latest_completion_time_map;
    LatestCompletionTime(graph, end_vertex,
                         earliest_completion_time_map, latest_completion_time_map);

    std::cout << "Earliest Completion Time: \n";
    PrintMap(earliest_completion_time_map);

    std::cout << "Latest Completion Time: \n";
    PrintMap(latest_completion_time_map);

    return 0;
}