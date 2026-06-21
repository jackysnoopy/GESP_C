#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
long long a[100001];
bool check(long long mx) {
    int cnt = 1;
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur + a[i] > mx) { cnt++; cur = a[i]; }
        else cur += a[i];
    }
    return cnt <= m;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        lo = max(lo, a[i]);
        hi += a[i];
    }
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
