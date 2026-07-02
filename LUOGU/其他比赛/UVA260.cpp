#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int n;
char g[205][205];
bool vis[205][205];

int dx_e[] = {-1, -1, 0, 0, 1, 1};
int dy_e[] = {-1, 0, -1, 1, -1, 0};
int dx_o[] = {-1, -1, 0, 0, 1, 1};
int dy_o[] = {0, 1, -1, 1, 0, 1};

bool bfs_black() {
    memset(vis, 0, sizeof(vis));
    queue<pair<int,int>> q;
    for (int c = 0; c < n; c++) {
        if (g[0][c] == 'b') {
            q.push({0, c});
            vis[0][c] = true;
        }
    }
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        if (r == n - 1) return true;
        for (int d = 0; d < 6; d++) {
            int nr, nc;
            if (r % 2 == 0) {
                nr = r + dx_e[d];
                nc = c + dy_e[d];
            } else {
                nr = r + dx_o[d];
                nc = c + dy_o[d];
            }
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc] && g[nr][nc] == 'b') {
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return false;
}

bool bfs_white() {
    memset(vis, 0, sizeof(vis));
    queue<pair<int,int>> q;
    for (int r = 0; r < n; r++) {
        if (g[r][0] == 'w') {
            q.push({r, 0});
            vis[r][0] = true;
        }
    }
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        if (c == n - 1) return true;
        for (int d = 0; d < 6; d++) {
            int nr, nc;
            if (r % 2 == 0) {
                nr = r + dx_e[d];
                nc = c + dy_e[d];
            } else {
                nr = r + dx_o[d];
                nc = c + dy_o[d];
            }
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc] && g[nr][nc] == 'w') {
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return false;
}

int main() {
    int caseNo = 0;
    while (cin >> n && n) {
        caseNo++;
        for (int i = 0; i < n; i++) cin >> g[i];
        cout << caseNo << " ";
        if (bfs_black()) cout << "b wins" << endl;
        else cout << "w wins" << endl;
    }
    return 0;
}
