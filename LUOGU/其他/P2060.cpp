#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int dist[401][401];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int xp, yp, xs, ys;
    cin >> xp >> yp >> xs >> ys;
    int dx[] = {1,2,1,2,-1,-2,-1,-2};
    int dy[] = {2,1,-2,-1,2,1,-2,-1};
    memset(dist, -1, sizeof(dist));
    queue<pair<int,int>> q;
    q.push({xp+200, yp+200});
    dist[xp+200][yp+200] = 0;
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if (x == xs+200 && y == ys+200) break;
        for (int d = 0; d < 8; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if (nx>=0 && nx<=400 && ny>=0 && ny<=400 && dist[nx][ny]==-1) {
                dist[nx][ny] = dist[x][y]+1;
                q.push({nx, ny});
            }
        }
    }
    cout << dist[xs+200][ys+200] << endl;
    return 0;
}