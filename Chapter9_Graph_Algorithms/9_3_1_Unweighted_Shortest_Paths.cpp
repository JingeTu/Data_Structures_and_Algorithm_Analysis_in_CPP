//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <queue>

class Vertex {
public:
    Vertex(std::string name) : name_{name}, path_{nullptr} {}

    std::string GetName() { return name_; }

    Vertex *GetPath() const {
        return path_;
    }

    void SetPath(Vertex *path) {
        this->path_ = path;
    }

    int GetDist() {
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

    void AddTo(Vertex *adjVertex) {
        std::list<Vertex *>::iterator it = to_.begin();
        std::list<Vertex *>::const_iterator end = to_.end();
        while (it != end) {
            if (*it++ == adjVertex)
                return;
        }
        to_.push_back(adjVertex);
    }

    const std::list<Vertex *> &GetTos() {
        return to_;
    }

    void PrintAdjs() {
        std::list<Vertex *>::iterator it = to_.begin();
        std::list<Vertex *>::const_iterator end = to_.end();
        while (it != end) {
            std::cout << (*it)->GetName() << " ";
            ++it;
        }
        std::cout << "\n";
    }

private:

    std::string name_;
    std::list<Vertex *> to_;
    int dist_;
    bool known_;
    Vertex *path_;
};

void unweighted(std::vector<Vertex *> &graph, Vertex *s) {
    for (auto &v : graph) {
        v->SetDist(INT_MAX);
        v->SetKnown(false);
    }

    s->SetDist(0);

    for (int curr_dist = 0; curr_dist < graph.size(); ++curr_dist)
        for (auto &v : graph)
            if (!v->GetKnown() && v->GetDist() == curr_dist) {
                v->SetKnown(true);
                auto &to = v->GetTos();

                for (auto &w : to)
                    if (w->GetDist() == INT_MAX) {
                        w->SetDist(curr_dist + 1);
                        w->SetPath(v);
                    }
            }
}

void unweighted_queue(std::vector<Vertex *> &graph, Vertex *s) {
    for (auto &v : graph) {
        v->SetDist(INT_MAX);
        v->SetKnown(false);
    }

    s->SetDist(0);
    std::queue<Vertex *> q;
    q.push(s);

    while (!q.empty()) {
        auto & v = q.front();
        q.pop();
        v->SetKnown(true);

        auto &to = v->GetTos();
        for (auto &w : to)
            if (w->GetDist() == INT_MAX) {
                w->SetDist(v->GetDist() + 1);
                w->SetPath(v);
                q.push(w);
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

    v1.AddTo(&v2);
    v1.AddTo(&v4);
    v2.AddTo(&v4);
    v2.AddTo(&v5);
    v3.AddTo(&v1);
    v3.AddTo(&v6);
    v4.AddTo(&v3);
    v4.AddTo(&v5);
    v4.AddTo(&v6);
    v4.AddTo(&v7);
    v5.AddTo(&v7);
    v7.AddTo(&v6);

    std::vector<Vertex *> vertex_vec;
    vertex_vec.reserve(7);
    vertex_vec.push_back(&v1);
    vertex_vec.push_back(&v2);
    vertex_vec.push_back(&v3);
    vertex_vec.push_back(&v4);
    vertex_vec.push_back(&v5);
    vertex_vec.push_back(&v6);
    vertex_vec.push_back(&v7);

//    unweighted(vertex_vec, &v3);
    /*
v3 to v1	Path Length: 1
v3 to v1 to v2	Path Length: 2
v3 to v1 to v4	Path Length: 2
v3 to v1 to v2 to v5	Path Length: 3
v3 to v6	Path Length: 1
v3 to v1 to v4 to v7	Path Length: 3
     */
    unweighted_queue(vertex_vec, &v3);
   /*
v3 to v1	Path Length: 1
v3 to v1 to v2	Path Length: 2
v3 to v1 to v4	Path Length: 2
v3 to v1 to v2 to v5	Path Length: 3
v3 to v6	Path Length: 1
v3 to v1 to v4 to v7	Path Length: 3
    */

    PrintPaths(vertex_vec);

    return 0;
}