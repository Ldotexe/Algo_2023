#include <iostream>
#include <cinttypes>
#include <vector>
#include <algorithm>
#include <cmath>

// source: https://codeforces.com/blog/entry/91632

class Primes {
public:
    explicit Primes(int64_t n) : n_(n) {};
    int64_t CountPrimes();
private:
    void CompleteIndex ();
    int64_t GetIndex (int64_t i);
    void RunDp ();
    void FillDpVec ();

    int64_t n_;
    std::vector<int64_t> ind_vec_;
    std::vector<int64_t> sieving_dp_;
};

int main () {
    int64_t n = 0;
    std::cin >> n;
    Primes pr(n);
    std::cout << pr.CountPrimes() << std::endl; 
    return 0;
}

int64_t Primes::CountPrimes() {
    CompleteIndex();
    FillDpVec();
    RunDp();
    return sieving_dp_[GetIndex(n_)] - 1;
}

void Primes::CompleteIndex () {
    for (int64_t i = 1; i * i <= n_; ++i) {
        ind_vec_.push_back(n_ / i);
        ind_vec_.push_back(i);
    }
    sort(ind_vec_.begin(), ind_vec_.end());
    ind_vec_.erase(unique(ind_vec_.begin(), ind_vec_.end()), ind_vec_.end());
}

int64_t Primes::GetIndex (int64_t i) {
    if (i <= static_cast<int64_t>(sqrt(static_cast<double>(n_)))){
        return i - 1;
    }
    return static_cast<int64_t>(ind_vec_.size() - (n_ / i));
}

void Primes::FillDpVec () {
    sieving_dp_.resize(ind_vec_.size());
    for (uint64_t i = 0; i < ind_vec_.size(); ++i){
        sieving_dp_[i] = ind_vec_[i];
    }
}

void Primes::RunDp () {
    int64_t cnt = 0;
    for (int64_t i = 2; i * i <= n_; ++i) {
        if (sieving_dp_[GetIndex(i)] != sieving_dp_[GetIndex(i - 1)]) {
            ++cnt;
            for (auto j = static_cast<int64_t>(ind_vec_.size() - 1); j >= 0 && !(ind_vec_[j] < i * i); --j) {
                sieving_dp_[j] -= sieving_dp_[GetIndex(ind_vec_[j] / i)] - cnt;
            }
        }
    }
}