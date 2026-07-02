#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int l[MAXN], r[MAXN];
bool special[MAXN];
int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> q;
    
    string lr;
    cin >> lr;
    
    string spec;
    cin >> spec;
    
    // Parse intervals from LR string
    vector<int> stack;
    int idx = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (lr[i] == 'L') {
            stack.push_back(idx);
            l[idx] = i + 1;
            idx++;
        } else {
            int pos = stack.back();
            stack.pop_back();
            r[pos] = i + 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        special[i] = (spec[i] == '1');
    }
    
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        
        // Simple BFS to find shortest path
        vector<int> dist(n, -1);
        dist[a] = 0;
        
        vector<int> queue;
        queue.push_back(a);
        
        int head = 0;
        while (head < queue.size()) {
            int u = queue[head++];
            
            // Check adjacent tractors
            for (int v = 0; v < n; v++) {
                if (dist[v] == -1 && !(r[u] < l[v] || r[v] < l[u])) {
                    dist[v] = dist[u] + 1;
                    queue.push_back(v);
                }
            }
        }
        
        int shortest = dist[b];
        
        // Count special tractors on shortest paths
        int special_count = 0;
        for (int v = 0; v < n; v++) {
            if (special[v] && dist[v] <= shortest) {
                // Check if v is on some shortest path
                if (dist[v] + dist[v] <= shortest) {
                    special_count++;
                }
            }
        }
        
        cout << shortest << " " << special_count << "\n";
    }
    
    return 0;
}