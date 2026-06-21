#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    sort(a.begin(), a.end());
    // Strawberry cake problem: minimize maximum slice difference.
    // Actually I don't have the full problem. Let me implement a basic solution.
    // Common: split m portions into n groups, minimize max(group_sum) - min(group_sum).
    // Or: minimize the maximum slice size.
    // Without full problem text, I'll implement a greedy binary search.
    
    // Binary search on max slice size
    int lo = a[m - 1], hi = 2000000000;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int groups = 0;
        long long cur = 0;
        for (int i = 0; i < m; i++) {
            if (cur + a[i] > mid) {
                groups++;
                cur = a[i];
            } else {
                cur += a[i];
            }
        }
        if (cur > 0) groups++;
        if (groups <= n) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
    return 0;
}
