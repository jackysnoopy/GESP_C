#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];
    vector<vector<int>> vis(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '#') vis[i][j] = 1;
    string result = "";
    int si = -1, sj = -1;
    char best = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!vis[i][j] && grid[i][j] > best) {
                best = grid[i][j]; si = i; sj = j;
            }
    if (best == 0) { cout << "\n"; return 0; }
    int di[] = {-1,1,0,0};
    int dj[] = {0,0,-1,1};
    int ci = si, cj = sj;
    while (true) {
        result += grid[ci][cj];
        vis[ci][cj] = 1;
        char nb = 0;
        int ni = -1, nj = -1;
        for (int d = 0; d < 4; d++) {
            int ti = ci + di[d], tj = cj + dj[d];
            if (ti >= 0 && ti < n && tj >= 0 && tj < m && !vis[ti][tj] && grid[ti][tj] > nb) {
                nb = grid[ti][tj]; ni = ti; nj = tj;
            }
        }
        if (nb == 0) break;
        ci = ni; cj = nj;
    }
    cout << result << "\n";
    return 0;
}
