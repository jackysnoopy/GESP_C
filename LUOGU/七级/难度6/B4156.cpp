#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> ships(n);
    for (int i = 0; i < n; i++) {
        cin >> ships[i].first >> ships[i].second;
    }
    
    // Johnson's algorithm for two-machine flow shop
    // Split into two groups:
    // - Group 1: jobs where min(U, V) == U (go first)
    // - Group 2: jobs where min(U, V) == V (go last)
    
    vector<pair<int, int>> group1, group2;
    for (int i = 0; i < n; i++) {
        if (ships[i].first <= ships[i].second) {
            group1.push_back(ships[i]);
        } else {
            group2.push_back(ships[i]);
        }
    }
    
    // Sort group1 by U ascending
    sort(group1.begin(), group1.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    });
    
    // Sort group2 by V descending
    sort(group2.begin(), group2.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    
    // Combine: group1 then group2
    vector<pair<int, int>> order;
    for (auto& s : group1) order.push_back(s);
    for (auto& s : group2) order.push_back(s);
    
    // Calculate total time
    long long time1 = 0, time2 = 0;
    for (int i = 0; i < n; i++) {
        int u = order[i].first;
        int v = order[i].second;
        
        time1 += u;
        time2 = max(time2, time1) + v;
    }
    
    cout << time2 << "\n";
    return 0;
}
