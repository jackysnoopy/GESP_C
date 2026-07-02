#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct State {
    int x, y, dir, color;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int grid[5][5];
    int sx, sy, ex, ey;

    while (cin >> sx >> sy >> ex >> ey) {
        sx--; sy--; ex--; ey--;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                cin >> grid[i][j];

        if (sx == ex && sy == ey) {
            cout << "0\n";
            continue;
        }

        int dist[5][5][4][5];
        memset(dist, -1, sizeof(dist));

        queue<State> q;
        q.push({sx, sy, 0, 0});
        dist[sx][sy][0][0] = 0;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        int ans = -1;
        while (!q.empty() && ans < 0) {
            State s = q.front(); q.pop();
            int d = dist[s.x][s.y][s.dir][s.color];

            for (int i = 0; i < 3; i++) {
                int ndir = (s.dir + (i == 0 ? 3 : i == 2 ? 1 : 0)) % 4;
                int nx = s.x + dx[ndir];
                int ny = s.y + dy[ndir];
                int ncolor = (s.color + 1) % 5;
                if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
                if (grid[nx][ny] == 0) continue;
                if (i == 1) {
                    if (dist[nx][ny][ndir][ncolor] >= 0) continue;
                    dist[nx][ny][ndir][ncolor] = d + 1;
                    if (nx == ex && ny == ey) { ans = d + 1; break; }
                    q.push({nx, ny, ndir, ncolor});
                } else {
                    int nddir = s.dir;
                    if (dist[s.x][s.y][nddir][s.color] >= 0) continue;
                    dist[s.x][s.y][nddir][s.color] = d + 1;
                    q.push({s.x, s.y, nddir, s.color});
                    State ns = {s.x, s.y, nddir, s.color};
                    s.dir = ndir;
                }
            }
        }

        if (ans < 0) cout << "-1\n";
        else cout << ans << "\n";
    }
    return 0;
}
