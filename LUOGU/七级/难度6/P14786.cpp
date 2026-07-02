#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<pair<long long, long long>> people(n);
        for (int i = 0; i < n; i++) {
            cin >> people[i].first >> people[i].second;
        }
        
        // Sort by starting floor
        sort(people.begin(), people.end());
        
        // Greedy: to maximize time, we should visit floors in an order that maximizes total distance
        // Key insight: we can visit floors in any order, picking up and dropping off
        
        // Strategy: alternate between far starts and far destinations
        // Sort starts and destinations separately
        
        vector<long long> starts, dests;
        for (auto& p : people) {
            starts.push_back(p.first);
            dests.push_back(p.second);
        }
        
        sort(starts.begin(), starts.end());
        sort(dests.begin(), dests.end(), greater<long long>());
        
        // Interleave to maximize total distance
        long long total = 0;
        long long current = 1; // Start from floor 1
        
        // Visit far starts first, then far destinations
        // Or interleave them optimally
        
        // Simple greedy: visit in order that maximizes each step
        vector<long long> visits;
        int si = 0, di = 0;
        
        while (si < (int)starts.size() || di < (int)dests.size()) {
            long long nextStart = (si < (int)starts.size()) ? starts[si] : -1;
            long long nextDest = (di < (int)dests.size()) ? dests[di] : -1;
            
            // Choose the one farther from current
            if (nextStart == -1) {
                visits.push_back(nextDest);
                di++;
            } else if (nextDest == -1) {
                visits.push_back(nextStart);
                si++;
            } else {
                long long dStart = abs(nextStart - current);
                long long dDest = abs(nextDest - current);
                if (dStart >= dDest) {
                    visits.push_back(nextStart);
                    si++;
                } else {
                    visits.push_back(nextDest);
                    di++;
                }
            }
        }
        
        for (long long v : visits) {
            total += abs(v - current);
            current = v;
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
