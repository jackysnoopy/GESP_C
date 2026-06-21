#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long b, p;
    cin >> n >> b >> p;
    vector<long long> a(n);
    long long mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    long long x = 2 * mx;
    long long ans = 1;
    long long base = (x + 233) % p;
    long long exp = b;
    while (exp > 0) {
        if (exp & 1) ans = ans * base % p;
        base = base * base % p;
        exp >>= 1;
    }
    cout << ans << "\n";
    return 0;
}
