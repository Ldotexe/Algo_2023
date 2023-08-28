#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cinttypes>

class Trie {
public:
    static constexpr int64_t kTnull = -1;
    struct Node {
        Node(char symbol, int64_t parent) : symbol(symbol), parent(parent){};
        std::unordered_map<char, int64_t> children;
        int64_t parent{-1};
        int64_t suff_link{-1};
        int64_t terminal_link{-1};
        int32_t pattern_{-1};
        char symbol;
        bool is_terminal;
    };

    Trie() : nodes_(1, {'\0', -1}) {
    }

    void Add(int32_t pattern, const std::string& key) {
        int64_t v = 0;
        for (auto ch : key) {
            if (nodes_[v].children.find(ch) == nodes_[v].children.end()) {
                nodes_.emplace_back(ch, v);
                nodes_[v].children[ch] = static_cast<int64_t>(nodes_.size() - 1);
            }
            v = nodes_[v].children[ch];
        }
        nodes_[v].pattern_ = pattern;
        nodes_[v].is_terminal = true;
    }

    Node& Get(int64_t index) {
        return nodes_[index];
    }

private:
    std::vector<Node> nodes_;
};

class AhoCorasikAutomation {
public:
    explicit AhoCorasikAutomation(const std::vector<std::string>& patterns) : patterns_(patterns) {
        int32_t i = 0;
        for (auto pattern : patterns) {
            trie_.Add(i++, pattern);
        }
    }

    std::vector<std::string> MakeStep(char symbol) {
        state_ = CalcStep(state_, symbol);
        return ExtractMatches();
    }

private:
    std::vector<std::string> ExtractMatches() {
        int64_t v = state_;
        std::vector<std::string> ans;
        while (v != 0) {
            auto& node = trie_.Get(v);
            if (node.is_terminal) {
                ans.emplace_back(patterns_[node.pattern_]);
            }
            v = GetTerminalLink(v);
        }
        return ans;
    }
    int64_t CalcStep(int64_t node, char symbol) {
        auto& v = trie_.Get(node);
        if (v.children.find(symbol) != v.children.end()) {
            return v.children[symbol];
        }
        if (node == 0) {
            return 0;
        }
        return CalcStep(GetSuffLink(node), symbol);
    }

    int64_t GetTerminalLink(int64_t node) {
        if (node == 0 || trie_.Get(node).parent == 0) {
            trie_.Get(node).terminal_link = 0;
            return 0;
        }
        if (trie_.Get(node).terminal_link != -1) {
            return trie_.Get(node).terminal_link;
        }
        int64_t v = GetSuffLink(node);
        while (v != 0 && !trie_.Get(v).is_terminal) {
            v = GetSuffLink(v);
        }

        trie_.Get(node).terminal_link = v;
        return v;
    }

    int64_t GetSuffLink(int64_t node) {
        if (node == 0 || trie_.Get(node).parent == 0) {
            return 0;
        }
        auto& v = trie_.Get(node);
        if (v.suff_link != -1) {
            return v.suff_link;
        }
        v.suff_link = CalcStep(GetSuffLink(v.parent), v.symbol);
        return v.suff_link;
    }
    int64_t state_{0};
    Trie trie_;
    std::vector<std::string> patterns_;
};

int main() {
    AhoCorasikAutomation ath({"a", "aa", "fef", "ef"});
    std::string text = "abababababaaafefffefeffefeefefiheihfeuihfifiuhefheuhia";
    for (auto ch : text) {
        auto v = ath.MakeStep(ch);
        if (!v.empty()) {
            for (auto w : v) {
                std::cout << w << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}