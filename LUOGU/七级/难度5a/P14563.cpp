#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, n, q, k, t;
    cin >> c >> n >> q >> k >> t;
    
    string s;
    cin >> s;
    
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        
        vector<int> dist(n + 1, -1);
        vector<int> steps(n + 1, 0);
        queue<int> que;
        
        dist[a] = 0;
        que.push(a);
        
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            
            for (int v = max(1, u - k); v <= min(n, u + k); v++) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    steps[v] = steps[u] + (s[v - 1] == '0' ? 1 : 0);
                    que.push(v);
                }
            }
        }
        
        if (t == 0) {
            cout << steps[b] << "\n";
        } else {
            cout << steps[b] << " " << dist[b] << "\n";
        }
    }
    
    return 0;
}