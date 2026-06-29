#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Group {
    int s, e, m;
};

bool compareEnd(const Group& a, const Group& b) {
    return a.e < b.e;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, n, c;
    cin >> k >> n >> c;
    
    vector<Group> groups(k);
    for (int i = 0; i < k; i++) {
        cin >> groups[i].s >> groups[i].e >> groups[i].m;
    }
    
    // Sort by end position
    sort(groups.begin(), groups.end(), compareEnd);
    
    // Use a priority queue to track active cows at each stop
    // At each stop, remove cows that have reached their destination
    // Then add new cows if capacity allows
    
    long long total = 0;
    priority_queue<pair<int, int>> active; // (end position, count)
    int current_load = 0;
    
    for (int i = 0; i < k; i++) {
        // Remove cows that have reached their destination
        while (!active.empty() && active.top().first <= groups[i].s) {
            current_load -= active.top().second;
            active.pop();
        }
        
        // Add cows from current group
        int can_add = min(groups[i].m, c - current_load);
        if (can_add > 0) {
            total += can_add;
            current_load += can_add;
            active.push({groups[i].e, can_add});
        }
    }
    
    cout << total << "\n";
    return 0;
}
