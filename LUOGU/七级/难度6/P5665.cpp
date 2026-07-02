#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 40000005;
const long long INF = 1e18;

long long prefix[MAXN];
int n;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int type;
    cin >> n >> type;
    
    if (type == 0) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
    } else {
        long long last;
        cin >> last;
        a[1] = last;
        for (int i = 2; i <= n; i++) {
            a[i] = (a[i-1] * 998244353 + 7) % 1000000007;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i-1] + a[i];
    }
    
    // dp[i] = minimum cost for prefix [1..i]
    // We use greedy approach: process from back to front
    // For each position, find the longest valid segment
    
    // Key insight: In optimal solution, segment sums are increasing
    // We can use binary search to find split points
    
    // Greedy from back: for each position i (from n down to 1),
    // find the best split point j such that:
    // 1. sum(j+1..i) < sum(i+1..n) (if i < n)
    // 2. The segment [j+1..i] is valid
    
    // For efficiency, we use the observation that optimal partition
    // has a specific structure that can be computed greedily
    
    long long ans = 0;
    long long last_sum = INF;
    int pos = n;
    
    // Greedy from back to front
    while (pos > 0) {
        // Binary search for the optimal split point
        // We want to find the longest segment [j+1..pos] such that
        // sum(j+1..pos) < last_sum and sum(j+1..pos) is maximized
        
        int lo = 0, hi = pos - 1;
        int best = 0;
        
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            long long seg_sum = prefix[pos] - prefix[mid];
            
            if (seg_sum < last_sum) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        
        long long seg_sum = prefix[pos] - prefix[best];
        ans += seg_sum * seg_sum;
        last_sum = seg_sum;
        pos = best;
    }
    
    cout << ans << endl;
    
    return 0;
}
