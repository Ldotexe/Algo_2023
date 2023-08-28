#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

class FindStr {
private:
    uint32_t size_;
    uint32_t str_size_;
    uint32_t colors_;
    std::vector<uint32_t> str_;
    std::vector<uint32_t> z_fun_;

public:
    void GetStr();
    void PrintMirror();
};

void PrintVector(std::vector<uint32_t> vec);
uint32_t MyMax(uint32_t first, uint32_t second);

int main() {
    FindStr str;
    str.GetStr();
    str.PrintMirror();
    return 0;
}

void FindStr::GetStr() {
    std::cin >> size_ >> colors_;
    str_size_ = 2 * size_ + 1;
    str_.resize(str_size_);
    for (uint32_t i = 0; i < size_; ++i) {
        std::cin >> str_[i];
        str_[2 * size_ - i] = str_[i];
    }
    str_[size_] = colors_ + 1;
    z_fun_.resize(str_size_);
}

void FindStr::PrintMirror() {
    uint32_t left = 0;
    uint32_t right = 0;
    for (uint32_t i = 1; i < str_size_; ++i) {
        for (z_fun_[i] = MyMax(0, std::min(right - i, z_fun_[i - left]));
             i + z_fun_[i] < str_size_ && str_[z_fun_[i]] == str_[i + z_fun_[i]]; ++z_fun_[i]) {
        }
        if (i + z_fun_[i] > right) {
            left = i;
            right = i + z_fun_[i];
        }
        if ((str_size_ - i) == z_fun_[i] && (str_size_ - i) % 2 == 0) {
            std::cout << size_ - (str_size_ - i) / 2 << " ";
        }
    }
    std::cout << size_ << std::endl;
}

uint32_t MyMax(uint32_t first, uint32_t second) {
    if (first > second) {
        return first;
    }
    return second;
}