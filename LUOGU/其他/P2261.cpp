#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k;
    cin >> n >> k;
    long long ans = n * k;
    for (long long l = 1, r; l <= n && l <= k; l = r + 1) {
        r = min(k / (k / l), n);
        ans -= (k / l) * (l + r) * (r - l + 1) / 2;
    }
    cout << ans << '\n';
    return 0;
}
