#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// 最小费用最大流（带势函数的 Dijkstra，支持负费用边）
struct MCMF {
    struct Edge { int to, rev; long long cap, cost; };
    vector<vector<Edge>> g;
    int n;
    MCMF(int n): g(n), n(n) {}
    void addEdge(int from, int to, long long cap, long long cost) {
        g[from].push_back({to, (int)g[to].size(), cap, cost});
        g[to].push_back({from, (int)g[from].size() - 1, 0, -cost});
    }
    // 用 SPFA 初始化势（含负费用边）
    void initPot(int s, vector<long long> &h) {
        fill(h.begin(), h.end(), LLONG_MAX);
        h[s] = 0;
        vector<int> inq(n, 0); queue<int> q; q.push(s); inq[s] = 1;
        while (!q.empty()) {
            int v = q.front(); q.pop(); inq[v] = 0;
            for (const Edge &e : g[v])
                if (e.cap > 0 && h[v] != LLONG_MAX && h[e.to] > h[v] + e.cost) {
                    h[e.to] = h[v] + e.cost;
                    if (!inq[e.to]) { q.push(e.to); inq[e.to] = 1; }
                }
        }
    }
    pair<long long,long long> flow(int s, int t) {
        long long totalFlow = 0, totalCost = 0;
        vector<long long> h(n, LLONG_MAX);
        initPot(s, h);
        for (int i = 0; i < n; i++) if (h[i] == LLONG_MAX) h[i] = 0;
        while (true) {
            vector<long long> dist(n, LLONG_MAX);
            vector<int> prevV(n, -1), prevE(n, -1);
            dist[s] = 0;
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto pr = pq.top(); pq.pop();
                int v = pr.second;
                if (pr.first > dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    const Edge &e = g[v][i];
                    if (e.cap > 0 && h[v] != LLONG_MAX && h[e.to] != LLONG_MAX) {
                        long long nd = dist[v] + e.cost + h[v] - h[e.to];
                        if (nd < dist[e.to]) {
                            dist[e.to] = nd; prevV[e.to] = v; prevE[e.to] = i;
                            pq.push({nd, e.to});
                        }
                    }
                }
            }
            if (dist[t] == LLONG_MAX) break;
            for (int v = 0; v < n; v++)
                if (dist[v] < LLONG_MAX) h[v] += dist[v];
            long long add = LLONG_MAX;
            for (int v = t; v != s; v = prevV[v])
                add = min(add, g[prevV[v]][prevE[v]].cap);
            for (int v = t; v != s; v = prevV[v]) {
                Edge &e = g[prevV[v]][prevE[v]];
                e.cap -= add; g[v][e.rev].cap += add;
            }
            totalFlow += add; totalCost += add * h[t];
        }
        return {totalFlow, totalCost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int D, N1, N2;
    long long C1, C2, Tc;
    cin >> D >> N1 >> N2 >> C1 >> C2 >> Tc;
    vector<long long> T(D + 1);
    for (int i = 1; i <= D; i++) cin >> T[i];

    // 下界费用流建模（拆点）：
    //   in[i]/out[i] 分别为第 i 天"可用池"/"用完待处理"。
    //   强制 in[i]->out[i] 流量 = T[i]（下界=上界=T[i]，用超源超汇转化）。
    //   SS->out[i] cap T[i] : 强制每天用 T[i] 个
    //   in[i]->ST cap T[i]  : 强制每天消耗 T[i] 个
    //   S->in[i]  INF Tc    : 新购
    //   out[i]->E INF 0     : 丢弃
    //   E->S     INF 0      : 丢弃的玩具回流为"购买预算"（费用计在 S->in）
    //   out[i]->in[i+N1] INF C1 : 快消毒（用完 i 天后 N1 晚，第 i+N1 天可用）
    //   out[i]->in[i+N2] INF C2 : 慢消毒
    //   in[i]->in[i+1] INF 0    : 未用完的玩具留存到次日
    const long long INF = 1e15;
    int SS = 0, ST = 1, S = 2, E = 3;
    int nodes = 4 + 2 * D + 2;
    MCMF mcmf(nodes);
    auto IN = [&](int i){ return 4 + 2 * (i - 1); };
    auto OUT = [&](int i){ return 5 + 2 * (i - 1); };
    for (int i = 1; i <= D; i++) {
        mcmf.addEdge(SS, OUT(i), T[i], 0);    // 强制使用
        mcmf.addEdge(IN(i), ST, T[i], 0);     // 强制消耗
        mcmf.addEdge(S, IN(i), INF, Tc);      // 新购
        mcmf.addEdge(OUT(i), E, INF, 0);      // 丢弃
        if (i + 1 <= D) mcmf.addEdge(IN(i), IN(i + 1), INF, 0);          // 留存
        if (i + N1 <= D) mcmf.addEdge(OUT(i), IN(i + N1), INF, C1);      // 快消毒
        if (i + N2 <= D) mcmf.addEdge(OUT(i), IN(i + N2), INF, C2);      // 慢消毒
    }
    mcmf.addEdge(E, S, INF, 0);               // 丢弃回流为购买预算
    auto res = mcmf.flow(SS, ST);
    cout << res.second << "\n";
    return 0;
}
