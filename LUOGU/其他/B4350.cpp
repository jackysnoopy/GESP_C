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
    long long ans = 0;
    for (int d = 0; d < n; d++) {
        long long best = 0;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] < 0) continue;
            long long val = a[i];
            if (val > best) { best = val; idx = i; }
        }
        if (idx == -1) break;
        ans += a[idx];
        a[idx] = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] >= 0) a[i] = (long long)sqrt((double)a[i]);
        }
    }
    cout << ans << "\n";
    return 0;
}
