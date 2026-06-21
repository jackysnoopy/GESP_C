#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int grid[1002][1002];
int dist[1002][1002];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x0, y0;
    cin >> n >> x0 >> y0;
    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        grid[x][y] = 1;
    }
    memset(dist, -1, sizeof(dist));
    queue<pair<int,int>> q;
    dist[x0][y0] = 0;
    q.push(make_pair(x0, y0));
    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = cx + dx[d], ny = cy + dy[d];
            if (nx < 0 || nx > 1000 || ny < 0 || ny > 1000) continue;
            if (grid[nx][ny] == 1) continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[cx][cy];
            q.push(make_pair(nx, ny));
        }
    }
    cout << dist[0][0] << "\n";
    return 0;
}
