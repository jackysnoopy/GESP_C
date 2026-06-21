#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        long long x;
        cin >> x;
        int cnt = 0;
        for (long long p = 2; p * p <= x; p++) {
            if (x % p == 0) {
                cnt++;
                while (x % p == 0) x /= p;
            }
        }
        if (x > 1) cnt++;
        cout << (cnt == 2 ? 1 : 0) << "\n";
    }
    return 0;
}
