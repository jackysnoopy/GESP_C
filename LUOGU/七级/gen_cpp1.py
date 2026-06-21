import os

cpp_codes = {
    "P10265": """#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    m--;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    int out_cnt = 0, in_cnt = 0;
    for (int j = 0; j < n; j++)
        if (a[m][j]) out_cnt++;
    for (int i = 0; i < n; i++)
        if (a[i][m]) in_cnt++;
    cout << out_cnt << " " << in_cnt << " " << out_cnt + in_cnt << "\n";
    return 0;
}
""",
    "P10287": """#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> g(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        indeg[v]++;
    }
    vector<int> dp(n, 1);
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (a[u] <= a[v])
                dp[v] = max(dp[v], dp[u] + 1);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
""",
    "P10110": """#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        long long cost = 1;
        if (v[x] > v[y]) cost = -(v[x] - v[y]) + 1;
        else cost = (v[y] - v[x]) + 1;
        g[x].push_back({y, cost});
    }
    vector<long long> dist(n, LLONG_MAX);
    dist[a] = 0;
    queue<int> q;
    q.push(a);
    vector<bool> inq(n, false);
    inq[a] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inq[v]) { q.push(v); inq[v] = true; }
            }
        }
    }
    if (dist[b] == LLONG_MAX) cout << "No solution\\n";
    else cout << dist[b] << "\\n";
    return 0;
}
""",
    "P10111": """#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n - 1), c(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    // score[my][opp] = 出 my 对 opp 的得分
    auto score = [&](int round, int my) {
        int opp = c[round];
        if (my == opp) return a[round];
        if ((my + 1) % 3 == opp) return 2 * a[round];
        return 0;
    };
    vector<vector<int>> dp(n, vector<int>(3, INT_MIN));
    for (int j = 0; j < 3; j++) dp[0][j] = score(0, j);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                int cost = (j != k) ? b[i - 1] : 0;
                dp[i][j] = max(dp[i][j], dp[i - 1][k] - cost + score(i, j));
            }
        }
    }
    int ans = max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    cout << ans << "\\n";
    return 0;
}
""",
    "P10378": """#include <iostream>
#include <vector>
using namespace std;

vector<int> parent;
int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}
void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    parent.resize(n);
    for (int i = 0; i < n; i++) parent[i] = i;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        unite(u, v);
    }
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << (find(u) == find(v) ? "Yes\\n" : "No\\n");
    }
    return 0;
}
""",
    "P10379": """#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> board(n, string(m, '.'));
    for (int t = 0; t < k; t++) {
        string shape;
        int col;
        cin >> shape >> col;
        // Simple tetromino shapes
        int r = 0, c = col;
        // Fall down
        while (r + 1 < n && board[r + 1][c] == '.') r++;
        board[r][c] = '#';
    }
    for (int i = 0; i < n; i++)
        cout << board[i] << "\\n";
    return 0;
}
""",
    "P10723": """#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> start(n), target(n);
    for (int i = 0; i < n; i++) cin >> start[i];
    for (int i = 0; i < n; i++) cin >> target[i];
    
    auto flip = [&](vector<string> &b, int r, int c) {
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < m)
                    b[nr][nc] = (b[nr][nc] == '0') ? '1' : '0';
            }
    };
    
    int ans = INT_MAX;
    for (int mask = 0; mask < (1 << m); mask++) {
        vector<string> b = start;
        int cnt = 0;
        for (int j = 0; j < m; j++)
            if (mask & (1 << j)) { flip(b, 0, j); cnt++; }
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m; j++)
                if (b[i-1][j] != target[i-1][j]) { flip(b, i, j); cnt++; }
        bool ok = true;
        for (int j = 0; j < m; j++)
            if (b[n-1][j] != target[n-1][j]) { ok = false; break; }
        if (ok) ans = min(ans, cnt);
    }
    cout << (ans == INT_MAX ? -1 : ans) << "\\n";
    return 0;
}
""",
    "P10724": """#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Prefix product modulo
    vector<long long> pref(n + 1, 1);
    const long long MOD = 1000000007;
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] * a[i] % MOD;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        long long ans = pref[r] * pref[l] % MOD;
        cout << ans << "\\n";
    }
    return 0;
}
""",
    "P11248": """#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    vector<vector<long long>> dp(n, vector<long long>(m));
    dp[0][0] = a[0][0];
    for (int j = 1; j < m; j++) dp[0][j] = dp[0][j-1] + a[0][j];
    for (int i = 1; i < n; i++) dp[i][0] = dp[i-1][0] + a[i][0];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + a[i][j];
    cout << dp[n-1][m-1] << "\\n";
    return 0;
}
""",
    "P11249": """#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];
    vector<pair<int,int>> treasures(k);
    for (int i = 0; i < k; i++) {
        cin >> treasures[i].first >> treasures[i].second;
        treasures[i].first--; treasures[i].second--;
    }
    // BFS for shortest path between all treasure points
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    vector<vector<int>> dist(k, vector<int>(k, 0));
    for (int t = 0; t < k; t++) {
        vector<vector<int>> d(n, vector<int>(m, -1));
        queue<pair<int,int>> q;
        q.push(treasures[t]);
        d[treasures[t].first][treasures[t].second] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto &dr : dirs) {
                int nx = x + dr[0], ny = y + dr[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && d[nx][ny] == -1) {
                    d[nx][ny] = d[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        for (int j = 0; j < k; j++)
            dist[t][j] = d[treasures[j].first][treasures[j].second];
    }
    // DP over subsets
    vector<vector<int>> dp(1 << k, vector<int>(k, 1e9));
    for (int i = 0; i < k; i++) dp[1 << i][i] = 0;
    for (int mask = 0; mask < (1 << k); mask++)
        for (int last = 0; last < k; last++)
            if (dp[mask][last] < 1e9)
                for (int nxt = 0; nxt < k; nxt++)
                    if (!(mask & (1 << nxt)) && dist[last][nxt] >= 0)
                        dp[mask | (1 << nxt)][nxt] = min(dp[mask | (1 << nxt)][nxt], dp[mask][last] + dist[last][nxt]);
    int ans = 1e9;
    for (int i = 0; i < k; i++) ans = min(ans, dp[(1 << k) - 1][i]);
    cout << ans << "\\n";
    return 0;
}
""",
    "P11377": """#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int budget, n;
    cin >> budget >> n;
    vector<int> price(n), atk(n);
    for (int i = 0; i < n; i++)
        cin >> price[i] >> atk[i];
    vector<int> dp(budget + 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = budget; j >= price[i]; j--)
            dp[j] = max(dp[j], dp[j - price[i]] + atk[i]);
    cout << *max_element(dp.begin(), dp.end()) << "\\n";
    return 0;
}
""",
}

for pid, code in cpp_codes.items():
    with open(f"{pid}.cpp", "w") as f:
        f.write(code)
    print(f"✅ {pid}.cpp")
