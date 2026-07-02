#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int MAXN = 200005;

int n, m;
vector<int> adj[MAXN];
int vis[MAXN];
int order[MAXN];
int pos[MAXN];
int cnt;
bool isChordal;

void mcs() {
    memset(vis, 0, sizeof(vis));
    vector<int> label(n + 1, 0);
    vector<vector<int>> bucket(n + 1);
    
    cnt = n;
    for (int i = n; i >= 1; i--) {
        // Find unvisited vertex with maximum label
        int u = -1;
        for (int j = n; j >= 0; j--) {
            if (!bucket[j].empty()) {
                while (!bucket[j].empty() && vis[bucket[j].back()]) {
                    bucket[j].pop_back();
                }
                if (!bucket[j].empty()) {
                    u = bucket[j].back();
                    bucket[j].pop_back();
                    break;
                }
            }
        }
        
        if (u == -1) {
            // Find any unvisited vertex
            for (int j = 1; j <= n; j++) {
                if (!vis[j]) {
                    u = j;
                    break;
                }
            }
        }
        
        vis[u] = 1;
        order[cnt] = u;
        pos[u] = cnt;
        cnt--;
        
        for (int v : adj[u]) {
            if (!vis[v]) {
                label[v]++;
                bucket[label[v]].push_back(v);
            }
        }
    }
}

bool checkChordal() {
    // Check if the order is a perfect elimination ordering
    vector<set<int>> adjSet(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int v : adj[i]) {
            adjSet[i].insert(v);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        int u = order[i];
        // Find later neighbors
        vector<int> laterNeighbors;
        for (int v : adj[u]) {
            if (pos[v] > pos[u]) {
                laterNeighbors.push_back(v);
            }
        }
        
        if (laterNeighbors.empty()) continue;
        
        // The first later neighbor should be adjacent to all others
        int first = laterNeighbors[0];
        for (int j = 1; j < (int)laterNeighbors.size(); j++) {
            if (adjSet[first].find(laterNeighbors[j]) == adjSet[first].end()) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m;
        
        for (int i = 1; i <= n; i++) adj[i].clear();
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        mcs();
        
        if (!checkChordal()) {
            cout << "No\n";
            continue;
        }
        
        cout << "Yes\n";
        for (int i = 1; i <= n; i++) {
            cout << order[i] << (i < n ? " " : "\n");
        }
        
        // Find max clique size (coloring number)
        vector<int> color(n + 1, 0);
        int maxColor = 0;
        for (int i = 1; i <= n; i++) {
            int u = order[i];
            set<int> usedColors;
            for (int v : adj[u]) {
                if (pos[v] < pos[u] && color[v] > 0) {
                    usedColors.insert(color[v]);
                }
            }
            int c = 1;
            while (usedColors.count(c)) c++;
            color[u] = c;
            maxColor = max(maxColor, c);
        }
        
        // For chordal graphs: max clique = coloring number = max independent set complement
        cout << maxColor << " " << maxColor << " " << (n - maxColor + 1) << "\n";
    }
    
    return 0;
}
