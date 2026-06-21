#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long lo = 0, hi = 2000000000LL;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        bool ok = true;
        long long rem = 0;
        for (int i = n - 1; i >= 0; i--) {
            rem = max(0LL, rem + a[i] - mid);
        }
        if (rem <= 0) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
