#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>

static constexpr size_t kAlphabetSize = 256;

std::vector<int64_t> SuffixArray(const std::string& str);
void PrintSufArr (std::vector<int64_t> suffarr);

int main() {
  std::string str;
  std::getline(std::cin, str);
  PrintSufArr(SuffixArray(str));
  return 0;
}

std::vector<int64_t> SuffixArray(const std::string& str) {
    std::string helper = str + '\0';
    auto n = static_cast<int64_t>(helper.length());
  
    std::array<int64_t, kAlphabetSize> cnt = {};
    for (auto symbol : helper) {
        ++cnt[symbol];
    }
    for (int64_t i = 1; i < static_cast<int64_t>(cnt.size()); ++i) {
        cnt[i] += cnt[i - 1];
    }
  
    std::vector<int64_t> transposition(n);
    
    for (int64_t i = n - 1; i >= 0; --i) {
        transposition[--cnt[helper[i]]] = i;
    }
    std::vector<int64_t> classes(n);        
    int64_t current_class = 0;
    for (int64_t i = 0; i < n; ++i) {
        if (i > 0 && helper[transposition[i]] != helper[transposition[i - 1]]) {
            ++current_class;
        }
        classes[transposition[i]] = current_class;
    }
     
    size_t k = 1;
    while ((1 << k) <= n) {
        std::vector<int64_t> cnt(n, 0);  
        std::vector<int64_t> new_transposition(n, 0);

        for (int64_t i = 0; i < n; ++i) {
            ++cnt[classes[transposition[i]]];
        }
        for (int64_t i = 1; i < n; ++i) {
            cnt[i] += cnt[i - 1];
        }
  
        for (int64_t i = n - 1; i >= 0; --i) {
            int64_t j = transposition[i] - (1 << (k - 1));
            if (j < 0) {
                j += n;
            }
            new_transposition[--cnt[classes[j]]] = j;
        }
  
        int64_t now_class = 0;
  
        std::vector<int64_t> new_classes(n, 0);
        new_classes[new_transposition[0]] = 0;
        for (int64_t i = 1; i < n; ++i) {
            if (classes[new_transposition[i]] != classes[new_transposition[i - 1]] ||
                classes[(new_transposition[i] + (1 << (k - 1))) % n] 
                != classes[(new_transposition[i - 1] + (1 << (k - 1))) % n]) {
                ++now_class;
            }
            new_classes[new_transposition[i]] = now_class;
        }
  
        transposition = std::move(new_transposition);
        classes = std::move(new_classes);
        ++k;
    }
    return transposition;    
  
}

void PrintSufArr (std::vector<int64_t> suffarr) {
    for (size_t i = 1; i < suffarr.size(); ++i) {
        std::cout << suffarr[i]  + 1<< " ";
    }
    std::cout << std::endl;
}