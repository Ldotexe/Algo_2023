#include <iostream>
#include <cinttypes>
#include <vector>

int64_t FindSumNPrime (int64_t n);

int main () {
    int64_t n = 0;
    std::cin >> n;
    std::cout << FindSumNPrime(n) << std::endl;
    return 0;
}

int64_t FindSumNPrime (int64_t n) {
    std::vector<int64_t> prime;
    std::vector<int64_t> lp;
    lp.resize(n + 1);

    for (int64_t i = 2; i <= n; ++i) {
	    if (lp[i] == 0) {
		    lp[i] = i;
		    prime.push_back (i);
	    }
	    for (int64_t j = 0; j < static_cast<int64_t>(prime.size()) && prime[j] <= lp[i] && i * prime[j] <= n; ++j) {
		    lp[i * prime[j]] = prime[j];
        }
    }

    int64_t answer = 0;
    for (int64_t i = 2; i <= n; ++i) {
        if (lp[i] != i) {
            answer += lp[i];
        }
    }

    return answer;
}