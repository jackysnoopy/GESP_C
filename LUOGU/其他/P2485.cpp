#include <iostream>
#include <map>
#include <cmath>
using namespace std;
long long power(long long b, long long e, long long m) {
    long long r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x; return g;
}
long long bsgs(long long a, long long b, long long p) {
    if (b == 1) return 0;
    long long m = (long long)ceil(sqrt((double)p));
    map<long long, long long> mp;
    long long cur = b;
    for (long long j = 0; j < m; ++j) { mp[cur] = j; cur = cur * a % p; }
    long long am = power(a, m, p); cur = 1;
    for (long long i = 1; i <= m; ++i) {
        cur = cur * am % p;
        if (mp.count(cur)) return i * m - mp[cur];
    }
    return -1;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long T, y, z, p;
    cin >> T >> p;
    while (T--) {
        cin >> y >> z >> p;
        if (p == 1) { cout << 0 << '\n'; continue; }
        long long x, dummy;
        if (exgcd(y, p, x, dummy) == 1) {
            cout << power(y, z, p) << '\n';
        } else if (y % p == 0) {
            if (z % p == 0) { long long xx; exgcd(y, p, xx, dummy); cout << ((xx % p + p) % p) << '\n'; }
            else cout << -1 << '\n';
        } else {
            long long g = exgcd(y, p, x, dummy);
            if (z % g != 0) { cout << -1 << '\n'; continue; }
            p /= g; z /= g; y %= p;
            long long ans = bsgs(y, z, p);
            cout << (ans == -1 ? -1 : ans) << '\n';
        }
    }
    return 0;
}
