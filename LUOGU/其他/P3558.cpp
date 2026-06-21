#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int n, sx, sy;
char a[301][301];
int dist[301][301];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> sx >> sy;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
    memset(dist, -1, sizeof(dist));
    queue<pair<int,int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (a[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == -1) cout << "# ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
