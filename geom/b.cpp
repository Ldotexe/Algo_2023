#include <bits/stdc++.h>


const int kN = 1e5 + 10;
const int64_t kMax = 1e9;

struct Pt {
    int64_t x;
    int64_t y;
    int64_t Vec(Pt a) {
        return x * a.y - a.x * y;
    }
    int64_t Sz2() {
        return x * x + y * y;
    }
    Pt operator-(Pt a) {
        return {x - a.x, y - a.y};
    }
};

int n;
Pt a[kN], p;
std::vector < Pt > ans, t;

bool Cmp(Pt a, Pt b) {
    Pt f = a - p;
    Pt s = b - p;
    if (f.Vec(s) > 0)  {
        return true;
    }
    if (f.Vec(s) < 0) {
        return false;
    }
    return f.Sz2() < s.Sz2();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    p.y = 3e9;
    p.x = 3e9;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i].x >> a[i].y;

        a[i].x += kMax;
        a[i].y += kMax;
        if (a[i].y < p.y || (a[i].y == p.y && a[i].x < p.x)) {
            p = a[i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i].x != p.x || a[i].y != p.y) {
            t.push_back(a[i]);
        }
    }
    sort(t.begin(), t.end(), Cmp);
    ans.push_back(p);
    for (auto u : t) {
        if (ans.size() < 2) {
            ans.push_back(u);
        }
        else {
            while (true) {
                if (ans.size() == 1) {
                    break;
                }
                Pt f = u - ans.back();
                Pt s = ans.back() - ans[ans.size() - 2];

                if (s.Vec(f) <= 0) {
                    ans.pop_back();
                } else {
                    break;
                } 
            }
            ans.push_back(u);
        }
    }
    std::cout << ans.size() << '\n';

    for (auto u : ans) {
        u.x -= kMax;
        u.y -= kMax;
        std::cout << u.x << ' ' << u.y << '\n';
    }

    int64_t sum = 0;
    for (int i = 0; i < static_cast<int>(ans.size() - 1); ++i) {
        sum += ans[i].Vec(ans[i + 1]);
    }
    sum += ans.back().Vec(ans[0]);

    if (sum % 2 == 0) {
        std::cout << sum / 2 << '\n';
    } else {
        std::cout << sum / 2 << ".5" << '\n';
    }


    return 0;
}