#include <iostream>
#include <vector>

class IntMod {
public:
    explicit IntMod() = default;
    explicit IntMod(int64_t num) : num(num) {};
    void Mod () {num = (num % mod_ + mod_) % mod_;};
    IntMod operator+ (IntMod other) {return IntMod(((num + other.num) % mod_ + mod_) % mod_);};
    void operator+= (IntMod other) {num = ((num + other.num) % mod_ + mod_) % mod_;};
    IntMod operator* (IntMod other) {return IntMod(((num * other.num) % mod_ + mod_) % mod_);};
    int64_t num;
private:
    int64_t mod_ = 1e9 + 9;
};

class FibMatrix {
public:
    FibMatrix operator*(FibMatrix other) {
    return { (a * other.a) + (b * other.c),
             (a * other.b) + (b * other.d),
             (c * other.a) + (d * other.c),
             (c * other.b) + (d * other.d)};};    
    
    FibMatrix Pow(int64_t deg) {
        if (deg == 1) {
            return *this;
        }
        if (deg & 1) {
            return *this * this->Pow(deg - 1);
        }
        FibMatrix res = this->Pow(deg / 2);
        return res * res;
    }

    IntMod a{1};
    IntMod b{1};
    IntMod c{1};
    IntMod d{0};
};


IntMod Fibonacci(int64_t n) {
    if (n < -1) {
        return IntMod(0);
    }
    if (n == -1 || n == 0) {
        return IntMod(1);
    }
    FibMatrix m;
    m = m.Pow(n);
    return m.a + m.b;
}

class Trip {
public:
    explicit Trip(size_t n) : n_(n) {};
    void FillAirports ();
    void AnswerRequests(size_t q);
private:
    IntMod CountVariants(int64_t c);
    
    size_t n_;
    struct Airport {
        explicit Airport() = default;

        int64_t x;
        int64_t y;
        IntMod k;
    };
    std::vector<Airport> airports_;
};

IntMod Trip::CountVariants(int64_t c) {
    IntMod ans(0);
    for (size_t i = 0; i < n_; ++i) {
        int64_t y_dif = airports_[i].y - (airports_[i].x + c);
        ans += Fibonacci(y_dif - 1) * airports_[i].k;
    }
    return ans;
}


int main() {
    size_t n = 0;
    size_t q = 0;
    std::cin >> n >> q;
    Trip tp(n);
    tp.FillAirports();
    tp.AnswerRequests(q);
    return 0;
}

void Trip::FillAirports () {
    airports_.resize(n_);
    for (size_t i = 0; i < n_; ++i) {
        std::cin >> airports_[i].x >> airports_[i].y >> airports_[i].k.num;
        airports_[i].k.Mod();
    }
}

void Trip::AnswerRequests (size_t q) {
    for (size_t i = 0; i < q; ++i) {
        int64_t c = 0;
        std::cin >> c;
        std::cout << CountVariants(c).num << std::endl;
    }
}