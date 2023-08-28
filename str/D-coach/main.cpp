#include <iostream>
#include <string>
#include <vector>

class FindStr {
private:
    size_t size_;
    size_t pattern_size_;
    std::string str_;
    std::vector<size_t> prefix_;

public:
    void GetPatternStr();
    void CheckInteresting();
    void PrintPrefStr(std::vector<size_t>& pref_str, size_t pos);
};

void PrintVector(std::vector<size_t> vec);

int main() {
    FindStr str;
    str.GetPatternStr();
    str.CheckInteresting();
    return 0;
}

void FindStr::GetPatternStr() {
    std::string str;
    std::string pattern;
    std::cin >> pattern >> str;
    str_ = pattern + '!' + str;
    size_ = str_.size();
    pattern_size_ = pattern.size();
    prefix_.resize(pattern_size_ + 1);
}

void FindStr::CheckInteresting() {
    std::vector<size_t> ans;
    std::vector<bool> reachable;
    ans.resize(size_ - pattern_size_);
    reachable.resize(size_ - pattern_size_);
    reachable[0] = true;
    for (size_t i = 1; i < size_; ++i) {
        size_t j = 0;
        for (j = prefix_[std::min(i - 1, pattern_size_)]; j > 0 && str_[i] != str_[j]; j = prefix_[j - 1]) {
        }
        if (str_[i] == str_[j]) {
            ++j;
        }
        prefix_[std::min(i, pattern_size_)] = j;
        if (i > pattern_size_) {
            if (j == 0) {
                std::cout << "Yes" << std::endl;
                return;
            }
            if (reachable[i - j - pattern_size_] == 1 && reachable[i - pattern_size_] == 0) {
                ans[i - pattern_size_] = i - j - pattern_size_;
                reachable[i - pattern_size_] = true;
            }
        }
    }

    if (reachable[size_ - pattern_size_ - 1] == 0) {
        std::cout << "Yes" << std::endl;
        return;
    }

    std::cout << "No" << std::endl;
    PrintPrefStr(ans, size_ - pattern_size_ - 1);
    std::cout << std::endl;
}

void FindStr::PrintPrefStr(std::vector<size_t>& pref_str, size_t pos) {
    if (pos != 0) {
        PrintPrefStr(pref_str, pref_str[pos]);
        for (size_t i = pref_str[pos]; i < pos; ++i) {
            std::cout << str_[i + pattern_size_ + 1];
        }
        std::cout << ' ';
    }
}