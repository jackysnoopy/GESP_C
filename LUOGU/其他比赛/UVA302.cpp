#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXV = 1005;
const int MAXE = 2005;

struct Edge {
    int to, id;
    bool used;
};

vector<Edge> adj[MAXV];
vector<int> circuit;
int deg[MAXV];

void dfs(int u) {
    for (auto& e : adj[u]) {
        if (!e.used) {
            e.used = true;
            // 标记反向边
            for (auto& re : adj[e.to]) {
                if (re.to == u && re.id == e.id && !re.used) {
                    re.used = true;
                    break;
                }
            }
            dfs(e.to);
            circuit.push_back(e.id);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int u, v, id;
    bool first = true;
    while (cin >> u >> v) {
        if (u == 0 && v == 0) break;
        // 初始化
        for (int i = 0; i < MAXV; i++) adj[i].clear();
        memset(deg, 0, sizeof(deg));
        int maxV = 0;
        do {
            cin >> id;
            adj[u].push_back({v, id, false});
            adj[v].push_back({u, id, false});
            deg[u]++;
            deg[v]++;
            maxV = max(maxV, max(u, v));
            cin >> u >> v;
        } while (u != 0 || v != 0);

        // 找起始点（度数为奇数的点，或最小编号的点）
        int start = 1;
        for (int i = 1; i <= maxV; i++) {
            if (deg[i] % 2 == 1) {
                start = i;
                break;
            }
        }

        circuit.clear();
        dfs(start);

        if (!first) cout << "\n";
        first = false;

        // 逆序输出（Hierholzer算法得到的是逆序回路）
        for (int i = (int)circuit.size() - 1; i >= 0; i--) {
            cout << circuit[i];
            if (i > 0) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
