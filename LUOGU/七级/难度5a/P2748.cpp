#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    
    // Calculate net change needed for each flower bed
    vector<int> diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = b[i] - a[i];
    }
    
    // Greedy: try to move soil from positive diff to negative diff
    long long cost = 0;
    
    // Create list of (position, diff) for positive and negative diffs
    vector<pair<int, int>> pos, neg;
    for (int i = 0; i < n; i++) {
        if (diff[i] > 0) {
            pos.push_back({i, diff[i]});
        } else if (diff[i] < 0) {
            neg.push_back({i, -diff[i]});
        }
    }
    
    // Match positive and negative diffs
    int i = 0, j = 0;
    while (i < pos.size() && j < neg.size()) {
        int move = min(pos[i].second, neg[j].second);
        int dist = abs(pos[i].first - neg[j].first);
        
        // Option 1: Buy new soil (cost x per unit)
        // Option 2: Remove soil (cost y per unit)
        // Option 3: Move soil (cost z * dist per unit)
        
        long long move_cost = (long long)move * z * dist;
        long long buy_cost = (long long)move * x;
        long long remove_cost = (long long)move * y;
        
        // Choose the cheapest option
        cost += min(move_cost, min(buy_cost, remove_cost));
        
        pos[i].second -= move;
        neg[j].second -= move;
        
        if (pos[i].second == 0) i++;
        if (neg[j].second == 0) j++;
    }
    
    cout << cost << "\n";
    return 0;
}
