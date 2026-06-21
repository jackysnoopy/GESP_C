#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int xiuqix;
    int a, b, c;
    cin >> a >> b >> c;
    // a days of +1, b days of 0, c days of -1. Fatigue starts at 0.
    // Maximize days where fatigue = 0.
    // Each (+1, -1) pair can return to 0. Number of such pairs = min(a, c).
    // On each return day, fatigue = 0. Plus all b zero-days keep fatigue at 0.
    // Answer = min(a, c) + b.
    // Verified with samples: (1,2,1)->3, (5,1,4)->5.
    xiuqix = min(a, c) + b;
    cout << xiuqix << "\n";
    return 0;
}
