#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;
const int MAXN = 105;
int n, m, k;
vector<int> adj[MAXN];
bool edge[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m >> k;
        
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            for (int j = 1; j <= n; j++) {
                edge[i][j] = false;
            }
        }
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            edge[u][v] = edge[v][u] = true;
        }
        
        // Simple DP approach for small n
        vector<int> dp(1 << n, 0);
        dp[0] = 1;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == 0) continue;
            
            // Try to add next vertex
            int next = -1;
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    next = i;
                    break;
                }
            }
            
            if (next == -1) continue;
            
            // Check if can add without conflict
            bool can_add = true;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    if (edge[i + 1][next + 1]) {
                        can_add = false;
                        break;
                    }
                }
            }
            
            if (can_add) {
                dp[mask | (1 << next)] = (dp[mask | (1 << next)] + dp[mask]) % MOD;
            }
            
            // Don't add this vertex
            dp[mask | (1 << next)] = (dp[mask | (1 << next)] + dp[mask]) % MOD;
        }
        
        // Count independent sets of size n-k
        long long ans = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == n - k) {
                ans = (ans + dp[mask]) % MOD;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}