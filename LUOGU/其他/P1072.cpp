#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;
        int cnt = 0;
        for (long long a = a1; a <= b1; a += a1) {
            if (gcd(a0, a) != a1) continue;
            if (b1 % a != 0) continue;
            long long b = b1 / a;
            if (b0 * b / gcd(b0, b) == b1) cnt++;
        }
        cout << cnt << '\n';
    }
    return 0;
}
