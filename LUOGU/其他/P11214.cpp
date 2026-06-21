#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long MOD = 1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<long long> m(n), a(n);
    for (int i = 0; i < n; i++) cin >> m[i];
    for (int i = 0; i < n; i++) cin >> a[i];
    // k=0: count = 1
    long long ans = 1;
    // For k >= 1: find max k
    long long maxK = 0;
    for (int i = 0; i < n; i++) {
        maxK = max(maxK, max(a[i] - 1, m[i] - a[i]));
    }
    // For each k, count = product of choices per dimension
    // But n can be up to 2e5, and maxK up to 1e9. Can't iterate over k.
    //
    // Key observation: for each dimension i, the number of choices is:
    // f_i(k) = 0 if k > max(a[i]-1, m[i]-a[i])
    //         2 if k <= min(a[i]-1, m[i]-a[i])
    //         1 if min < k <= max
    // So f_i is a step function with at most 2 breakpoints.
    // The product of f_i has at most 2n breakpoints.
    // Between breakpoints, f_i is constant, so the product is constant.
    // We can compute the sum efficiently.
    
    // Collect all breakpoints
    vector<long long> bps;
    bps.push_back(0); // k=0 is special (count=1, not product)
    for (int i = 0; i < n; i++) {
        long long lo = min(a[i] - 1, m[i] - a[i]);
        long long hi = max(a[i] - 1, m[i] - a[i]);
        bps.push_back(lo + 1);
        bps.push_back(hi + 1);
    }
    sort(bps.begin(), bps.end());
    bps.erase(unique(bps.begin(), bps.end()), bps.end());
    
    // For each interval [bps[j], bps[j+1]-1], compute the product
    for (int j = 0; j + 1 < (int)bps.size(); j++) {
        long long k_start = bps[j];
        long long k_end = bps[j + 1] - 1;
        if (k_start > maxK || k_end < 1) continue;
        k_start = max(k_start, 1LL);
        k_end = min(k_end, maxK);
        if (k_start > k_end) continue;
        // Compute product of f_i(k) for k = k_start (representative of this interval)
        long long prod = 1;
        for (int i = 0; i < n; i++) {
            long long lo = min(a[i] - 1, m[i] - a[i]);
            long long hi = max(a[i] - 1, m[i] - a[i]);
            int choices = 0;
            if (k_start <= lo) choices = 2;
            else if (k_start <= hi) choices = 1;
            else choices = 0;
            prod = prod * choices % MOD;
            if (prod == 0) break;
        }
        long long len = k_end - k_start + 1;
        ans = (ans + prod % MOD * (len % MOD)) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
