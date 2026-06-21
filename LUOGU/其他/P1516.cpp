#include <iostream>
#include <algorithm>
using namespace std;
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long x, y, m1, m2, L;
    cin >> x >> y >> m1 >> m2 >> L;
    long long a = m1 - m2, b = L, c = y - x;
    long long xp, yp;
    long long g = exgcd(a, b, xp, yp);
    if (c % g != 0) { cout << "Impossible" << '\n'; return 0; }
    long long t = xp * (c / g);
    long long mod = abs(b / g);
    t = (t % mod + mod) % mod;
    cout << t << '\n';
    return 0;
}
