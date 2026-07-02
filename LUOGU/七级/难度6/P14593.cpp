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
    
    vector<pair<long long, long long>> contests(n);
    for (int i = 0; i < n; i++) {
        cin >> contests[i].first >> contests[i].second;
    }
    
    // Sort by difficulty a_i
    sort(contests.begin(), contests.end());
    
    // Greedy: use priority queue to pick best b_i among available contests
    priority_queue<long long> pq;
    long long ability = 0;
    int idx = 0;
    int count = 0;
    
    while (idx < n || !pq.empty()) {
        // Add all contests with a_i <= current ability
        while (idx < n && contests[idx].first <= ability) {
            pq.push(contests[idx].second);
            idx++;
        }
        
        if (pq.empty()) {
            if (idx < n) {
                // Skip to next contest's difficulty
                ability = contests[idx].first;
                continue;
            }
            break;
        }
        
        // Pick contest with highest b_i
        long long best = pq.top();
        pq.pop();
        
        if (best >= ability) {
            ability = max(ability, best);
            count++;
        }
    }
    
    cout << count << "\n";
    
    return 0;
}
