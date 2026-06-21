#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    vector<pair<int,int>> domestic(m1), international(m2);
    for (int i = 0; i < m1; i++) cin >> domestic[i].first >> domestic[i].second;
    for (int i = 0; i < m2; i++) cin >> international[i].first >> international[i].second;
    
    sort(domestic.begin(), domestic.end());
    sort(international.begin(), international.end());
    
    // Simulate greedy with n bridges, assign each flight to a bridge
    // Record the bridge index for each flight
    auto simulate = [n](const vector<pair<int,int>>& flights) -> vector<int> {
        vector<int> cnt(n + 1, 0);
        // min-heap of (free_time, bridge_id)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        for (int b = 1; b <= n; b++) pq.push(make_pair(0, b));
        
        for (auto& f : flights) {
            int arr = f.first, dep = f.second;
            // Pop all free bridges
            vector<pair<int,int>> temp;
            while (!pq.empty() && pq.top().first <= arr) {
                temp.push_back(pq.top());
                pq.pop();
            }
            if (!temp.empty()) {
                // Use the bridge with the smallest id
                int bridgeId = temp[0].second;
                for (int i = 1; i < (int)temp.size(); i++) {
                    if (temp[i].second < bridgeId) bridgeId = temp[i].second;
                }
                cnt[bridgeId]++;
                pq.push(make_pair(dep, bridgeId));
                // Put back the other free bridges
                for (int i = 0; i < (int)temp.size(); i++) {
                    if (temp[i].second != bridgeId) {
                        pq.push(temp[i]);
                    }
                }
            }
            // If no free bridge, flight is not served
        }
        // prefix sum
        for (int k = 2; k <= n; k++) cnt[k] += cnt[k-1];
        return cnt;
    };
    
    vector<int> dom = simulate(domestic);
    vector<int> intl = simulate(international);
    
    int best = 0;
    for (int k = 0; k <= n; k++) {
        int d = (k >= 1 && k <= n) ? dom[k] : 0;
        int ii = ((n-k) >= 1 && (n-k) <= n) ? intl[n-k] : 0;
        best = max(best, d + ii);
    }
    cout << best << "\n";
    return 0;
}
