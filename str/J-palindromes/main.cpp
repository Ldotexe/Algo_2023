#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Palindrome {
private:
    std::vector<std::string> words_;
    std::unordered_map<std::string, size_t> rev_parts_;
public:
    void GetWords ();
    std::vector<std::pair<size_t, size_t>> PairPalindromes ();
};

void PrintPairPalindromes (std::vector<std::pair<size_t, size_t>> pairs);

int main () {
    Palindrome p;
    p.GetWords ();
    PrintPairPalindromes (p.PairPalindromes());
    return 0;
}

void Palindrome::GetWords () {
    size_t n = 0;
    std::cin >> n;
    words_.resize (n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> words_[i];
        rev_parts_[std::string(words_[i].rbegin(), words_[i].rend())] = i;
    }
}

std::vector<std::pair<size_t, size_t>> Palindrome::PairPalindromes () {
    std::vector<std::pair<size_t, size_t>> answer;
    for (size_t i = 0; i < words_.size(); ++i) {
        std::string word = words_[i];
        for (size_t j = 1; j <= word.size(); ++j) {
            std::string left = word.substr(0, j);
            std::string right = word.substr(j);
            if (left == std::string(left.rbegin(), left.rend()) && rev_parts_.count(right)) {
                answer.emplace_back(rev_parts_[right], i);
            }
            if (right == std::string(right.rbegin(), right.rend()) && rev_parts_.count(left) && rev_parts_[left] != i) {
                answer.emplace_back(i, rev_parts_[left]);
            }
        }
    }
    return answer;
}


void PrintPairPalindromes (std::vector<std::pair<size_t, size_t>> pairs) {
    std::cout << pairs.size() << '\n';
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << pairs[i].first + 1 << ' ' << pairs[i].second + 1 << '\n';
    }
}