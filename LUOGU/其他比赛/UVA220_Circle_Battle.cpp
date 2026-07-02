#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double r;
    while (cin >> n >> r && (n != 0 || r != 0)) {
        double angle = 2.0 * acos(-1.0) / n;
        double d = 2.0 * r * sin(angle / 2.0);
        cout << fixed << setprecision(2) << d << "\n";
    }

    return 0;
}
