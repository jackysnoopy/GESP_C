#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> d(n), f(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    for (int i = 0; i < n; i++) cin >> f[i];
    // Greedy: simulate from left to right
    // For each pair (i, n-1-i), we can swap their fuel
    // We want to maximize how far we can go
    int half = n / 2;
    long long fuel = x;
    int ans = 0;
    int swaps = 0;
    int lo = 0, hi = n - 1;
    // Process houses in order, at each step decide whether to swap
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        if (fuel < d[i]) break;
        fuel -= d[i];
        // House i and house n-1-i are a pair
        int j = n - 1 - i;
        if (i < j) {
            // Decide: take f[i] or f[j]
            if (f[i] >= f[j]) {
                fuel += f[i];
            } else {
                fuel += f[j];
                swaps++;
            }
        } else if (i == j) {
            fuel += f[i];
        } else {
            // Already processed as pair of j
            if (!used[i]) {
                fuel += f[i];
            }
        }
        used[i] = true;
        if (i < n - 1 - i) used[n - 1 - i] = true;
        ans = i + 1;
    }
    cout << ans << " " << swaps << "\n";
    return 0;
}
