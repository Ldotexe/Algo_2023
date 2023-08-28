#include <cmath>
#include <iostream>
#include <vector>

class Split {
public:
    explicit Split(int64_t n, int64_t k) : n_(n), k_(k) {};
    int64_t FindWeight ();

private:
    void CountW ();
    void FillFacts ();
    int64_t Mod(int64_t num);
    int64_t Reverse(int64_t num);
    int64_t Pow(int64_t num, int64_t deg);
    int64_t Stir(int64_t n);

    int64_t n_ = 0;
    int64_t k_ = 0;
    int64_t w_ = 0;
    std::vector<int64_t> facts_;
    int64_t mod_ = 1e9 + 7;
};
 
int64_t Split::Mod(int64_t num) {
    return (num % mod_ + mod_) % mod_;
}
 
int64_t Split::Reverse(int64_t num) {
    return Pow(num, mod_ - 2);
}
 
int64_t Split::Pow(int64_t num, int64_t deg) {
    if (deg == 0) {
        return 1;
    }
    if (deg == 1) {
        return num;
    }
    if (deg & 1) {
        return Mod(num * Pow(num, deg - 1));
    }
    int64_t ans = Pow (num, deg / 2);
    return Mod(ans * ans);
}
 
int64_t Split::Stir(int64_t n) {
    int64_t ans = 0;
    for (int64_t i = 1; i <= k_; ++i) {
        int64_t sign = 1 - 2 * ((k_ + i) & 1);
        ans += Mod(sign * Pow(i, n) * Mod(Reverse(facts_[i]) * Reverse(facts_[k_ - i])));
    }
 
    return Mod(ans);
}

void Split::CountW () {
    int64_t next = 0;
    for (int64_t i = 0; i < n_; ++i) {
        std::cin >> next;
        w_ = (w_ + next) % mod_;
    }
}

void Split::FillFacts () {
    facts_.resize (k_ + 1);
    facts_[0] = 1;
    for (int64_t i = 1; i < k_ + 1; ++i) {
        facts_[i] = (i * facts_[i - 1]) % mod_;
    }
}

int64_t Split::FindWeight () {
    CountW ();
    FillFacts ();
    return Mod(w_ * ((Stir(n_) + (n_ - 1) * Stir(n_ - 1)) % mod_));
}

int main() {
    int64_t n = 0;
    int64_t k = 0;
    std::cin >> n >> k;
    Split sp(n, k);
    std::cout << sp.FindWeight() << std::endl;
 
    return 0;
}