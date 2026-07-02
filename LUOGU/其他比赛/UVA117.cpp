#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 30;
int adj[MAXN][MAXN];
int degree[MAXN];
int n;

int dijkstra(int s, int t) {
    vector<int> dist(n, INT_MAX);
    vector<bool> vis(n, false);
    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!vis[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] == INT_MAX) break;
        vis[u] = true;
        for (int v = 0; v < n; v++) {
            if (adj[u][v] && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }
    return dist[t];
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        map<string, int> name2id;
        n = 0;
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                adj[i][j] = 0;
        for (int i = 0; i < MAXN; i++) degree[i] = 0;
        
        do {
            string a = line.substr(0, 2);
            string b = line.substr(2, 2);
            int w = line[4] - '0';
            
            if (name2id.find(a) == name2id.end()) name2id[a] = n++;
            if (name2id.find(b) == name2id.end()) name2id[b] = n++;
            
            int u = name2id[a], v = name2id[b];
            adj[u][v] += w;
            adj[v][u] += w;
            degree[u]++;
            degree[v]++;
        } while (getline(cin, line) && !line.empty());
        
        int oddVerts[MAXN], oddCount = 0;
        for (int i = 0; i < n; i++)
            if (degree[i] % 2 == 1) oddVerts[oddCount++] = i;
        
        int totalWeight = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                totalWeight += adj[i][j];
        
        if (oddCount == 0) {
            cout << totalWeight << "\n";
        } else {
            int minExtra = INT_MAX;
            for (int mask = 0; mask < (1 << oddCount); mask++) {
                if (__builtin_popcount(mask) != oddCount / 2) continue;
                vector<int> left, right;
                for (int i = 0; i < oddCount; i++) {
                    if (mask & (1 << i)) left.push_back(oddVerts[i]);
                    else right.push_back(oddVerts[i]);
                }
                int extra = 0;
                for (int i = 0; i < (int)left.size(); i++)
                    extra += dijkstra(left[i], right[i]);
                minExtra = min(minExtra, extra);
            }
            cout << totalWeight + minExtra << "\n";
        }
    }
    return 0;
}
