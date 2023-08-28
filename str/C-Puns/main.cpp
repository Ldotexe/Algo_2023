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
    explicit FindStr(std::string& pattern, std::string& str) {
        str_ = pattern + '!' + str;
        size_ = str_.size();
        pattern_size_ = pattern.size();
        prefix_.resize(pattern_size_ + 1);
    }
    size_t FindLastPrefixLen();
};

class Pun {
private:
    size_t size_;
    std::string pun_;

public:
    void MakePun(size_t n);
    void UpdatePun(std::string& next_str);
    void PrintPun();
};

int main() {
    size_t n = 0;
    Pun pun;
    std::cin >> n;
    pun.MakePun(n);
    pun.PrintPun();
    return 0;
}

void Pun::MakePun(size_t n) {
    std::string next_str;
    std::cin >> next_str;
    pun_ = next_str;
    size_ = next_str.size();
    for (size_t i = 1; i < n; ++i) {
        std::cin >> next_str;
        UpdatePun(next_str);
    }
}

void Pun::UpdatePun(std::string& next_str) {
    std::string prev_str;
    size_t next_len = next_str.size();
    if (size_ > next_len) {
        for (size_t i = 0; i < next_len; ++i) {
            prev_str += pun_[size_ - next_len + i];
        }
    } else {
        prev_str = pun_;
    }
    FindStr fstr(next_str, prev_str);
    size_t old_prefix = fstr.FindLastPrefixLen();
    for (size_t i = old_prefix; i < next_len; ++i) {
        pun_ += next_str[i];
    }
    size_ += next_len - old_prefix;
}

size_t FindStr::FindLastPrefixLen() {
    for (size_t i = 1; i < size_; ++i) {
        size_t j = 0;
        for (j = prefix_[std::min(i - 1, pattern_size_)]; j > 0 && str_[i] != str_[j]; j = prefix_[j - 1]) {
        }
        if (str_[i] == str_[j]) {
            ++j;
        }
        prefix_[std::min(i, pattern_size_)] = j;
    }
    return prefix_[pattern_size_];
}

void Pun::PrintPun() {
    std::cout << pun_ << std::endl;
}