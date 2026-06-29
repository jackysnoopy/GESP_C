#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 510;

int n, m;
int h[MAXN][MAXN];
bool vis[MAXN][MAXN];
int cover[MAXN][MAXN];
int maxr[MAXN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int sx, int sy, int id) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;
    cover[sx][sy] = id;
    maxr[id] = max(maxr[id], sx);
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vis[nx][ny]) continue;
            if (h[nx][ny] >= h[x][y]) continue;
            
            vis[nx][ny] = true;
            cover[nx][ny] = id;
            maxr[id] = max(maxr[id], nx);
            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }
    
    memset(vis, false, sizeof(vis));
    memset(cover, 0, sizeof(cover));
    memset(maxr, 0, sizeof(maxr));
    
    int id = 0;
    for (int j = 1; j <= m; j++) {
        if (!vis[1][j]) {
            id++;
            bfs(1, j, id);
        }
    }
    
    bool ok = true;
    for (int j = 1; j <= m; j++) {
        if (cover[n][j] == 0) {
            ok = false;
            break;
        }
    }
    
    if (!ok) {
        int cnt = 0;
        for (int j = 1; j <= m; j++) {
            if (cover[n][j] == 0) cnt++;
        }
        cout << "0\n" << cnt << "\n";
    } else {
        vector<pair<int, int>> intervals;
        for (int i = 1; i <= id; i++) {
            if (maxr[i] == n) {
                int l = m + 1, r = 0;
                for (int j = 1; j <= m; j++) {
                    if (cover[n][j] == i) {
                        l = min(l, j);
                        r = max(r, j);
                    }
                }
                intervals.push_back({l, r});
            }
        }
        
        sort(intervals.begin(), intervals.end());
        
        int ans = 0;
        int cur = 0;
        int idx = 0;
        while (cur < m) {
            int nxt = cur;
            while (idx < (int)intervals.size() && intervals[idx].first <= cur + 1) {
                nxt = max(nxt, intervals[idx].second);
                idx++;
            }
            if (nxt == cur) {
                cout << "0\n" << m - cur << "\n";
                return 0;
            }
            cur = nxt;
            ans++;
        }
        
        cout << "1\n" << ans << "\n";
    }
    
    return 0;
}