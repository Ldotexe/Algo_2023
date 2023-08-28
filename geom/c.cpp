#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

const double kPi = atan(1.0)*4;
const double kEps = 1e-8;


class Light {
public:
    explicit Light(int n, double l, double r) : n_(n), l_(l), r_(r) {};
    double Change (double x, double y, double z);
    double FindDistance ();
private:
    void FillLight ();

    int n_;
    int vars_;
    double l_;
    double r_;
    std::vector<double> x_;
    std::vector<double> y_;
    std::vector<double> alpha_;
    std::vector<double> dp_;
};

void Light::FillLight() {
    x_.resize(n_);
    y_.resize(n_);
    alpha_.resize(n_);
    dp_.resize(1 << 20);
    for (int i = 0; i < n_; ++i) {
        std::cin >> x_[i] >> y_[i] >> alpha_[i];
        alpha_[i] *= kPi/180;
    }
    vars_ = 1 << n_;
    for (int j = 0; j < vars_; ++j) { 
        dp_[j] = l_;
    }
}

double Light::FindDistance() {
    FillLight();
    for (int j = 0; j < vars_; ++j) {
        for (int i = 0; i < n_; ++i) {
            if (!(j >> i & 1)) {
                dp_[j | 1 << i] = fmax(dp_[j | 1 << i], dp_[j] + Change(x_[i] - dp_[j], y_[i], alpha_[i]));
                if (dp_[j|1<<i] >= r_) { 
                    return r_- l_; 
                }
            }
        }
    }

    return dp_[vars_ - 1] - l_;
}

double Light::Change(double x, double y, double z) {
    double c = atan2(y, x);
    double a = kPi - z - c;
    if (a < kEps) {
        return r_;
    }
    return sqrt(x * x + y * y) / sin(a) * sin(z);
}
int main() {
    int n = 0;
    double l = 0;
    double r = 0;
    std::cin >> n >> l >> r;
    Light lt(n, l, r);
    printf("%.9f\n", lt.FindDistance());
    return 0;
}