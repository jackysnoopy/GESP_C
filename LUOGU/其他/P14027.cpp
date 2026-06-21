#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, k;
    cin >> a >> b >> k;
    int days = 0;
    while (a < b) {
        if (k == 1) {
            a += 1;
        } else {
            // Choose multiply if it gets us to b faster
            if (a == 0) {
                a += k;
            } else if (a * k - a >= b - a) {
                // multiply is at least as good or overshoots
                a *= k;
            } else {
                a += k;
            }
        }
        days++;
    }
    cout << days << endl;
    return 0;
}
