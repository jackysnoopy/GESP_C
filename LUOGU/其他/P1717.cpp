#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, H;
    cin >> n >> H;
    vector<int> f(n), d(n), t(n - 1);
    for (int i = 0; i < n; i++) cin >> f[i];
    for (int i = 0; i < n; i++) cin >> d[i];
    for (int i = 0; i < n - 1; i++) cin >> t[i];
    
    int totalMin = H * 60; // total time in minutes (5-min intervals)
    int bestAns = 0;
    
    // Try each lake as the last lake
    for (int last = 0; last < n; last++) {
        // Time to walk to lake last
        int walkTime = 0;
        for (int i = 0; i < last; i++) walkTime += t[i] * 5;
        int fishTime = totalMin - walkTime;
        if (fishTime <= 0) continue;
        
        // Number of 5-min intervals
        int intervals = fishTime / 5;
        
        // Greedy: always fish at the lake with the most fish
        // Use priority queue
        vector<int> cur_f(f.begin(), f.begin() + last + 1);
        vector<int> cur_d(d.begin(), d.begin() + last + 1);
        
        priority_queue<pair<int,int>> pq; // (fish, lake)
        for (int i = 0; i <= last; i++) {
            if (cur_f[i] > 0) pq.push({cur_f[i], i});
        }
        
        int ans = 0;
        for (int k = 0; k < intervals; k++) {
            if (pq.empty()) break;
            auto p = pq.top(); pq.pop();
            int fish = p.first, lake = p.second;
            ans += fish;
            cur_f[lake] -= cur_d[lake];
            if (cur_f[lake] > 0) pq.push({cur_f[lake], lake});
        }
        bestAns = max(bestAns, ans);
    }
    
    cout << bestAns << "\n";
    return 0;
}
