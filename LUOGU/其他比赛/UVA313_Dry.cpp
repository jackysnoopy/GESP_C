#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double L, W, D, H;
    while (cin >> L >> W >> D >> H) {
        if (L == 0 && W == 0 && D == 0 && H == 0) break;
        double volume = L * W * D;
        double surfaceArea = 2.0 * (L * W + L * D + W * D);
        double total = volume + surfaceArea;
        cout << (int)round(total) << "\n";
    }
    return 0;
}
