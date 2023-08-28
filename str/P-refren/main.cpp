/* Рассмотрим последовательность n целых чисел от 1 до m. 
Подпоследовательность подряд идущих чисел называется рефреном, если произведение
её длины на количество вхождений в последовательность максимально.
По заданной последовательности требуется найти её рефрен.*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>

struct Suffix { 
   int index_;
   std::pair<int, int> class_;
};

bool CmpFunc(Suffix a, Suffix b) {
    return a.class_ < b.class_;
}

std::vector<Suffix> ZeroIteration(std::string& str) {
   int n = static_cast<int>(str.size());
   std::vector<Suffix> suffix_array(n);

   for (int i = 0; i < n; ++i) {
      suffix_array[i].index_ = i;
      suffix_array[i].class_.first = str[i] - '0';     
      suffix_array[i].class_.second = ((i + 1) < n) ? (str[i + 1] - '0') : -1; 
   }
   sort(suffix_array.begin(), suffix_array.end(), CmpFunc); 
   return suffix_array;
}

std::vector<int> BuildSuffixArray(std::string& str, std::vector<Suffix>& suffix_array) { 
   int n = static_cast<int> (str.size()); 
   std::vector<int> index(n); 

   for (int step = 4; step < (n << 1); step <<= 1) {   

      int curr_class = 0;
      int prev_class = suffix_array[0].class_.first;

      suffix_array[0].class_.first = curr_class;
      index[suffix_array[0].index_] = 0;

      for (int i = 1; i < n; ++i) { 

         if (suffix_array[i].class_.first != prev_class || suffix_array[i].class_.second != suffix_array[i - 1].class_.second) {
            prev_class = suffix_array[i].class_.first;
            suffix_array[i].class_.first = ++curr_class;
         }
         else { 
            prev_class = suffix_array[i].class_.first;
            suffix_array[i].class_.first = curr_class;
         }

         index[suffix_array[i].index_] = i;
      }

      for (int i = 0; i < n; ++i) {   
         int next_index = suffix_array[i].index_ + (step >> 1);
         if (next_index < n) {
            suffix_array[i].class_.second = suffix_array[index[next_index]].class_.first;
         }
         else {
            suffix_array[i].class_.second = -1;
         }
      }
      sort(suffix_array.begin(), suffix_array.end(), CmpFunc); 
   }

   std::vector<int> suffix_vector;
   for (int i = 0; i < n; ++i) {
        suffix_vector.push_back(suffix_array[i].index_); 
    }
      
    return suffix_vector;
}

std::vector<int> KasaiAlgorithm(std::string& str, std::vector<int>& suffix_array) {
   int n = static_cast<int>(suffix_array.size());

   std::vector<int> longest_common_prefix(n, 0);  
   std::vector<int> suffix_inverse(n, 0);

   for (int i=0; i < n; ++i) {
        suffix_inverse[suffix_array[i]] = i;
   }

   int k = 0;
   for (int i = 0; i < n; ++i) { 

      if (suffix_inverse[i] == n - 1) { 
         k = 0;
         continue;
      }

      int j = suffix_array[suffix_inverse[i] + 1];   

      while (j + k < n && i + k < n && str[j + k] == str[i + k]) {
        ++k;
      }

      longest_common_prefix[suffix_inverse[i]] = k;

      if (k > 0) {
        --k;    
      }
   }
   return longest_common_prefix;
}

void Refren(std::string str, std::vector<int>& suffix_array, std::vector<int>& lcp) {
    int size = static_cast<int>(str.size());

    std::vector<std::vector<int>> v(size);

    for (int i = 0; i < size; ++i) {
        v[lcp[i]].push_back(i);
    }
        
    std::set<int64_t> begining_set;
    begining_set.insert(-1);
    begining_set.insert(size);

    int64_t answer = size;
    int64_t len = size;
    int64_t current_suffix = 0;

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < static_cast<int>(v[i].size()); ++j) {

            int64_t start = *begining_set.lower_bound(v[i][j]);
            int64_t end = *(--begining_set.lower_bound(v[i][j]));
            int64_t inserts = (start - 1) - (end + 1) + 1;

            if (answer < (inserts + 1) * i) {
                answer = (inserts + 1) * i;
                len = i;
                current_suffix = suffix_array[v[i][j]];
            }
        }
        for (auto u : v[i]) {
            begining_set.insert(u);
        }
    }

    std::cout << answer << '\n' << len << '\n';
    for (int64_t i = current_suffix; i < current_suffix + len; ++i)
        std::cout << str[(size_t)i] - '0' << " ";
    std::cout << '\n';
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::string str;
    for(int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        str += static_cast<char>(x + '0');
    }

    std::vector<Suffix> suffix_array = ZeroIteration(str);
    std::vector<int>suffix_indices = BuildSuffixArray(str, suffix_array);
    std::vector<int> longest_common_prefix = KasaiAlgorithm(str, suffix_indices);
    
    Refren(str, suffix_indices, longest_common_prefix);

    return 0;
}