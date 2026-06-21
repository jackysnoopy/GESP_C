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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long r = 0, m = 1;
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        long long x, y;
        long long g = exgcd(m, a, x, y);
        if ((b - r) % g != 0) { cout << -1 << '\n'; return 0; }
        long long t = (b - r) / g * (x % (a / g));
        r += m * t;
        m = m / g * a;
        r = (r % m + m) % m;
    }
    cout << r << '\n';
    return 0;
}
