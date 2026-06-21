#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> a(n);
    long long total = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; total += a[i]; }
    
    if (total < m) { cout << 0 << "\n"; return 0; }
    
    long long ans = 0;
    // Try all possible values of t
    // t ranges from 1 to total/k (since k*t <= total)
    // But t can also be determined by the asteroid values.
    // For efficiency, iterate t from 1 to some bound.
    // The number of distinct values of floor(a[i]/t) is O(sqrt(a[i])) per asteroid.
    // Total distinct values across all asteroids is O(n * sqrt(max_a)).
    // For n=20, max_a=10^6, this is about 20*1000 = 20000. Manageable.
    
    // Actually, let's just iterate t from 1 to max_a.
    // max_a can be up to 10^9, which is too slow.
    // Use the optimization: for each asteroid, the values of floor(a[i]/t) change at O(sqrt(a[i])) points.
    
    // Simpler: iterate t from 1 to some reasonable bound.
    // The answer is at most total (when k=m).
    // For k < m, the answer is at most k * total / m.
    // The optimal t is at most total / m.
    
    long long maxT = total / m + 1;
    if (maxT > 1000000) maxT = 1000000; // safety bound
    
    for (long long t = 1; t <= maxT; t++) {
        long long r = 0;
        for (int i = 0; i < n; i++) r += a[i] / t;
        if (r < m) continue;
        // Total kept crystals <= total - (r-m)*t
        long long kept = total - (r - m) * t;
        long long cur = k * kept / m;
        if (cur > ans) ans = cur;
    }
    
    cout << ans << "\n";
    return 0;
}
