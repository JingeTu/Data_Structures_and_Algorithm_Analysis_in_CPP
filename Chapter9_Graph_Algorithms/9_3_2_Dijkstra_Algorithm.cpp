//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <list>
#include <vector>
#include <climits>
#include <queue>

class Vertex;

struct ToEdge {
    Vertex *to_vertex_;
    int weight_;

    ToEdge(Vertex *to, const int &weight) : to_vertex_{to}, weight_{weight} {}
};

class Vertex {
public:
    Vertex(std::string name) : name_{name}, path_{nullptr}, known_{false} {}

    std::string GetName() { return name_; }

    Vertex *GetPath() const {
        return path_;
    }

    void SetPath(Vertex *path) {
        this->path_ = path;
    }

    int GetDist() const {
        return dist_;
    }

    void SetDist(const int &dist) {
        this->dist_ = dist;
    }

    bool GetKnown() {
        return known_;
    }

    void SetKnown(const bool known) {
        this->known_ = known;
    }

    void AddTo(const ToEdge &to_edge) {
        std::list<ToEdge>::iterator it = to_.begin();
        std::list<ToEdge>::const_iterator end = to_.end();
        while (it != end) {
            if ((*it++).to_vertex_ == to_edge.to_vertex_)
                return;
        }
        to_.push_back(to_edge);
    }

    const std::list<ToEdge> &GetTos() {
        return to_;
    }

    void PrintAdjs() {
        std::list<ToEdge>::iterator it = to_.begin();
        std::list<ToEdge>::const_iterator end = to_.end();
        while (it != end) {
            std::cout << (*it++).to_vertex_->GetName() << " ";
        }
        std::cout << "\n";
    }

private:
    std::string name_;
    std::list<ToEdge> to_;
    int dist_;
    bool known_;
    Vertex *path_;
};

void dijkstra(std::vector<Vertex *> graph, Vertex *s) {
    for (auto v: graph) {
        v->SetDist(INT_MAX / 2); // ATTENTION here, in case of the_minimum->GetDist() + x.weight_ overflow, here use INT_MAX / 2 instead of INT_MAX
        v->SetKnown(false);
    }

    s->SetDist(0);
    int known_count = 0;

    while (known_count < graph.size()) {
        Vertex *the_minimum = nullptr;
        int dv_min = INT_MAX / 2;
        for (auto &v: graph) {
            if (!v->GetKnown() && v->GetDist() <= dv_min) {
                the_minimum = v;
                dv_min = v->GetDist();
            }
        }

        the_minimum->SetKnown(true);
        ++known_count;

        const auto &to = the_minimum->GetTos();
        for (auto &x: to) {
            if (x.to_vertex_->GetDist() > the_minimum->GetDist() + x.weight_) {
                x.to_vertex_->SetDist(the_minimum->GetDist() + x.weight_);
                x.to_vertex_->SetPath(the_minimum);
            }
        }
    }
}

struct cmp {
    bool operator()(const Vertex *a, const Vertex *b) {
        return a->GetDist() < b->GetDist();
    }
};

void dijkstra_heap(std::vector<Vertex *> graph, Vertex *s) {
    // wait for more powerful priority queue implemented by myself, Need decreaseKey
    // maybe use boost, but this will be not portable
    for (auto v: graph) {
        v->SetDist(INT_MAX);
        v->SetKnown(false);
    }

    s->SetDist(0);
    int known_count = 0;

    std::priority_queue<Vertex *, std::vector<Vertex *>, cmp> unknowns;
    for (auto &v: graph) {
        unknowns.push(v);
    }

    while (known_count < graph.size()) {
        Vertex *the_minimum = nullptr;
        int dv_min = INT_MAX;
        for (auto &v: graph) {
            if (!v->GetKnown() && v->GetDist() < dv_min) {
                the_minimum = v;
                dv_min = v->GetDist();
            }
        }

        the_minimum->SetKnown(true);
        ++known_count;

        const auto &to = the_minimum->GetTos();
        for (auto &x: to) {
            if (x.to_vertex_->GetDist() > the_minimum->GetDist() + x.weight_) {
                x.to_vertex_->SetDist(the_minimum->GetDist() + x.weight_);
                x.to_vertex_->SetPath(the_minimum);

            }
        }
    }
}

void PrintPathsHelper(const std::vector<Vertex *> &graph, Vertex *v) {
    if (v->GetPath() != nullptr) {
        PrintPathsHelper(graph, v->GetPath());
        std::cout << " to ";
    }
    std::cout << v->GetName();
}

void PrintPaths(const std::vector<Vertex *> &graph) {
    for (auto &v : graph) {
        if (v->GetPath() != nullptr) {
            PrintPathsHelper(graph, v);
            std::cout << "\tPath Length: " << v->GetDist();
            std::cout << '\n';
        }
        else {
            std::cout << "No path from START to " << v->GetName() << ".\n";
        }
    }
}

int main() {

    Vertex v1("v1");
    Vertex v2("v2");
    Vertex v3("v3");
    Vertex v4("v4");
    Vertex v5("v5");
    Vertex v6("v6");
    Vertex v7("v7");

    // cyclic graph
//    v1.AddTo(ToEdge(&v2, 2));
//    v1.AddTo(ToEdge(&v4, 1));
//    v2.AddTo(ToEdge(&v4, 3));
//    v2.AddTo(ToEdge(&v5, 10));
//    v3.AddTo(ToEdge(&v1, 4));
//    v3.AddTo(ToEdge(&v6, 5));
//    v4.AddTo(ToEdge(&v3, 2));
//    v4.AddTo(ToEdge(&v5, 2));
//    v4.AddTo(ToEdge(&v6, 8));
//    v4.AddTo(ToEdge(&v7, 4));
//    v5.AddTo(ToEdge(&v7, 6));
//    v7.AddTo(ToEdge(&v6, 1));

    // acyclic graph
    v1.AddTo(ToEdge(&v2, 2));
    v1.AddTo(ToEdge(&v4, 1));
    v1.AddTo(ToEdge(&v3, 4));
    v2.AddTo(ToEdge(&v4, 3));
    v2.AddTo(ToEdge(&v5, 10));
    v3.AddTo(ToEdge(&v6, 5));
    v4.AddTo(ToEdge(&v3, 2));
    v4.AddTo(ToEdge(&v5, 2));
    v4.AddTo(ToEdge(&v6, 8));
    v4.AddTo(ToEdge(&v7, 4));
    v5.AddTo(ToEdge(&v7, 6));
    v7.AddTo(ToEdge(&v6, 1));

    std::vector<Vertex *> vertex_vec;
    vertex_vec.reserve(7);
    vertex_vec.push_back(&v1);
    vertex_vec.push_back(&v2);
    vertex_vec.push_back(&v3);
    vertex_vec.push_back(&v4);
    vertex_vec.push_back(&v5);
    vertex_vec.push_back(&v6);
    vertex_vec.push_back(&v7);

    dijkstra(vertex_vec, &v3);

    PrintPaths(vertex_vec);

    return 0;
}