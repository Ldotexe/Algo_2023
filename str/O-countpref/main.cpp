/* Дана строка. Для каждого ее префикса найдите количество ее различных подстрок.*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


struct Node {

    Node() : parent_(-1), suffix_link_(-1), length_(0), count_(1), symbol_to_this_('?') {}

    explicit Node(const char& symbol, const int& parent) : parent_(parent), suffix_link_(-1), length_(0), count_(0), symbol_to_this_(symbol) {}

    int parent_;
    int suffix_link_;
    int length_;
    uint64_t count_;
    char symbol_to_this_;
    std::unordered_map<char, int> transitions_;
};

struct SuffixAutomation {

    SuffixAutomation() : last_index_(0) {
        vertexes_.resize(1);
    }

    int Clone(const char& curr_symbol, const int& check_symbol, int parent) {
        int clone = static_cast<int>(vertexes_.size());

        Node node(curr_symbol, parent);
        vertexes_.emplace_back(node);

        vertexes_[clone].length_ = vertexes_[parent].length_ + 1;
        vertexes_[clone].suffix_link_ = vertexes_[check_symbol].suffix_link_;
        vertexes_[check_symbol].suffix_link_ = clone;

        vertexes_[clone].transitions_ = vertexes_[check_symbol].transitions_;

        while(parent >= 0 && vertexes_[parent].transitions_.find(curr_symbol) != vertexes_[parent].transitions_.end() && vertexes_[parent].transitions_[curr_symbol] == check_symbol) {
            vertexes_[check_symbol].count_ -= vertexes_[parent].count_;

            vertexes_[clone].count_ += vertexes_[parent].count_;

            vertexes_[parent].transitions_[curr_symbol] = clone;

            parent = vertexes_[parent].suffix_link_;
        }

        return clone;
    }

    void AddVertex(const char& symbol) {
        int new_node = static_cast<int>(vertexes_.size());
        
        Node node(symbol, last_index_);

        vertexes_.emplace_back(node);

        vertexes_[new_node].length_ = vertexes_[last_index_].length_ + 1;
        vertexes_[new_node].count_ += vertexes_[last_index_].count_;

        vertexes_[last_index_].transitions_[symbol] = new_node;

        last_index_ = vertexes_[last_index_].suffix_link_;

        while(last_index_ >= 0 && vertexes_[last_index_].transitions_.find(symbol) == vertexes_[last_index_].transitions_.end()) {
            vertexes_[last_index_].transitions_[symbol] = new_node;
            vertexes_[new_node].count_ += vertexes_[last_index_].count_;
            last_index_ = vertexes_[last_index_].suffix_link_;
        }

        if(last_index_ >= 0) {
            int check_symbol = vertexes_[last_index_].transitions_[symbol];
            if (vertexes_[check_symbol].length_ == vertexes_[last_index_].length_ + 1) {
                vertexes_[new_node].suffix_link_ =  check_symbol;
            }
            else {
                vertexes_[new_node].suffix_link_ = Clone(symbol, check_symbol, last_index_);
            }
        }
        else {
            vertexes_[new_node].suffix_link_ = 0;
        }
        
        last_index_ = new_node;
    }

    std::vector<uint64_t> Build(const std::string& str) {
        int str_size = static_cast<int>(str.size());
        vertexes_.reserve(str_size + 1);

        std::vector<uint64_t> substrings_cnt;

        uint64_t tmp = 0;
        for(int i = 0; i < str_size; ++i) {
            this->AddVertex(str[i]);

            tmp += vertexes_[last_index_].count_;

            substrings_cnt.emplace_back(tmp);
        }

        return substrings_cnt;
    }

    std::vector<Node> vertexes_;
    int last_index_;
};

void ShowArray(std::vector<uint64_t>& vec, size_t n) {
    for(size_t i = 0; i < n; ++i) {
        printf("%ld\n", vec[i]);
    } 
}

int main() {
    std::string str;
    std::cin >> str;
    
    SuffixAutomation suff_auto;

    std::vector<uint64_t> substrings_cnt = suff_auto.Build(str);

    ShowArray(substrings_cnt, substrings_cnt.size());

    return 0;
}