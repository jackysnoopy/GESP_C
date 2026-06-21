#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 200005;
int par[MAXN];

int find(int x) {
    if (x < 0) return -1;
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> segs(m);
    for (int i = 0; i < m; i++) cin >> segs[i].first >> segs[i].second;
    
    // Group segments by left endpoint
    vector<vector<pair<int,int>>> startAt(n + 1); // startAt[l] = list of (r, index)
    for (int i = 0; i < m; i++) {
        int l = segs[i].first;
        if (l <= n) startAt[l].push_back({segs[i].second, i});
    }
    
    for (int i = 0; i <= n; i++) par[i] = i;
    
    // min-heap of (r, l)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    int count = 0;
    for (int k = 1; k <= n; k++) {
        // Add segments with l == k
        for (auto& p : startAt[k]) {
            pq.push({p.first, k});
        }
        // Try to assign segments
        while (!pq.empty()) {
            int r = pq.top().first;
            int l = pq.top().second;
            if (r < k) {
                pq.pop();
                continue;
            }
            // Segment [l, r] with l <= k <= r
            // Find rightmost available seat in [l, k]
            int seat = find(k);
            if (seat >= l) {
                count++;
                par[seat] = find(seat - 1);
                pq.pop();
            } else {
                // No seat available in [l, k], this segment can't be assigned for any larger k either
                // because l is fixed and seats only get more used
                // Actually for larger k' > k, we'd check [l, k'] which has more seats
                // But with DSU, if find(k) < l, then find(k') might also be < l if all seats in [l,k'] are used
                // Actually no - for larger k, find(k') could return a seat in (k, k'] which might be >= l
                // But l <= k, so we need a seat in [l, k']. If find(k) < l, all seats in [l,k] are used.
                // For k' > k, seats k+1..k' might be available and >= l.
                // So we should NOT discard this segment yet.
                break;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
