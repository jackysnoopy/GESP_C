#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 52;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN][4];
int R, C;

struct State {
    int x, y, dir;
};

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(int sx, int sy, int sd, int ex, int ey) {
    memset(dist, -1, sizeof(dist));
    queue<State> q;
    dist[sx][sy][sd] = 0;
    q.push({sx, sy, sd});
    while (!q.empty()) {
        State s = q.front(); q.pop();
        if (s.x == ex && s.y == ey) return dist[s.x][s.y][s.dir];
        // Turn left
        int nd = (s.dir + 3) % 4;
        if (dist[s.x][s.y][nd] == -1) {
            dist[s.x][s.y][nd] = dist[s.x][s.y][s.dir] + 1;
            q.push({s.x, s.y, nd});
        }
        // Turn right
        nd = (s.dir + 1) % 4;
        if (dist[s.x][s.y][nd] == -1) {
            dist[s.x][s.y][nd] = dist[s.x][s.y][s.dir] + 1;
            q.push({s.x, s.y, nd});
        }
        // Move forward 1-3 steps
        for (int step = 1; step <= 3; step++) {
            int nx = s.x + dx[s.dir] * step;
            int ny = s.y + dy[s.dir] * step;
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) break;
            if (grid[nx][ny] == '1') break;
            if (dist[nx][ny][s.dir] == -1) {
                dist[nx][ny][s.dir] = dist[s.x][s.y][s.dir] + 1;
                q.push({nx, ny, s.dir});
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
        int sx, sy, sd, ex, ey;
        cin >> sx >> sy >> sd >> ex >> ey;
        sx--; sy--; ex--; ey--;
        sd--;
        int ans = bfs(sx, sy, sd, ex, ey);
        if (ans == -1) cout << "-1\n";
        else cout << ans << "\n";
    }
    return 0;
}
