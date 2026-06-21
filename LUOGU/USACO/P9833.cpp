#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> stations(n); // (distance from city, fuel)
    for (int i = 0; i < n; i++) cin >> stations[i].first >> stations[i].second;
    int l, p;
    cin >> l >> p;
    
    // Sort stations by distance from city (descending = closest first)
    sort(stations.begin(), stations.end(), greater<pair<int,int>>());
    
    // Greedy: drive from position l towards city (position 0)
    // At each station, add fuel to priority queue
    // When fuel runs out, take the max fuel from priority queue
    
    priority_queue<int> pq;
    int fuel = p;
    int pos = l; // current position (distance from city)
    int ans = 0;
    int idx = 0;
    
    while (pos > 0) {
        // Add all stations between pos and the next stop
        while (idx < n && stations[idx].first >= pos) {
            pq.push(stations[idx].second);
            idx++;
        }
        
        // Drive one unit
        fuel--;
        pos--;
        
        if (fuel < 0 && !pq.empty()) {
            fuel += pq.top();
            pq.pop();
            ans++;
        } else if (fuel < 0 && pq.empty()) {
            cout << "-1\n";
            return 0;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
