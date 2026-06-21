#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000006;
const long long MOD = 1e9 + 7;

int fa[MAXN], sz[MAXN];

int find(int x) {
    while (fa[x] != x) { fa[x] = fa[fa[x]]; x = fa[x]; }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
    
    struct Edge { int u, v; long long w; };
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    
    int need = n - m - 1;
    vector<long long> new_edges;
    if (need > 0) {
        new_edges.resize(need);
        for (int i = 0; i < need; i++) cin >> new_edges[i];
    }
    
    // 已有边按权值排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    
    // 新边按权值排序
    sort(new_edges.begin(), new_edges.end());
    
    // 合并所有边（已有+新），按权值排序
    // 新边在Kruskal中端点可选，总是可以加入
    // 策略：已有边优先（因为端点固定），新边在后
    
    // 收集连通块
    // 先处理已有边
    vector<pair<long long, int>> blocks; // (size, root)
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            if (sz[fu] < sz[fv]) swap(fu, fv);
            fa[fv] = fu; sz[fu] += sz[fv];
        }
    }
    
    // 收集所有连通块
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            blocks.push_back({sz[i], i});
        }
    }
    
    // 新边权值从小到大，连接两个最大的连通块
    // 使用大根堆
    priority_queue<pair<long long, int>> pq;
    for (auto& b : blocks) {
        pq.push(b);
    }
    
    // 构建MST边列表，用于后续DFS
    struct MSTEdge { int to; long long w; };
    vector<vector<MSTEdge>> tree(n + 1);
    
    // 将已有边加入树
    for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            tree[e.u].push_back({e.v, e.w});
            tree[e.v].push_back({e.u, e.w});
            if (sz[fu] < sz[fv]) swap(fu, fv);
            fa[fv] = fu; sz[fu] += sz[fv];
        }
    }
    
    // 新边权值从小到大，连接两个最大的连通块
    // 重新收集连通块
    for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
    for (auto& e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            if (sz[fu] < sz[fv]) swap(fu, fv);
            fa[fv] = fu; sz[fu] += sz[fv];
        }
    }
    
    // 收集连通块到优先队列
    priority_queue<pair<long long, int>> pq2;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            pq2.push({sz[i], i});
        }
    }
    
    for (long long w : new_edges) {
        if (pq2.size() < 2) break;
        auto p1 = pq2.top(); pq2.pop();
        auto p2 = pq2.top(); pq2.pop();
        
        // 在树中加入这条边（连接两个连通块的代表节点）
        tree[p1.second].push_back({p2.second, w});
        tree[p2.second].push_back({p1.second, w});
        
        // 合并连通块
        int r1 = p1.second, r2 = p2.second;
        long long nsz = p1.first + p2.first;
        // 需要更新fa和sz
        if (sz[r1] < sz[r2]) swap(r1, r2);
        fa[r2] = r1; sz[r1] += sz[r2];
        
        pq2.push({nsz, r1});
    }
    
    // DFS计算每条边的贡献
    long long ans = 0;
    vector<int> subtree(n + 1, 0);
    vector<bool> vis(n + 1, false);
    
    // 从任意节点开始DFS
    function<void(int, int)> dfs = [&](int u, int parent) {
        vis[u] = true;
        subtree[u] = 1;
        for (auto& e : tree[u]) {
            if (e.to == parent) continue;
            dfs(e.to, u);
            subtree[u] += subtree[e.to];
            // 边(u, e.to)的贡献
            long long s1 = subtree[e.to];
            long long s2 = n - s1;
            ans = (ans + (e.w % MOD) * (s1 % MOD) % MOD * (s2 % MOD)) % MOD;
        }
    };
    
    dfs(1, -1);
    
    cout << ans << endl;
    return 0;
}
