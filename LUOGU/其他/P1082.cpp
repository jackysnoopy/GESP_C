#include <iostream>
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
    long long a, b, x, y;
    cin >> a >> b;
    exgcd(a, b, x, y);
    cout << ((x % b + b) % b) << '\n';
    return 0;
}
