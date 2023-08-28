#include <iostream>

struct Dot {
    int x;
    int y;
};

class Segment {
public:
    double FindDistance (Segment other);
private:    
    Dot s_;
    Dot e_;
};

double Segment::FindDistance (Segment other) {
    
    return 1;
}

int main () {

    return 0;
}