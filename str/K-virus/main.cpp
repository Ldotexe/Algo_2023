#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

class Graph {
public:
    Graph() {
        graph_.resize(1);
    }

    void AddVirus(std::vector<uint64_t> virus) {
        int v = 0; // сначал смотрим корень
        for (uint64_t bit : virus) {
            if (graph_[v].next.count(bit) == 0) {
                graph_[v].next[bit] = graph_.size();

                // добавляем нашу новую ноду в граф
                Node n;
                n.parent = v;
                n.bit_parent = bit;
                graph_.push_back(std::move(n));

                // делаем переход в новую вершину
                v = graph_.size() - 1;
            } else {
                v = graph_[v].next[bit];
            }
        }
        graph_[v].term = true;
    }

    uint64_t Suf(uint64_t v) {
        if (graph_[v].suf == -1) {
            if (v == 0 || graph_[v].parent == 0) {
                graph_[v].suf = 0;
            } else {
                graph_[v].suf = Go(Suf(graph_[v].parent), graph_[v].bit_parent);
            }
        }
        return graph_[v].suf;
    }

    int64_t Go(uint64_t v, uint64_t bit) {
        if (graph_[v].go.count(bit) == 0) {
            if (graph_[v].next.count(bit) != 0) {
                graph_[v].go[bit] = graph_[v].next[bit];
            } else {
                if (v == 0)
                    graph_[v].go[bit] = 0;
                else
                    graph_[v].go[bit] = Go(Suf(v), bit);
            }
        }
        return graph_[v].go[bit];
    }

    void Count() {
        for (uint64_t i = 0; i < graph_.size(); ++i) {
            Suf(i);
            Go(i, 0);
            Go(i, 1);
        }
    }

    uint64_t GetTerm(uint64_t v) {
        if (graph_[v].term_link == -1) {
            auto step = Suf(v);
            while (step != 0 && !graph_[step].term) step = Suf(step);
            graph_[v].term_link = step;
        }

        return graph_[v].term_link;
    }

    bool Dfs(uint64_t v) {
        if (used_[v] == 1) {
            used_[v] == 0;
            return true;
        }

        if (used_[v] == 2 || graph_[v].term || GetTerm(v) != 0) {
            return false;
        }

        used_[v] = 1;
        bool result = Dfs(Go(v, 0)) || Dfs(Go(v, 1));
        used_[v] = 2;
        return result;
    }

    std::string Findcycle() {
        used_.resize(graph_.size(), 0);

        if (Dfs(0)) {
            return "TAK";
        }
        return "NIE";
    }


private:
    struct Node {
        std::map<uint64_t, uint64_t> next;
        int64_t parent = -1;
        uint64_t bit_parent;
        bool term = false;
        int64_t suf = -1;
        std::map<uint64_t, uint64_t> go;
        int64_t term_link = -1;
    };

    std::vector<Node> graph_;
    std::vector<uint64_t> used_;
};

int main() {
    Graph g;

    uint64_t n = 0;
    std::cin >> n;
    for (uint64_t i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;

        std::vector<uint64_t> virus;
        for (char c : str) {
            virus.push_back(std::stoi(std::string{c}));
        }
        g.AddVirus(virus);
    }

    g.Count();
    std::cout << g.Findcycle() << '\n';
}