//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <list>
#include <queue>
#include <stack>

class Vertex {
public:
    Vertex(std::string name) : name_{name}, in_degree_{0}, topNum{0} {}

    std::string GetName() { return name_; }

    int GetInDegree() {
        return in_degree_;
    }

    void SetTopNum(const int &topNum) {
        this->topNum = topNum;
    }

    int GetTopNum() {
        return topNum;
    }

    void AddTo(Vertex *adjVertex) {
        std::list<Vertex *>::iterator it = to_.begin();
        std::list<Vertex *>::const_iterator end = to_.end();
        while (it != end) {
            if (*it++ == adjVertex)
                return;
        }
        adjVertex->AddInDegree();
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

    void SubtractInDegree() {
        --in_degree_;
    }

private:

    void AddInDegree() {
        ++in_degree_;
    }

    std::string name_;
    std::list<Vertex *> to_;
    int in_degree_;
    int topNum;
};

void topSort(std::vector<Vertex *> &vertex_vec) {
    std::queue<Vertex *> q;
    int counter = 0;

    for (auto &v : vertex_vec)
        if (v->GetInDegree() == 0)
            q.push(v);

    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        v->SetTopNum(++counter);

        const std::list<Vertex *> &to = v->GetTos();

        for (auto w : to) {
            w->SubtractInDegree();
            if (w->GetInDegree() == 0)
                q.push(w);
        }
    }
}

void topSort_stack(std::vector<Vertex *> &vertex_vec) {
    std::stack<Vertex *> s;
    int counter = 0;

    for (auto &v : vertex_vec)
        if (v->GetInDegree() == 0)
            s.push(v);

    while (!s.empty()) {
        Vertex *v = s.top();
        s.pop();
        v->SetTopNum(++counter);

        const std::list<Vertex *> &to = v->GetTos();

        for (auto w : to) {
            w->SubtractInDegree();
            if (w->GetInDegree() == 0)
                s.push(w);
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
    v1.AddTo(&v3);
    v1.AddTo(&v4);
    v2.AddTo(&v4);
    v2.AddTo(&v5);
    v3.AddTo(&v6);
    v4.AddTo(&v3);
    v4.AddTo(&v6);
    v4.AddTo(&v7);
    v5.AddTo(&v4);
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

//    topSort_stack(vertex_vec); // v1 v2 v5 v4 v7 v3 v6
    topSort(vertex_vec);         // v1 v2 v5 v4 v3 v7 v6

    std::vector<std::string> sort_order(7);

    int i;

    for (i = 0; i < vertex_vec.size(); ++i) {
        sort_order[vertex_vec[i]->GetTopNum() - 1] = vertex_vec[i]->GetName();
    }

    for (i = 0; i < sort_order.size(); ++i) {
        std::cout << sort_order[i] << " ";
    }
    std::cout << "\n";

    return 0;
}