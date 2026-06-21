#include <iostream>
#include <vector>
using namespace std;
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<long long> m(n), r(n);
    long long M = 1;
    for (int i = 0; i < n; ++i) { cin >> m[i] >> r[i]; M *= m[i]; }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long Mi = M / m[i], x, y;
        exgcd(Mi, m[i], x, y);
        ans = (ans + r[i] * Mi % M * ((x % m[i] + m[i]) % m[i]) % M) % M;
    }
    cout << (ans % M + M) % M << '\n';
    return 0;
}
