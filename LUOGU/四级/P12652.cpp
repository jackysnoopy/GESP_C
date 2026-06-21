#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> par(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> par[i];
    
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    
    vector<set<pair<int,int>>> children(n + 1);
    for (int i = 2; i <= n; i++) {
        children[par[i]].insert({A[i], i});
    }
    
    for (int op = 0; op < n; op++) {
        cout << A[1] << "\n";
        
        // Find special path
        vector<int> path;
        int cur = 1;
        path.push_back(cur);
        while (!children[cur].empty()) {
            cur = children[cur].begin()->second;
            path.push_back(cur);
        }
        
        int k = path.size();
        vector<int> oldW(k);
        for (int i = 0; i < k; i++) oldW[i] = A[path[i]];
        
        // Apply shift: A[path[i]] = oldW[(i+1) % k]
        for (int i = 0; i < k; i++) {
            A[path[i]] = oldW[(i + 1) % k];
        }
        
        // Remove leaf from its parent's children
        if (k >= 2) {
            children[path[k-2]].erase({oldW[k-1], path[k-1]});
        }
        
        // Update children sets for non-leaf path nodes (i = 1 to k-2)
        for (int i = 1; i <= k - 2; i++) {
            int node = path[i];
            int p = path[i - 1];
            children[p].erase({oldW[i], node});
            children[p].insert({A[node], node});
        }
    }
    
    return 0;
}
