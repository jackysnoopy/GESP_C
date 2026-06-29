#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> State;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, c;
    ll r;
    int k;
    cin >> n >> m >> c >> r >> k;
    
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll l;
        cin >> u >> v >> l;
        adj[u].push_back(make_pair(v, l));
        adj[v].push_back(make_pair(u, l));
    }
    
    vector<vector<pair<ll, int>>> best(n + 1);
    
    priority_queue<State, vector<State>, greater<State>> pq;
    
    for (int i = 1; i <= c; i++) {
        pq.push(State(0, i, i));
    }
    
    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();
        ll d = get<0>(s);
        int v = get<1>(s);
        int src = get<2>(s);
        
        if ((int)best[v].size() == k && best[v].back().first <= d) {
            continue;
        }
        
        bool found = false;
        for (size_t i = 0; i < best[v].size(); i++) {
            if (best[v][i].second == src && best[v][i].first <= d) {
                found = true;
                break;
            }
        }
        if (found) continue;
        
        best[v].push_back(make_pair(d, src));
        sort(best[v].begin(), best[v].end());
        if ((int)best[v].size() > k) {
            best[v].pop_back();
        }
        
        for (size_t i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i].first;
            ll w = adj[v][i].second;
            pq.push(State(d + w, u, src));
        }
    }
    
    vector<int> result;
    for (int v = c + 1; v <= n; v++) {
        if ((int)best[v].size() >= k && best[v][k - 1].first <= r) {
            result.push_back(v);
        }
    }
    
    cout << result.size() << "\n";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << "\n";
    }
    
    return 0;
}
