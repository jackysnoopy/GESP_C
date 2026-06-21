#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    sort(x.begin(), x.end());
    // Two pointers: find longest interval where we can visit all
    // Start at 0, visit leftmost and rightmost
    // Cost = min(2*left + right, left + 2*right) where left = |x_l|, right = |x_r|
    int ans = 0;
    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n) {
            int left = abs(x[l]);
            int right = abs(x[r]);
            int cost = min(2 * left + right, left + 2 * right) + (right - left);
            // Actually: go to x[l], then to x[r]. Total = |x[l]| + |x[r]-x[l]| = |x[r]| (if same sign)
            // More carefully: visit [l..r], start at 0
            // Option 1: go left first then right: 2*|x[l]| + |x[r]|  (if x[l]<0)
            // Option 2: go right first then left: 2*|x[r]| + |x[l]|
            int ldist = -x[l]; // if x[l] <= 0
            int rdist = x[r];  // if x[r] >= 0
            int c1 = 2 * ldist + rdist;
            int c2 = ldist + 2 * rdist;
            int c3 = max(ldist, rdist); // if same direction
            int total = min(min(c1, c2), c3);
            if (total <= t) r++;
            else break;
        }
        ans = max(ans, r - l);
        if (r <= l) r = l + 1;
    }
    cout << ans << "\n";
    return 0;
}
