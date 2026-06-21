#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long l, r;
    cin >> l >> r;
    long long ans = 0;
    for (long long i = l; i <= r; i++) {
        long long x = i;
        while ((x & 1) == 0 && x > 0) x >>= 1;
        if (x == 1) ans++;
    }
    cout << ans << "\n";
    return 0;
}
