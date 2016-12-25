//
// Created by 涂金戈 on 09/12/2016.
//

#include <iostream>
#include <queue>
#include <list>
#include <climits>
#include <vector>

class Vertex;

struct ToEdge {
    Vertex *to_vertex_;
    int weight_;

    ToEdge(Vertex *to, const int &weight) : to_vertex_{to}, weight_{weight} {}
};

class Vertex {
public:
    Vertex(std::string name) : name_{name}, in_degree_{0}, topNum{0}, path_{nullptr}, known_{false} {}

    std::string GetName() { return name_; }

    Vertex *GetPath() const {
        return path_;
    }

    void SetPath(Vertex *path) {
        this->path_ = path;
    }

    int GetInDegree() {
        return in_degree_;
    }

    void SetTopNum(const int &topNum) {
        this->topNum = topNum;
    }

    int GetTopNum() {
        return topNum;
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
        to_edge.to_vertex_->AddInDegree();
        to_.push_back(to_edge);
    }

    const std::list<ToEdge> &GetTos() {
        return to_;
    }

    void PrintAdjs() {
        std::list<ToEdge>::iterator it = to_.begin();
        std::list<ToEdge>::const_iterator end = to_.end();
        while (it != end) {
            std::cout << (*it).to_vertex_->GetName() << " ";
            ++it;
        }
        std::cout << "\n";
    }

    void SubtractInDegree() {
        --in_degree_;
    }

private:

    void AddInDegree() {
        ++in_degree_;
    }

    std::string name_;
    std::list<ToEdge> to_;
    int dist_;
    bool known_;
    int in_degree_;
    int topNum;
    Vertex *path_;
};

void acyclic_dijkstra(std::vector<Vertex *> &graph, Vertex *s) {
    std::queue<Vertex *> q;
    int counter = 0;

    for (auto &v : graph) {
        v->SetDist(INT_MAX / 2);
        v->SetKnown(false);
    }

    s->SetDist(0);
    q.push(s);

    for (auto &v : graph) {
        if (v->GetInDegree() == 0 &&
            v != s) // if the vertex has a indegree of 0, there is no path from start vertex to it
            q.push(v);
    }

    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        v->SetTopNum(++counter); // not related to dijkstra result, can remove
        v->SetKnown(true);

        const std::list<ToEdge> &to = v->GetTos();

        for (auto &w : to) {
            if (w.to_vertex_->GetDist() > v->GetDist() + w.weight_) {
                w.to_vertex_->SetDist(v->GetDist() + w.weight_);
                w.to_vertex_->SetPath(v);
            }
            w.to_vertex_->SubtractInDegree();
            if (w.to_vertex_->GetInDegree() == 0)
                q.push(w.to_vertex_);
        }
    }
}

void PrintPathsHelper(const std::vector<Vertex *> &graph, Vertex *v) {
    if (v != nullptr && v->GetPath() != nullptr) {
        PrintPathsHelper(graph, v->GetPath());
        std::cout << " to ";
    }
    if (v !== nullptr) {
        std::cout << v->GetName();
    }
}

void PrintPaths(const std::vector<Vertex *> &graph) {
    for (auto &v : graph) {
        if (v->GetPath() != nullptr) {
            PrintPathsHelper(graph, v);
            std::cout << "\tPath Length: " << v->GetDist();
            std::cout << '\n';
        } else {
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

    v1.AddTo(ToEdge(&v2, 2));
    v1.AddTo(ToEdge(&v4, 1));
    v1.AddTo(ToEdge(&v3, 1));
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

    acyclic_dijkstra(vertex_vec, &v1);

    PrintPaths(vertex_vec);

    return 0;
}