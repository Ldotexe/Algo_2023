#include <iostream>
#include <vector>

class ShortGCDFinder {
public:
    void GetArr ();
    int FindShortGCD ();

private:
    int FindGCD (int first, int last);
    int GCD (int a, int b);

    int n_;
    std::vector<int> arr_;
};

int main () {
    ShortGCDFinder sf;
    sf.GetArr();
    std::cout << sf.FindShortGCD () << std::endl;
    return 0;
}

void ShortGCDFinder::GetArr () {
    std::cin >> n_;
    arr_.resize (n_);
    for (int i = 0; i < n_; ++i) {
        std::cin >> arr_[i];
    }
}

int ShortGCDFinder::FindShortGCD (){
    int counter = 0;
    for (int i = 0; i < n_; ++i) {
        if (arr_[i] == 1) {
            ++counter;
        }
    }
    if (counter != 0) {
        return n_ - counter;
    }
    int subans = -1;
    for (int i = 0; i < n_; ++i) {
        int cur_gcd = arr_[i];
        for (int j = i + 1; j < n_; ++j) {
            cur_gcd = GCD (cur_gcd, arr_[j]);
            if (cur_gcd == 1 && (j - i < subans || subans == -1)) {
                subans = j - i;
                break;
            }
        }
    }
    if (subans != -1) {
        return n_ + subans - 1;
    }

    return -1;
}

int ShortGCDFinder::GCD (int a, int b) {
	for (; b; std::swap (a, b)) {
		a %= b;
	}
	return a;
}