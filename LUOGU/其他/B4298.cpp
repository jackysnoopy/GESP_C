#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    // Remove rods until sorted (non-decreasing or non-increasing).
    // Minimize removals = maximize keep.
    // LIS (non-decreasing) or LIS from right (non-increasing).
    int m1 = 0, m2 = 0;
    vector<int> dp;
    // LIS non-decreasing
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(dp.begin(), dp.end(), h[i]);
        if (it == dp.end()) dp.push_back(h[i]);
        else *it = h[i];
    }
    m1 = dp.size();
    dp.clear();
    // LIS non-increasing (reverse array and find LIS non-decreasing, or find LDS)
    for (int i = n - 1; i >= 0; i--) {
        auto it = upper_bound(dp.begin(), dp.end(), h[i]);
        if (it == dp.end()) dp.push_back(h[i]);
        else *it = h[i];
    }
    m2 = dp.size();
    cout << n - max(m1, m2) << "\n";
    return 0;
}
