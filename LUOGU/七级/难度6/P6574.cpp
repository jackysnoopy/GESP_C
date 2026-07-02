#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int n, d;
int ans = 0;

multiset<int> dfs(int u, int fa) {
    multiset<int> s;
    s.insert(0);
    
    for (int v : adj[u]) {
        if (v == fa) continue;
        auto cs = dfs(v, u);
        for (int x : cs) s.insert(x + 1);
    }
    
    while (s.size() > 1) {
        auto it = s.end();
        --it;
        int mx = *it;
        s.erase(it);
        
        auto lb = s.lower_bound(d - mx);
        if (lb != s.end()) {
            s.erase(lb);
            ans++;
        } else {
            s.insert(mx);
            break;
        }
    }
    
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> d;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    
    dfs(0, -1);
    cout << ans << "\n";
    return 0;
}
