#include <iostream>
#include <string>
#include <vector>

class AlgoStr {
private:
    size_t size_;
    std::string str_;
    std::vector<int> z_;
    std::vector<int> prefix_;

public:
    explicit AlgoStr(size_t size) {
        size_ = size;
        str_.resize(size);
        z_.resize(size);
        prefix_.resize(size);
    }

    void GetZ();
    void RecoverPrefixFromZ();
    void RecoverStrFromPrefix();
    void PrintStr();
};

int main() {
    size_t n = 0;
    std::cin >> n;
    AlgoStr str(n);
    str.GetZ();
    str.RecoverPrefixFromZ();
    str.RecoverStrFromPrefix();
    str.PrintStr();
}

void AlgoStr::GetZ() {
    for (size_t i = 0; i < size_; ++i) {
        std::cin >> z_[i];
    }
}

void AlgoStr::RecoverPrefixFromZ() {
    for (size_t i = 1; i < size_; ++i) {
        for (int j = z_[i] - 1; j >= 0; --j) {
            if (prefix_[i + j] > 0) {
                break;
            }
            prefix_[i + j] = j + 1;
        }
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
        int cur = prefix_[i - 1];
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