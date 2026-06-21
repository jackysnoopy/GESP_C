#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<long long> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < m; ++j) cin >> b[j];
    sort(a.begin(), a.end(), greater<long long>());
    sort(b.begin(), b.end(), greater<long long>());
    long long base = 0;
    for (long long x : a) base += x;
    for (long long x : b) base += x;
    long long bonus = 0;
    int cnt = min(n, m);
    for (int i = 0; i < cnt; ++i) {
        long long best = 0;
        best = max(best, a[i] + b[i]);
        best = max(best, 2LL * a[i]);
        best = max(best, b[i] + k);
        bonus += best - a[i] - b[i];
    }
    cout << base + bonus << '\n';
    return 0;
}
