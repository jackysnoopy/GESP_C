#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    // Convert to deficit/surplus array
    vector<int> d(n);
    for (int i = 0; i < n; i++) d[i] = c[i] - 1;
    // Find starting point to minimize sum of prefix^2
    // Equivalent to: find cyclic shift that minimizes sum of squared prefix sums
    // Use the observation: minimize max prefix sum difference
    // For circular barn: find the split point that minimizes total d^2
    // Greedy: start from the room right after a room with 0 cows (surplus = -1)
    // Actually: find the largest gap of consecutive rooms with c[i]>=1
    // The optimal is to start right after a room with c[i]>=2 (or equivalently,
    // find the longest consecutive run of rooms with c[i]<=1 minus rooms with c[i]=0)
    
    // Simpler approach: compute prefix sums and find the shift
    vector<int> ps(n+1, 0);
    for (int i = 0; i < n; i++) ps[i+1] = ps[i] + d[i];
    // ps[n] = 0 (total is 0)
    // We want to find shift k that minimizes sum of (ps[i+k]-ps[k])^2 for i=1..n-1
    // = sum ps[i+k]^2 - 2*ps[k]*sum ps[i+k] + (n-1)*ps[k]^2
    // Since sum ps[i+k] = -ps[k] (total sum is 0, excluding last), this simplifies.
    
    // Actually, standard approach for this problem:
    // The optimal starting point is right after the room with max cumulative deficit.
    // Equivalent: find the room where if you start there, you never go negative.
    
    // Compute circular prefix sums, find the starting point
    // that minimizes sum of squared prefix sums.
    
    // Brute force for n<=1000:
    long long best = 1e18;
    for (int start = 0; start < n; start++) {
        long long cost = 0;
        long long cur = 0;
        for (int i = 1; i < n; i++) {
            int idx = (start + i) % n;
            cur += d[idx];
            cost += cur * cur;
        }
        best = min(best, cost);
    }
    cout << best << "\n";
    return 0;
}
