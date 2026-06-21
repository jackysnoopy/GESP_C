#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int s;
        cin >> s;
        vector<int> stops(s);
        for (int j = 0; j < s; j++) cin >> stops[j];
        set<int> stopSet(stops.begin(), stops.end());
        for (int j = stops[0]; j <= stops[s - 1]; j++) {
            if (stopSet.count(j) == 0) {
                for (int st : stops) {
                    adj[j].push_back(st);
                    indeg[st]++;
                }
            }
        }
    }
    
    queue<int> q;
    vector<int> level(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            level[v] = max(level[v], level[u] + 1);
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, level[i]);
    cout << ans << "\n";
    return 0;
}
