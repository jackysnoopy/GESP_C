#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;

int n;
int a[MAXN];
int state[MAXN];
int dp[MAXN][2];
vector<int> cycle;

void solve_tree(int u) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    
    for (int v = 1; v <= n; v++) {
        if (a[v] == u && state[v] == 2) {
            solve_tree(v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    int ans = 0;
    
    for (int i = 1; i <= n; i++) {
        if (state[i] != 0) continue;
        
        int u = i;
        while (state[u] == 0) {
            state[u] = 1;
            u = a[u];
        }
        
        if (state[u] == 2) continue;
        
        cycle.clear();
        int v = u;
        do {
            cycle.push_back(v);
            state[v] = 2;
            v = a[v];
        } while (v != u);
        
        int cycle_len = cycle.size();
        
        if (cycle_len == 1) {
            int node = cycle[0];
            solve_tree(node);
            ans += max(dp[node][0], dp[node][1]);
        } else {
            int dp0 = 0, dp1 = 1;
            for (int j = 1; j < cycle_len; j++) {
                int node = cycle[j];
                solve_tree(node);
                int new_dp0 = dp0 + max(dp[node][0], dp[node][1]);
                int new_dp1 = dp1 + dp[node][0];
                dp0 = new_dp0;
                dp1 = new_dp1;
            }
            
            int node = cycle[0];
            solve_tree(node);
            int res1 = dp0 + dp[node][0];
            
            dp0 = 0;
            dp1 = 1;
            for (int j = 1; j < cycle_len; j++) {
                int node = cycle[j];
                int new_dp0 = dp0 + max(dp[node][0], dp[node][1]);
                int new_dp1 = dp1 + dp[node][0];
                dp0 = new_dp0;
                dp1 = new_dp1;
            }
            int res2 = dp1;
            
            ans += max(res1, res2);
        }
    }
    
    cout << ans << "\n";
    return 0;
}
