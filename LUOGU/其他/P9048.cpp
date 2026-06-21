#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long t, f;
    cin >> n >> t >> f;
    vector<pair<long long, long long>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    // Sort by position, then greedily pick check-ins
    sort(a.begin(), a.end());
    // DP or greedy: at each position, decide to check in or not
    // Time cost: travel + wait
    // Greedy: for each check-in point, compute time to reach it
    // Then greedily pick as many as possible
    vector<long long> times(n);
    for (int i = 0; i < n; i++) {
        times[i] = a[i].first + a[i].second; // arrival time + wait end
    }
    // We need to find max check-ins such that total time <= t
    // This is interval scheduling with a twist
    // Actually: we start at 0, must end at f.
    // At position x_i, we arrive at time x_i, wait until a_i, check in.
    // Then continue to next.
    // Cost to go from i to j: max(times[i], x_j) + ... 
    // This is a scheduling problem.
    // Greedy: sort by x_i + a_i (time we leave check-in i), pick greedily
    sort(times.begin(), times.end());
    int ans = 0;
    long long curTime = 0;
    for (int i = 0; i < n; i++) {
        long long arrive = a[i].first;
        long long leave = max(arrive, curTime) + a[i].second;
        if (leave + (f - a[i].first) <= t) {
            ans++;
            curTime = leave;
        }
    }
    cout << ans << "\n";
    return 0;
}
