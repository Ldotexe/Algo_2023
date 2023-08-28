#include <iostream>
#include <string>
#include <vector>

class AlgoStr {
private:
    size_t size_;
    std::string str_;
    std::vector<size_t> prefix_;

public:
    explicit AlgoStr(size_t size) {
        size_ = size;
        str_.resize(size);
        prefix_.resize(size);
    }

    void GetPrefix();
    void RecoverStrFromPrefix();
    void PrintStr();
};

int main() {
    size_t n = 0;
    std::cin >> n;
    AlgoStr str(n);
    str.GetPrefix();
    str.RecoverStrFromPrefix();
    str.PrintStr();
}

void AlgoStr::GetPrefix() {
    for (size_t i = 0; i < size_; ++i) {
        std::cin >> prefix_[i];
    }
}

void AlgoStr::RecoverStrFromPrefix() {
    std::vector<bool> check;
    check.resize('z' - 'a' + 1);
    char let = 'a';
    str_[0] = 'a';
    for (size_t i = 1; i < size_; ++i) {
        for (size_t j = 0; j < 'z' - 'a' + 1; ++j) {
            check[j] = false;
        }
        size_t cur = prefix_[i - 1];
        while (cur + 1 != prefix_[i] && cur != 0) {
            check[str_[cur] - 'a'] = true;
            cur = prefix_[cur - 1];
        }
        if (cur + 1 == prefix_[i]) {
            str_[i] = str_[cur];
        } else {
            check[str_[prefix_[i]] - 'a'] = true;
            for (let = 0; check[let]; ++let) {
            }
            str_[i] = static_cast<char>('a' + let);
        }
    }
}

void AlgoStr::PrintStr() {
    std::cout << str_ << std::endl;
}