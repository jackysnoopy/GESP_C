#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;
        
        vector<string> zip(N);
        for (int i = 0; i < N; i++) cin >> zip[i];
        
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // Sort cities by zip code for lexicographically smallest
        vector<int> cityOrder(N);
        for (int i = 0; i < N; i++) cityOrder[i] = i;
        sort(cityOrder.begin(), cityOrder.end(), [&](int a, int b) {
            return zip[a] < zip[b];
        });
        
        // BFS to find visitation order
        vector<bool> visited(N, false);
        vector<int> result;
        
        for (int s : cityOrder) {
            if (visited[s]) continue;
            // BFS from s
            vector<int> queue;
            queue.push_back(s);
            visited[s] = true;
            int head = 0;
            while (head < (int)queue.size()) {
                int u = queue[head++];
                result.push_back(u);
                vector<int> neighbors;
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        neighbors.push_back(v);
                    }
                }
                sort(neighbors.begin(), neighbors.end(), [&](int a, int b) {
                    return zip[a] < zip[b];
                });
                for (int v : neighbors) queue.push_back(v);
            }
        }
        
        cout << "Case #" << t << ": ";
        for (int i = 0; i < N; i++) cout << zip[result[i]];
        cout << "\n";
    }
    
    return 0;
}