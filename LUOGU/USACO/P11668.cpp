#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // A moo (a, b, b) with a != b occurs if:
    // - a appears at some position
    // - b appears at two positions after a's position
    // OR
    // - b appears at two positions, and a appears before the second b.
    //
    // Count distinct (a, b) pairs where this is possible.
    //
    // For each value b that appears >= 2 times:
    //   Find the position of the second occurrence of b.
    //   All values a != b that appear before this position contribute.
    //
    // For each value a:
    //   Find the position of a's occurrence.
    //   All values b != a that appear >= 2 times, with second occurrence after a's position, contribute.
    
    // Efficient approach:
    // 1. For each value v, find its first and last occurrence.
    // 2. For each value b with count >= 2:
    //    Find the position of the second occurrence (second smallest position of b).
    //    Count all distinct values a != b that appear before this position.
    // 3. Sum over all b.
    
    // Use a sorted set or BIT to count distinct values.
    // For each b (in order of second occurrence):
    //   Query: number of distinct values before this position, excluding b itself.
    //   This gives the count of valid a values.
    
    // Find positions of each value
    vector<vector<int>> positions(n + 1);
    for (int i = 0; i < n; i++) {
        positions[a[i]].push_back(i);
    }
    
    // Collect events: for each b with count >= 2, the event is at the second occurrence position.
    vector<pair<int,int>> events; // (position, value)
    for (int v = 1; v <= n; v++) {
        if ((int)positions[v].size() >= 2) {
            events.push_back({positions[v][1], v});
        }
    }
    sort(events.begin(), events.end());
    
    // Sweep line: add values as we go, query count of distinct values before each event.
    // Use a BIT or just a running count.
    vector<bool> seen(n + 1, false);
    int distinct_count = 0;
    long long ans = 0;
    int event_idx = 0;
    
    for (int i = 0; i < n; i++) {
        if (!seen[a[i]]) {
            seen[a[i]] = true;
            distinct_count++;
        }
        while (event_idx < (int)events.size() && events[event_idx].first == i) {
            int b = events[event_idx].second;
            // Count distinct values before position i, excluding b
            int cnt = distinct_count - (seen[b] ? 1 : 0);
            ans += cnt;
            event_idx++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
