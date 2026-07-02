#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m;
vector<string> grid;
vector<vector<int>> dist;

struct State {
    int x, y, portals;
};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    grid.resize(n);
    dist.assign(n, vector<int>(m, -1));
    
    int sx, sy, fx, fy;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'C') {
                sx = i;
                sy = j;
            } else if (grid[i][j] == 'F') {
                fx = i;
                fy = j;
            }
        }
    }
    
    queue<State> q;
    q.push({sx, sy, 0});
    dist[sx][sy] = 0;
    
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        
        if (cur.x == fx && cur.y == fy) {
            cout << dist[fx][fy] << endl;
            return 0;
        }
        
        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];
            if (isValid(nx, ny) && grid[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                q.push({nx, ny, cur.portals});
            }
        }
    }
    
    cout << "nemoguce" << endl;
    return 0;
}