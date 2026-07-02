#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int r, c;
        cin >> r >> c;
        char grid[31][81];
        for (int i = 0; i < r; i++) cin >> grid[i];
        int sx, sy, tx, ty, lx, ly;
        cin >> sx >> sy >> tx >> ty >> lx >> ly;
        int dist[31][81];
        memset(dist, -1, sizeof(dist));
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        dist[lx][ly] = 0;
        pair<int,int> q[901];
        int front = 0, back = 0;
        q[back++] = {lx, ly};
        while (front < back) {
            int x = q[front].first, y = q[front].second; front++;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] == '.' && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q[back++] = {nx, ny};
                }
            }
        }
        if (dist[tx][ty] == -1) {
            cout << "No route" << endl;
        } else {
            int mx = tx, my = ty;
            while (mx != lx || my != ly) {
                int best = dist[mx][my];
                int nmx = mx, nmy = my;
                for (int d = 0; d < 4; d++) {
                    int nx = mx + dx[d], ny = my + dy[d];
                    if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] == '.' && dist[nx][ny] != -1 && dist[nx][ny] < best) {
                        best = dist[nx][ny];
                        nmx = nx;
                        nmy = ny;
                    }
                }
                mx = nmx;
                my = nmy;
            }
            cout << mx << " " << my << endl;
        }
    }
    return 0;
}
