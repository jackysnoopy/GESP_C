#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 22;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

char grid[MAXN][MAXN];
int dist[MAXN][MAXN][4];
int R, C;

struct State {
    int x, y, dir;
};

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, -1, sizeof(dist));
    queue<State> q;
    for (int d = 0; d < 4; d++) {
        dist[sx][sy][d] = 0;
        q.push({sx, sy, d});
    }
    while (!q.empty()) {
        State s = q.front(); q.pop();
        if (s.x == ex && s.y == ey) return dist[s.x][s.y][s.dir];
        for (int d = 0; d < 4; d++) {
            int nx = s.x + dx[d];
            int ny = s.y + dy[d];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            if (grid[nx][ny] == '#') continue;
            int cost = (d == s.dir) ? 0 : 1;
            int nd = dist[s.x][s.y][s.dir] + cost;
            if (dist[nx][ny][d] == -1 || nd < dist[nx][ny][d]) {
                dist[nx][ny][d] = nd;
                q.push({nx, ny, d});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> R >> C && R && C) {
        for (int i = 0; i < R; i++) cin >> grid[i];
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        sx--; sy--; ex--; ey--;
        int ans = bfs(sx, sy, ex, ey);
        cout << ans << "\n";
    }
    return 0;
}
