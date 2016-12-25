//
// Created by 涂金戈 on 09/12/2016.
//

#include <iostream>
#include <vector>
#include <list>
#include <cstdio>

class Vertex;

struct Edge {
    Vertex *vertex;
    int weight;
    std::string name_;

    Edge(Vertex *to, const int &weight, const std::string &name = "") : vertex{to}, weight{weight}, name_{} {}
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

    void AddTo(const Edge &to_edge) {
        std::list<Edge>::iterator it = to_.begin();
        std::list<Edge>::const_iterator end = to_.end();
        while (it != end) {
            if ((*it++).vertex == to_edge.vertex)
                return;
        }
        to_.push_back(to_edge);
        to_edge.vertex->AddFrom(Edge(this, to_edge.weight));
    }

    const std::list<Edge> &GetTos() {
        return to_;
    }

    const std::list<Edge> &GetFroms() {
        return from_;
    }

    void PrintAdjs() {
        std::list<Edge>::iterator it = to_.begin();
        std::list<Edge>::const_iterator end = to_.end();
        while (it != end) {
            std::cout << (*it++).vertex->GetName() << " ";
        }
        std::cout << "\n";
    }

private:

    void AddFrom(const Edge &from_edge) {
        std::list<Edge>::iterator it = from_.begin();
        std::list<Edge>::const_iterator end = from_.end();
        while (it != end) {
            if ((*it++).vertex == from_edge.vertex)
                return;
        }
        from_.push_back(from_edge);
    }

    std::string name_;
    std::list<Edge> to_;
    std::list<Edge> from_;
    int dist_;
    bool known_;
    Vertex *path_;
};

int EarliestCompletionTime(std::vector<Vertex *> graph, Vertex *start, Vertex *end) {

    for (Vertex *v : graph) {
        v->SetDist(-INT_MAX / 2);
        v->SetKnown(false);
    }

    start->SetDist(0);
    int known_count = 0;

    while (known_count < graph.size()) {
        Vertex *the_maximum = nullptr;
        int dv_max = -INT_MAX / 2;
        for (Vertex *v : graph) {
            if (!v->GetKnown() && v->GetDist() > dv_max) {
                the_maximum = v;
                dv_max = v->GetDist();
            }
        }

        the_maximum->SetKnown(true);
        ++known_count;

        const auto to = the_maximum->GetTos();
        for (const Edge &e : to) {
            if (!e.vertex->GetKnown() && e.vertex->GetDist() < the_maximum->GetDist() + e.weight) {
                e.vertex->SetDist(the_maximum->GetDist() + e.weight);
            }
        }
    }

    return end->GetDist();
}

void LatestCompletionTime(std::vector<Vertex *> graph, Vertex *end) {
    for (Vertex *v: graph) {
        v->SetKnown(false);
    }

    end->SetDist(end->GetDist());
    int known_count = 0;

    while (known_count < graph.size()) {
        Vertex *the_maximum = nullptr;
        int dv_max = -INT_MAX / 2;
        for (Vertex *v :graph) {
            if (!v->GetKnown() && v->GetDist() > dv_max) {
                const auto to = v->GetTos();
                // The selected vertex should have all it's 'to vertices' known.
                bool all_known = true;
                for (const Edge &te : to) {
                    if (!te.vertex->GetKnown()) {
                        all_known = false;
                        break;
                    }
                }
                if (all_known) {
                    the_maximum = v;
                    dv_max = v->GetDist();
                }
            }
        }

        the_maximum->SetKnown(true);
        ++known_count;

        const auto from = the_maximum->GetFroms();
        for (const Edge &fe : from) {
            if (!fe.vertex->GetKnown()) {
                const auto to = fe.vertex->GetTos();
                int dv_min = INT_MAX / 2;
                for (const Edge &te : to) {
                    if (te.vertex->GetKnown() && te.vertex->GetDist() - te.weight < dv_min)
                        dv_min = te.vertex->GetDist() - te.weight;
                }
                fe.vertex->SetDist(dv_min);
            }
        }
    }
}

int main() {

    // Activity-node graph
//    Vertex start("start");
//    Vertex A("A");
//    A.SetDist(3);
//    Vertex B("B");
//    B.SetDist(2);
//    Vertex C("C");
//    C.SetDist(3);
//    Vertex D("D");
//    D.SetDist(2);
//    Vertex E("E");
//    E.SetDist(1);
//    Vertex F("F");
//    F.SetDist(3);
//    Vertex G("G");
//    G.SetDist(2);
//    Vertex H("H");
//    H.SetDist(1);
//    Vertex K("K");
//    K.SetDist(4);
//    Vertex finish("finish");
//
//    start.AddTo(Edge(&A, 1));
//    start.AddTo(Edge(&B, 1));
//    A.AddTo(Edge(&C, 1));
//    A.AddTo(Edge(&D, 1));
//    B.AddTo(Edge(&D, 1));
//    B.AddTo(Edge(&E, 1));
//    C.AddTo(Edge(&F, 1));
//    D.AddTo(Edge(&F, 1));
//    D.AddTo(Edge(&G, 1));
//    E.AddTo(Edge(&G, 1));
//    E.AddTo(Edge(&K, 1));
//    F.AddTo(Edge(&H, 1));
//    G.AddTo(Edge(&H, 1));
//    H.AddTo(Edge(&finish, 1));
//    K.AddTo(Edge(&H, 1));
//
//    std::vector<Vertex *> vertex_vec;
//    vertex_vec.push_back(&start);
//    vertex_vec.push_back(&A);
//    vertex_vec.push_back(&B);
//    vertex_vec.push_back(&C);
//    vertex_vec.push_back(&D);
//    vertex_vec.push_back(&E);
//    vertex_vec.push_back(&F);
//    vertex_vec.push_back(&G);
//    vertex_vec.push_back(&H);
//    vertex_vec.push_back(&K);
//    vertex_vec.push_back(&finish);

    // Event-node graph
    Vertex node_1("1");
    Vertex node_2("2");
    Vertex node_3("3");
    Vertex node_4("4");
    Vertex node_5("5");
    Vertex node_6("6");
    Vertex node_7("7");
    Vertex node_8("8");
    Vertex node_9("9");
    Vertex node_10("10");
    Vertex node_6_p("6'");
    Vertex node_7_p("7'");
    Vertex node_8_p("8'");
    Vertex node_10_p("10'");

    node_1.AddTo(Edge(&node_2, 3));
    node_1.AddTo(Edge(&node_3, 2));
    node_2.AddTo(Edge(&node_6_p, 0));
    node_2.AddTo(Edge(&node_4, 3));
    node_3.AddTo(Edge(&node_6_p, 0));
    node_3.AddTo(Edge(&node_5, 1));
    node_4.AddTo(Edge(&node_7_p, 0));
    node_5.AddTo(Edge(&node_8_p, 0));
    node_5.AddTo(Edge(&node_9, 4));
    node_6.AddTo(Edge(&node_7_p, 0));
    node_6.AddTo(Edge(&node_8_p, 0));
    node_6_p.AddTo(Edge(&node_6, 2));
    node_7.AddTo(Edge(&node_10_p, 0));
    node_7_p.AddTo(Edge(&node_7, 3));
    node_8.AddTo(Edge(&node_10_p, 0));
    node_8_p.AddTo(Edge(&node_8, 2));
    node_9.AddTo(Edge(&node_10_p, 0));
    node_10_p.AddTo(Edge(&node_10, 1));

    std::vector<Vertex *> vertex_vec;
    vertex_vec.push_back(&node_1);
    vertex_vec.push_back(&node_2);
    vertex_vec.push_back(&node_3);
    vertex_vec.push_back(&node_4);
    vertex_vec.push_back(&node_5);
    vertex_vec.push_back(&node_6);
    vertex_vec.push_back(&node_7);
    vertex_vec.push_back(&node_8);
    vertex_vec.push_back(&node_9);
    vertex_vec.push_back(&node_10);
    vertex_vec.push_back(&node_6_p);
    vertex_vec.push_back(&node_7_p);
    vertex_vec.push_back(&node_8_p);
    vertex_vec.push_back(&node_10_p);

    int result = EarliestCompletionTime(vertex_vec, &node_1, &node_10);

    LatestCompletionTime(vertex_vec, &node_10);

    return 0;
}