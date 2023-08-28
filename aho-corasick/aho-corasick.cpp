#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cinttypes>

class Trie {
public:
    static constexpr int64_t kTnull = -1;
    struct Node {
        Node() = default;
        Node(int64_t parent, char symbol) : parent(parent), symbol(symbol){};
        std::unordered_map<char, int64_t> children;
        int64_t parent{-1};
        char symbol;
        bool is_terminal {false};

        bool HasChild (char symbol) {
            return children.find(symbol) != children.end();
        }
    };

    Trie() : nodes_(1) {}

    int64_t Add(const std::string& key) {
        int64_t v = 0;
        for (auto ch : key) {
            if (!nodes_[v].HasChild(ch)) {
                nodes_.emplace_back(ch, v);
                nodes_[v].children[ch] = static_cast<int64_t>(nodes_.size() - 1);
            }
            v = nodes_[v].children[ch];
        }
        nodes_[v].is_terminal = true;
        return v;
    }

    Node& Get(int64_t index) {
        return nodes_[index];
    }

    size_t NodeCount() {
        return nodes_.size();
    }


private:
    std::vector<Node> nodes_;
};

class AhoCorasikAutomation {
public:
    explicit AhoCorasikAutomation(const std::vector<std::string>& patterns) : patterns_(patterns) {
        int32_t i = 0;
        for (auto pattern : patterns) {
            pattern_mapper_[trie_.Add(pattern)] = i++;
        }
        suff_links_.assign(trie_.NodeCount(), -1);
        term_links_.assign(trie_.NodeCount(), -1);
    }

    std::vector<std::string> MakeStep(char symbol) {
        state_ = CalcStep(state_, symbol);
        return ExtractMatches();
    }

    void ResetState () {
        state_ = 0;
    }

private:
    std::vector<std::string> ExtractMatches() {
        int64_t v = state_;
        std::vector<std::string> ans;
        while (v != 0) {
            auto& node = trie_.Get(v);
            if (node.is_terminal) {
                ans.emplace_back(patterns_[pattern_mapper_[v]]);
            }
            v = GetTerminalLink(v);
        }
        return ans;
    }
    int64_t CalcStep(int64_t node, char symbol) {
        auto& v = trie_.Get(node);
        if (v.HasChild(symbol)) {
            return v.children[symbol];
        }
        if (node == 0) {
            return 0;
        }
        return CalcStep(GetSuffLink(node), symbol);
    }

    int64_t GetTerminalLink(int64_t node) {
        if (term_links_[node] != -1) {
            return term_links_[node];
        }
        if (node == 0 || trie_.Get(node).parent == 0) {
            term_links_[node] = 0;
            return 0;
        }
        int64_t v = GetSuffLink(node);
        while (v != 0 && !trie_.Get(v).is_terminal) {
            v = GetSuffLink(v);
        }

        term_links_[node] = v;
        return v;
    }

    int64_t GetSuffLink(int64_t node) {
        if (suff_links_[node] != -1) {
            return suff_links_[node];
        }
        if (node == 0 || trie_.Get(node).parent == 0) {
            suff_links_[node] = 0;
            return 0;
        }
        auto& v = trie_.Get(node);
        suff_links_[node] = CalcStep(GetSuffLink(v.parent), v.symbol);
        return suff_links_[node];
    }

    std::vector<int64_t> suff_links_;
    std::vector<int64_t> term_links_;
    std::unordered_map<int64_t, size_t> pattern_mapper_;

    int64_t state_{0};
    Trie trie_;
    std::vector<std::string> patterns_;
};

class Matcher {
    public:
    explicit Matcher (const std::vector<std::string>& patterns) : authomation_(patterns){

    }
    std::vector<std::pair<size_t, std::string>> FindMatches (const std::string& text) {
        authomation_.ResetState();
        std::vector<std::pair<size_t, std::string>> matches;
        for (size_t i = 0; i < text.size(); ++i) {
            auto step_matches = authomation_.MakeStep(text[i]);
            if (!step_matches.empty()) {
                for (auto match : step_matches) {
                    auto pos = static_cast<size_t> (i - static_cast<int64_t>(match.length()) + 1);
                    matches.emplace_back(pos, match);
                }
            }
        }
        return matches;
    }
    private:
    AhoCorasikAutomation authomation_;
};

int main() {
    Matcher matcher({"a", "aa", "fef", "ef"});
    std::string text = "abababababaaafefffefeffefeefefiheihfeuihfifiuhefheuhia";
    auto matches = matcher.FindMatches(text);
    for (auto& [pos, word] : matches) {
        std::cout << pos << " " << word << std::endl;
    }
    return 0;
}