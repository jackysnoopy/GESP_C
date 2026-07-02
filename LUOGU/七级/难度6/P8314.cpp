#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 200005;
vector<pair<int, int>> adj[MAXN];
int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }
    
    int low = 0, high = 1e9;
    
    while (low < high) {
        int mid = (low + high) / 2;
        
        int centers = 0;
        vector<bool> covered(n + 1, false);
        
        for (int i = 1; i <= n; i++) {
            if (!covered[i]) {
                centers++;
                queue<pair<int, int>> q;
                q.push(make_pair(i, 0));
                covered[i] = true;
                
                while (!q.empty()) {
                    int u = q.front().first;
                    int dist = q.front().second;
                    q.pop();
                    
                    if (dist >= mid) continue;
                    
                    for (size_t j = 0; j < adj[u].size(); j++) {
                        int v = adj[u][j].first;
                        int w = adj[u][j].second;
                        if (!covered[v]) {
                            covered[v] = true;
                            q.push(make_pair(v, dist + w));
                        }
                    }
                }
            }
        }
        
        if (centers <= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    cout << low << endl;
    
    vector<int> centers;
    vector<bool> covered(n + 1, false);
    
    for (int i = 1; i <= n && (int)centers.size() < k; i++) {
        if (!covered[i]) {
            centers.push_back(i);
            queue<pair<int, int>> q;
            q.push(make_pair(i, 0));
            covered[i] = true;
            
            while (!q.empty()) {
                int u = q.front().first;
                int dist = q.front().second;
                q.pop();
                
                if (dist >= low) continue;
                
                for (size_t j = 0; j < adj[u].size(); j++) {
                    int v = adj[u][j].first;
                    int w = adj[u][j].second;
                    if (!covered[v]) {
                        covered[v] = true;
                        q.push(make_pair(v, dist + w));
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < (int)centers.size(); i++) {
        cout << centers[i] << (i + 1 == (int)centers.size() ? "\n" : " ");
    }
    
    return 0;
}