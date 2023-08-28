#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

class FindStr {
private:
    int pattern_size_;
    int str_size_;
    std::string str_;
    std::vector<int> z_fun_;
    std::vector<int> rev_z_fun_;
    bool pattern_is_simple_;

    void BuildZFun ();
    void BuildRevZFun ();

public:
    void GetStr ();
    void PrintCicle ();
};

void PrintVector(std::vector<uint32_t> vec);
uint32_t MyMax(uint32_t first, uint32_t second);

int main() {
    FindStr str;
    str.GetStr();
    str.PrintCicle();
    return 0;
}

void FindStr::GetStr() {
    std::string str;
    std::string pattern;
    pattern_is_simple_ = false;
    std::cin >> pattern >> str;
    pattern_size_ = static_cast<int>(pattern.size());
    int cnum = 0;
    char str_c = 0;
    for (int i = 0; i < pattern_size_; ++i) {
        if (str_c != pattern[i]) {
            str_c = pattern[i];
            cnum = 0;
        }
        ++cnum;
    }
    if (cnum == pattern_size_) {
        pattern_is_simple_ = true;
    }
    str_size_ = static_cast<int>(str.size() + 2 * (pattern_size_ + 1));
    str_ = pattern + '!' + str + '#' + pattern;
    z_fun_.resize(str_size_);
    rev_z_fun_.resize(str_size_);
}

void FindStr::BuildZFun() {
    int left = 0;
    int right = 0;
    for (int i = 1; i < str_size_; ++i) {
        for (z_fun_[i] = std::max(0, std::min(right - i, z_fun_[i - left]));
             i + z_fun_[i] < str_size_ && str_[z_fun_[i]] == str_[i + z_fun_[i]]; ++z_fun_[i]) {
        }
        if (i + z_fun_[i] > right) {
            left = i;
            right = i + z_fun_[i];
        }
    }
}

void FindStr::BuildRevZFun() {
    int left = static_cast<int>(str_size_ - 1);
    int right = static_cast<int>(str_size_ - 1);
    for (auto i = static_cast<int>(str_size_ - 2); i >= static_cast<int32_t>(pattern_size_ + 1); --i) {
        for (rev_z_fun_[i] = std::max(0, std::min(i - left, rev_z_fun_[str_size_ - 1 - (right - i)]));
             i - rev_z_fun_[i] >= 0 && str_[str_size_ - 1 - rev_z_fun_[i]] == str_[i - rev_z_fun_[i]]; ++rev_z_fun_[i]) {
                
        }
        if (i - rev_z_fun_[i] < left) {
            right = i;
            left = i - rev_z_fun_[i];
        }
    }
}

void FindStr::PrintCicle() {
    BuildZFun();
    BuildRevZFun();
    uint64_t ans = 0;
    if (pattern_is_simple_) {
        for (int i = pattern_size_; i < str_size_ - pattern_size_ - 1; ++i) {
            if (z_fun_[i + 1] >= pattern_size_) {
                ++ans;
            }
        }
    }
    else{
        for (int i = pattern_size_; i < str_size_ - pattern_size_ - 1; ++i) {
            if (z_fun_[i + 1] + rev_z_fun_[i] >= pattern_size_) {
                ans += z_fun_[i + 1] + rev_z_fun_[i] - pattern_size_ + 1;
            }
            if (z_fun_[i + 1] == pattern_size_) {
                --ans;
            }
        }
    }
    std::cout << ans << std::endl;
}