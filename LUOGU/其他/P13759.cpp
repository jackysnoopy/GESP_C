#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // n/m groups, each of size n/m (odd).
    // Minimize sum of medians.
    // Sort ascending. Pick m medians from positions: 
    // if group size = s = n/m, then in each group, the median is at position s/2 (0-indexed within group).
    // Optimal: sort ascending. The medians should be at positions s/2, 3s/2+s/2=2s, ...
    // Actually: sort ascending. Take elements at positions s/2, s/2+s, s/2+2s, ...
    // Wait: in a sorted array, if we form groups of size s:
    // Group 0: a[0..s-1], median = a[s/2]
    // Group 1: a[s..2s-1], median = a[s+s/2]
    // ...
    // Group m-1: a[(m-1)s..ms-1], median = a[(m-1)s+s/2]
    // Sum of medians = sum of a[k*s + s/2] for k=0..m-1.
    // Is this optimal? Yes, because sorting and grouping contiguously minimizes sum of medians.
    // Proof sketch: any other arrangement would have a larger median for some group.
    
    sort(a.begin(), a.end());
    int s = n / m;
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans += a[i * s + s / 2];
    }
    cout << ans << endl;
    return 0;
}
