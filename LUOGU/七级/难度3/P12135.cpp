#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 2000005;
int par[MAXN], rnk[MAXN];

int find(int x) {
    return par[x] == x ? x : par[x] = find(par[x]);
}

void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);
    par[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string row[2];
    cin >> row[0] >> row[1];
    int n = row[0].size();

    for (int i = 0; i < 2 * n; i++) par[i] = i, rnk[i] = 0;

    for (int j = 0; j < n; j++) {
        if (row[0][j] == '#' && row[1][j] == '#') unite(j, n + j);
        if (j > 0 && row[0][j] == '#' && row[0][j-1] == '#') unite(j-1, j);
        if (j > 0 && row[1][j] == '#' && row[1][j-1] == '#') unite(n+j-1, n+j);
    }

    vector<int> cmin(2*n, n), cmax(2*n, -1);
    vector<bool> seen(2*n, false);
    vector<int> roots;

    for (int j = 0; j < n; j++) {
        for (int r = 0; r < 2; r++) {
            if (row[r][j] == '#') {
                int root = find(r * n + j);
                if (!seen[root]) {
                    seen[root] = true;
                    roots.push_back(root);
                }
                cmin[root] = min(cmin[root], j);
                cmax[root] = max(cmax[root], j);
            }
        }
    }

    if (roots.size() <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<bool> lr0(2*n, false), lr1(2*n, false);
    vector<bool> rr0(2*n, false), rr1(2*n, false);

    for (int j = 0; j < n; j++) {
        for (int r = 0; r < 2; r++) {
            if (row[r][j] == '#') {
                int root = find(r * n + j);
                if (j == cmin[root]) {
                    if (r == 0) lr0[root] = true;
                    else lr1[root] = true;
                }
                if (j == cmax[root]) {
                    if (r == 0) rr0[root] = true;
                    else rr1[root] = true;
                }
            }
        }
    }

    sort(roots.begin(), roots.end(), [&](int a, int b) {
        return cmin[a] < cmin[b];
    });

    long long ans = 0;
    for (int i = 1; i < (int)roots.size(); i++) {
        int a = roots[i-1], b = roots[i];
        int gap = cmin[b] - cmax[a] - 1;
        bool share = (rr0[a] && lr0[b]) || (rr1[a] && lr1[b]);
        ans += gap + (share ? 0 : 1);
    }

    cout << ans << "\n";
    return 0;
}
