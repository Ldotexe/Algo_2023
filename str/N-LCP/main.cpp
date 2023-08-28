//Today we learned: https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9A%D0%B0%D1%81%D0%B0%D0%B8_%D0%B8_%D0%B4%D1%80.
#include <iostream>
#include <vector>
#include <string>

std::vector<size_t> BuildLCP(std::string str, std::vector<size_t> suf);
void PrintVec(std::vector<size_t>& vec);

int main() {
    size_t n = 0;
    std::string str;
    std::cin >> n >> str;

    std::vector<size_t> suf(n);
    for(size_t i = 0; i < n; ++i) {
        std::cin >> suf[i];
        --suf[i];
    }

    std::vector<size_t> lcp = BuildLCP(str, suf);
    PrintVec(lcp);

    return 0;
}

std::vector<size_t> BuildLCP(std::string str, std::vector<size_t> suf) {
  size_t n = suf.size();

  std::vector<size_t> lcp(n);  
  std::vector<size_t> pos(n);

  for (size_t i = 0; i < n; ++i) {
    pos[suf[i]] = i;
  }

  int k = 0;
  for (size_t i = 0; i < n; ++i) { 
    if (k > 0) {
      --k;    
    }

    if (pos[i] == n - 1) { 
      k = 0;
      continue;
    }

    size_t j = suf[pos[i] + 1];   
    while (j + k < n && i + k < n && str[j + k] == str[i + k]) {
      ++k;
    }

    lcp[pos[i]] = k;
   }
   return lcp;
}

void PrintVec(std::vector<size_t>& vec) {
    for(size_t i = 0; i < vec.size() - 1; ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
}