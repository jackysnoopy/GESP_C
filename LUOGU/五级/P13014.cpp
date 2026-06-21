#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long g = 0;
    for (int i = 1; i < n; i++) {
        g = gcd(g, llabs(a[i] - a[0]));
    }
    while (q--) {
        long long i;
        cin >> i;
        cout << gcd(a[0] + i, g) << "\n";
    }
    return 0;
}
