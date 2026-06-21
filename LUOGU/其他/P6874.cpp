#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> m(n), s(n);
    for (int i = 0; i < n; i++) cin >> m[i];
    for (int i = 0; i < n; i++) cin >> s[i];
    // Both stacks must form a V-shape: decreasing then increasing
    // Adjacent columns differ by exactly 1
    // Total = m[i] + s[i] for each column
    // Target: h[i] = h[mid] - |i-mid| for some mid
    // Minimize sum |total[i] - h[i]|
    // Try each possible mid and base height
    long long ans = 1e18;
    int mid = n / 2;
    for (long long base = 0; base <= 2000000; base++) {
        long long cost = 0;
        for (int i = 0; i < n; i++) {
            long long target = base - abs(i - mid);
            if (target < 0) target = 0;
            cost += abs(m[i] + s[i] - target);
        }
        ans = min(ans, cost);
    }
    cout << ans << "\n";
    return 0;
}
