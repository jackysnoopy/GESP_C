#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<long long> a(n), b(n);
    for (long long &x : a) cin >> x;
    for (long long &x : b) cin >> x;
    long long have = m;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long extra = min(b[i], have);
        ans += a[i] + extra;
        have -= extra;
    }
    cout << ans << '\n';
    return 0;
}
