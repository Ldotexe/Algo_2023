#include <iostream>
#include <cinttypes>

int64_t PowMod (int64_t num, int64_t deg, int64_t mod);
int64_t ReverseMod (int64_t num, int64_t mod);
int64_t AddAndDivMod (int64_t a, int64_t b, int64_t c, int64_t d);

int main () {
    int64_t a = 0;
    int64_t b = 0;
    int64_t c = 0;
    int64_t d = 0;
    std::cin >> a >> b >> c >> d;
    std::cout << AddAndDivMod(a, b, c, d) << std::endl;
    return 0;
}

int64_t PowMod (int64_t num, int64_t deg, int64_t mod) {
    if (deg == 1) {
        return num;
    }
    if (deg % 2 == 0) {
        int64_t res = PowMod (num, deg / 2, mod);
        return (res * res) % mod;
    }
    return (PowMod(num, deg - 1, mod) * num) % mod;
}

int64_t ReverseMod (int64_t num, int64_t mod) {
    return PowMod (num, mod - 2, mod);
}

int64_t AddAndDivMod (int64_t a, int64_t b, int64_t c, int64_t d) {
    int64_t mod = 1000000007;
    int64_t sum = ((a * d + b * c) % mod + mod) % mod;
    int64_t bd = ((b * d) % mod + mod) % mod;
    int64_t rev = (ReverseMod (bd, mod) % mod + mod) % mod;
    return (((sum * rev % mod) + mod) % mod);
}