#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000005;

int n;
int w[MAXN];
vector<int> adj[MAXN];

int subMin[MAXN], subCnt[MAXN], par[MAXN], sz[MAXN];
int upMin[MAXN], upCnt[MAXN];
long long ans[MAXN];

void dfs1(int u, int p) {
    par[u] = p;
    sz[u] = 1;
    subMin[u] = w[u];
    subCnt[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (subMin[v] < subMin[u]) {
            subMin[u] = subMin[v];
            subCnt[u] = subCnt[v];
        } else if (subMin[v] == subMin[u]) {
            subCnt[u] += subCnt[v];
        }
    }
}

void dfs2(int u, int p) {
    int deg = (int)adj[u].size();
    if (deg <= 1) {
        ans[u] = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            upMin[v] = w[u];
            upCnt[v] = 1;
            dfs2(v, u);
        }
        return;
    }

    vector<int> children;
    for (int v : adj[u])
        if (v != p) children.push_back(v);

    int numComp = (int)children.size();
    if (p != -1) numComp++;

    if (numComp <= 1) {
        ans[u] = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            upMin[v] = w[u];
            upCnt[v] = 1;
            dfs2(v, u);
        }
        return;
    }

    struct Comp { int m, c; };
    vector<Comp> comps;
    for (int v : children)
        comps.push_back({subMin[v], subCnt[v]});
    if (p != -1)
        comps.push_back({upMin[u], upCnt[u]});

    int k = (int)comps.size();
    int need = 2 * (k - 1);

    vector<int> curE(k, 1);
    int totalE = k;
    int remaining = need - totalE;

    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    for (int i = 0; i < k; i++) {
        long long mc;
        if (curE[i] < comps[i].c)
            mc = comps[i].m;
        else
            mc = comps[i].m + (curE[i] - comps[i].c + 1);
        pq.push({mc, i});
    }

    while (remaining > 0) {
        pair<long long,int> top = pq.top();
        pq.pop();
        int idx = top.second;
        curE[idx]++;
        remaining--;
        long long nextMc;
        if (curE[idx] < comps[idx].c)
            nextMc = comps[idx].m;
        else
            nextMc = comps[idx].m + (curE[idx] - comps[idx].c + 1);
        pq.push({nextMc, idx});
    }

    long long totalCost = 0;
    for (int i = 0; i < k; i++) {
        int e = curE[i];
        int m = comps[i].m;
        int c = comps[i].c;
        totalCost += (long long)e * m;
        if (e > c)
            totalCost += (long long)(e - c) * (e - c + 1) / 2;
    }
    ans[u] = totalCost;

    for (int v : adj[u]) {
        if (v == p) continue;
        int bestMin = w[u];
        int bestCnt = 1;
        if (p != -1) {
            if (upMin[u] < bestMin) {
                bestMin = upMin[u];
                bestCnt = upCnt[u];
            } else if (upMin[u] == bestMin) {
                bestCnt += upCnt[u];
            }
        }
        for (int j = 0; j < (int)children.size(); j++) {
            if (children[j] != v) {
                if (subMin[children[j]] < bestMin) {
                    bestMin = subMin[children[j]];
                    bestCnt = subCnt[children[j]];
                } else if (subMin[children[j]] == bestMin) {
                    bestCnt += subCnt[children[j]];
                }
            }
        }
        upMin[v] = bestMin;
        upCnt[v] = bestCnt;
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    upMin[1] = 2000000001;
    upCnt[1] = 0;
    dfs1(1, -1);
    dfs2(1, -1);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << (i == n ? '\n' : ' ');

    return 0;
}
