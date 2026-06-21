#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cstring>
#include <tuple>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,pair<ll,int>>>> g(n);
    vector<tuple<int,int,ll,int>> edges;
    vector<int> beautyValues;

    for (int i = 0; i < m; i++) {
        int u, v, w, b;
        cin >> u >> v >> w >> b;
        u--; v--;
        g[u].push_back({v, {w, b}});
        g[v].push_back({u, {w, b}});
        edges.push_back(make_tuple(u, v, (ll)w, b));
        beautyValues.push_back(b);
    }

    // 去重并排序景观评分
    sort(beautyValues.begin(), beautyValues.end());
    beautyValues.erase(unique(beautyValues.begin(), beautyValues.end()), beautyValues.end());

    ll ans = INF;

    // 枚举每条边作为"被免除的边"
    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        ll w = get<2>(edges[i]);
        int be = get<3>(edges[i]);

        // Dijkstra：从1出发，只走景观评分 <= be 的边
        vector<ll> d1(n, INF);
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        d1[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            ll d = pq.top().first;
            int cur = pq.top().second;
            pq.pop();
            if (d != d1[cur]) continue;
            for (int j = 0; j < g[cur].size(); j++) {
                int next = g[cur][j].first;
                ll wj = g[cur][j].second.first;
                int bj = g[cur][j].second.second;
                if (bj > be) continue; // 只走景观评分不超过限制的边
                if (d1[cur] + wj < d1[next]) {
                    d1[next] = d1[cur] + wj;
                    pq.push({d1[next], next});
                }
            }
        }

        // Dijkstra：从n出发，只走景观评分 <= be 的边
        vector<ll> dn(n, INF);
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq2;
        dn[n - 1] = 0;
        pq2.push({0, n - 1});

        while (!pq2.empty()) {
            ll d = pq2.top().first;
            int cur = pq2.top().second;
            pq2.pop();
            if (d != dn[cur]) continue;
            for (int j = 0; j < g[cur].size(); j++) {
                int next = g[cur][j].first;
                ll wj = g[cur][j].second.first;
                int bj = g[cur][j].second.second;
                if (bj > be) continue;
                if (dn[cur] + wj < dn[next]) {
                    dn[next] = dn[cur] + wj;
                    pq2.push({dn[next], next});
                }
            }
        }

        // 路径必须包含这条边，并且这条边是景观评分最高的
        if (d1[u] < INF && dn[v] < INF)
            ans = min(ans, d1[u] + dn[v]);
        if (d1[v] < INF && dn[u] < INF)
            ans = min(ans, d1[v] + dn[u]);
    }

    cout << (ans >= INF ? -1 : ans) << "\n";
    return 0;
}
