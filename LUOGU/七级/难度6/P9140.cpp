#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> v(n), c(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> c[i];
    // 选价值密度最高的物品作基底（平手取体积较大者，减少模数规模并稳定）
    int best = 0;
    for (int i = 1; i < n; i++) {
        // 交叉乘法比较密度 c[i]/v[i] 与 c[best]/v[best]，平手取体积较大者
        if (c[i] * v[best] > c[best] * v[i]) best = i;
        else if (c[i] * v[best] == c[best] * v[i] && v[i] > v[best]) best = i;
    }
    long long vb = v[best], cb = c[best];
    vector<long long> ov, oc;
    for (int i = 0; i < n; i++)
        if (i != best) { ov.push_back(v[i]); oc.push_back(c[i]); }

    // 同余最短路: dist[r] = 用其余物品凑到余数 r (mod vb) 的最小体积
    const long long INF = LLONG_MAX;
    int M = (int)vb;
    vector<long long> dist(M, INF);
    vector<long long> val(M, 0);
    dist[0] = 0;
    // 用 Dijkstra (边权 = 体积 >=1, 非负)
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto pr = pq.top(); pq.pop();
        long long d = pr.first; int u = pr.second;
        if (d > dist[u]) continue;
        for (int j = 0; j < (int)ov.size(); j++) {
            int to = (int)(((long long)u + ov[j]) % M);
            long long nd = d + ov[j];
            if (nd < dist[to]) {
                dist[to] = nd;
                val[to] = val[u] + oc[j];
                pq.push({nd, to});
            }
        }
    }
    // 处理询问
    while (q--) {
        long long V;
        cin >> V;
        int r = (int)(V % M);
        if (dist[r] > V) {
            cout << -1 << "\n";
        } else {
            long long ans = val[r] + (V - dist[r]) / vb * cb;
            cout << ans << "\n";
        }
    }
    return 0;
}
