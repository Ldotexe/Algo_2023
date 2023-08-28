#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>


const int64_t kMod = 7'340'033;
const int64_t kRoot = 5;
const int64_t kRoot1 = 4'404'020;
const int64_t kRoot2 = 1 << 20;

int64_t Pow(int64_t a, int64_t n) {
    int64_t res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res * a) % kMod;
        }
        a = (a * a) % kMod;
        n >>= 1;
    }
    return res;
}

std::vector<int64_t> CalculateRev(size_t n, int64_t log_n) {
    std::vector<int64_t> rev(n);
    for (size_t i = 0; i < n; ++i) {
        rev[i] = 0;
        for (int64_t j = 0; j < log_n; ++j) {
            if (i & (1 << j)) {
                rev[i] |= 1 << (log_n - 1 - j);
            }
        }
    }
    return rev;
}

void FFT(std::vector<int64_t>& a, std::vector<int64_t>& rev, bool flag) {
    auto n = static_cast<int64_t>(a.size());

    for (int64_t i = 0; i < n; ++i) {
        if (i < rev[i]) {
            std::swap(a[i], a[rev[i]]);
        }
    }

    for (int64_t len = 2; len <= n; len <<= 1) {
        int64_t wlen = flag ? kRoot1 : kRoot;

        for (int64_t i = len; i < kRoot2; i <<= 1) {
            wlen = static_cast<int64_t>(wlen * 1ll * wlen % kMod);
        }

        for (int64_t i = 0; i < n; i += len) {
            int64_t w = 1;
            for (int64_t j = 0; j < len / 2; ++j) {
                int64_t u = a[i + j];
                auto v = static_cast<int64_t>(a[i + j + len / 2] * 1ll * w % kMod);
                a[i + j] = u + v < kMod ? u + v : u + v - kMod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + kMod;
                w = static_cast<int64_t>(w * 1ll * wlen % kMod);
            }
        }
    }

    if (flag) {
        int64_t rev = Pow(n, kMod - 2);

        for (int64_t i = 0; i < n; ++i) {
            a[i] = static_cast<int64_t>(a[i] * 1ll * rev % kMod);
        }
    }
}

std::vector<int64_t> Multiply(const std::vector<int64_t>& a, const std::vector<int64_t>& b) {
    std::vector<int64_t> fa = a;

    std::vector<int64_t> fb = b;

    size_t n = 1;
    while (n <= std::max(fa.size(), fb.size())) {
        n <<= 1;
    }

    int64_t log_n = 0;
    while ((1LLU << log_n) < n) {
        ++log_n;
    }

    std::vector<int64_t> rev = CalculateRev(n, log_n);

    fa.resize(n, 0);
    fb.resize(n, 0);

    FFT(fa, rev, false);
    FFT(fb, rev, false);

    for (size_t i = 0; i < n; ++i) {
        fa[i] = (fa[i] * fb[i]) % kMod;
    }

    FFT(fa, rev, true);
 
    return fa;
}

std::vector<int64_t> operator-(const std::vector<int64_t>& a) {
    std::vector<int64_t> res = a;
    auto n = static_cast<int64_t>(a.size());
    for (int64_t i = 0; i < n; ++i) {
        res[i] = (res[i] * (-1) + kMod) % kMod;
    }
    return res;
}

std::vector<int64_t> operator+(const std::vector<int64_t>& a, const std::vector<int64_t>& b) {
    size_t n = std::max(a.size(), b.size());
    std::vector<int64_t> res(n, 0);
    for (size_t i = 0; i < n; ++i) {
        if (i < a.size()) {
            res[i] += a[i];
        }
        if (i < b.size()) {
            res[i] += b[i];
        }
        res[i] %= kMod;
    }
    return res;
}

std::vector<int64_t> Reverse(std::vector<int64_t>& p, int64_t n) {
    if (n == 1) {
        return {Pow(p[0], kMod - 2)};
    }

    std::vector<int64_t> p1(n / 2);
    std::vector<int64_t> p2(n / 2);

    int64_t n2 = n / 2;
    for (int64_t i = 0; i < n2; ++i) {
        p1[i] = p[i];
        p2[i] = p[i + n2];
    }

    std::vector<int64_t> q1 = Reverse(p1, n2);
    std::vector<int64_t> x = Multiply(p1, q1);
    for (int64_t i = n2; i < n; ++i) {
        x[i - n2] = x[i];
    }
    x.resize(n2);

    std::vector<int64_t> q2 = Multiply(p2, q1);
    q2 = q2 + x;
    q2 = Multiply(q2, -q1);

    q2.resize(n2);
    q1.resize(n);
    for (int64_t i = n2; i < n; ++i) {
        q1[i] = q2[i - n2];
    }
    return q1;
}

int main() {
    int64_t m = 0;
    int64_t n = 0;
    std::cin >> m >> n;
    std::vector<int64_t> p(n + 1);
    for (int64_t i = 0; i <= n; ++i) {
        std::cin >> p[i];
    }

    if (p[0] == 0) {
        std::cout << "The ears of a dead donkey";
        return 0;
    }

    int64_t k = 1;
    while (k < m) {
        k <<= 1;
    }
    p.resize(k);
    auto ans = Reverse(p, k);
    for (int64_t i = 0; i < m; ++i) {
        std::cout << ans[i] << ' ';
    }
}