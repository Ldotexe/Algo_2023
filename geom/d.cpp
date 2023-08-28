#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cinttypes>

static const int kCntclws = 1;
static const int kClws = -1;
static const int kBck = 2;
static const int kFrt = -2;
static const int kSeg = 0;

class Triangulation {
public:
    class Vector {
    public:
        double x, y;
        double eps_ = 1e-10;
 
        explicit Vector(double x = 0, double y = 0): x(x), y(y) {}
 
        Vector operator+ (Vector p) { return Vector(x + p.x, y + p.y); }
        Vector operator- (Vector p) { return Vector(x - p.x, y - p.y); }
        Vector operator* (double a) { return Vector(a * x, a * y); }
        Vector operator/ (double a) { return Vector(x / a, y / a); }

        double Norm() {
            return x * x + y * y;
        }

        bool operator< (const Vector &p) const {
            return x != p.x ? x < p.x : y < p.y;
        }

        int Dcmp(double x);
 
        bool operator == (const Vector &p) {
            return Dcmp(x - p.x) == 0 && Dcmp(y - p.y) == 0;
        }
    };

    explicit Triangulation (int n) : n_(n) {};
    void FillTriangulation ();
    int64_t FindTriangulationNum ();
private:
    std::vector<Vector> p_;
    std::vector<std::vector<int64_t>> dp_;
    void Clc(int l, int r);
    int Cow(Vector p0, Vector p1, Vector p2);

    int n_;
    double eps_ = 1e-10;
    int64_t mod_ = 1e9 + 7;
};

double Crs(Triangulation::Vector a, Triangulation::Vector b) {
    return a.x * b.y - a.y * b.x;
}

double Dot(Triangulation::Vector a, Triangulation::Vector b) {
    return a.x * b.x + a.y * b.y;
}

void Triangulation::FillTriangulation() {
    p_.resize(n_);
    dp_.resize(n_);
    for (int i = 0; i < n_; ++i) { 
        dp_[i].resize(n_);
        for (int j = 0; j < n_; ++j) {
            dp_[i][j] = -1;
        }
    }
    for (int i = 0; i < n_; ++i) {
        std::cin >> p_[i].x >> p_[i].y;
    }
}

int64_t Triangulation::FindTriangulationNum () {
    int64_t s = 0;
    for (int i = 0; i < n_; ++i) {
        s += static_cast<int64_t>(Crs(p_[i], p_[(i + 1) % n_]));
    }
    if (s < 0) {
        std::reverse(p_.begin(),p_.end());
    }
    Clc(0, n_ - 1);
    return dp_[0][n_- 1];
}

int Triangulation::Vector::Dcmp(double x) {
    if(x > eps_) { 
        return 1;
    }
    if(x < -eps_) { 
        return -1;
    }
    return 0;
}

int Triangulation::Cow(Vector p0, Vector p1, Vector p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (Crs(a, b) > eps_) {
        return kCntclws;
    }
    if (Crs(a, b) < -eps_) {
        return kClws;
    }
    if (Dot(a, b) < -eps_) {
        return kBck;
    }
    if (a.Norm() < b.Norm()) {
        return kFrt;
    }

    return kSeg;
}


void Triangulation::Clc(int l, int r) {
    if(dp_[l][r] >= 0) {
        return;
    }
    if(l == r-1){
        dp_[l][r] = 1;
        return;
    }
    dp_[l][r] = 0;
    for(int i = l+1; i<r; ++i){
        if (Crs((p_[l] - p_[r]), (p_[i] - p_[r])) > 0) {
            Clc(l, i);
            Clc(i, r);
            (dp_[l][r] += dp_[l][i] * dp_[i][r]) %= mod_;
        }
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    Triangulation tr(n);
    tr.FillTriangulation();
    std::cout << tr.FindTriangulationNum () << std::endl;
    return 0;
}