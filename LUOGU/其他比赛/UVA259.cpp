#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Edge { int to, cap, rev; };
vector<vector<Edge>> G;
vector<int> level, iter;

void addEdge(int f, int t, int c) {
    G[f].push_back({t, c, (int)G[t].size()});
    G[t].push_back({f, 0, (int)G[f].size()-1});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    vector<int> q; q.push_back(s); level[s] = 0;
    for (int i = 0; i < (int)q.size(); i++) {
        for (auto& e : G[q[i]])
            if (e.cap > 0 && level[e.to] < 0)
                level[e.to] = level[q[i]]+1, q.push_back(e.to);
    }
    return level[t] >= 0;
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < (int)G[v].size(); i++) {
        Edge& e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) { e.cap -= d; G[e.to][e.rev].cap += d; return d; }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(iter.begin(), iter.end(), 0);
        int d;
        while ((d = dfs(s, t, 1e9)) > 0) flow += d;
    }
    return flow;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        int n = 0;
        for (char c : line) n += (c == ' ');
        n++;
        int S = 0, T = n + 27;
        int tot = T + 1;
        G.assign(tot, vector<Edge>());
        level.resize(tot); iter.resize(tot);
        for (int i = 1; i <= n; i++) {
            string l; getline(cin, l);
            addEdge(S, i, l[0]-'0');
            for (int j = 2; l[j] && l[j] != ';'; j++)
                addEdge(i, n+1+(l[j]-'A'), 1);
        }
        for (int i = 0; i < 26; i++) addEdge(n+1+i, T, 1);
        int flow = maxFlow(S, T);
        if (flow == 26) {
            vector<char> ans(n, '_');
            for (int i = 1; i <= n; i++)
                for (auto& e : G[i])
                    if (e.to > n && e.to <= n+26 && e.cap == 0)
                        ans[i-1] = 'A' + (e.to - n - 1);
            for (int i = 0; i < n; i++) cout << ans[i];
            cout << endl;
        } else cout << "!" << endl;
    }
    return 0;
}
