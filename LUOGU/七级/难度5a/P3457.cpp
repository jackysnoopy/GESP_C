#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int n, m;
int a[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int x, int y, int h) {
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    
    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                if (a[nx][ny] <= h) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    memset(visited, false, sizeof(visited));
    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && a[i][j] > 0) {
                bfs(i, j, a[i][j]);
                ans++;
            }
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}
