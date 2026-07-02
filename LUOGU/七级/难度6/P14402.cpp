#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1005;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int R, C;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int r1, c1, r2, c2;

int bfs() {
    if (r1 == r2 && c1 == c2) return 0;
    
    memset(dist, -1, sizeof(dist));
    
    // BFS from start
    // Each state is (row, col) - the position where we stop
    // We slide in a direction until hitting a wall
    
    vector<pair<int, int>> q;
    dist[r1][c1] = 0;
    q.push_back({r1, c1});
    
    int head = 0;
    while (head < (int)q.size()) {
        int x = q[head].first;
        int y = q[head].second;
        head++;
        int d = dist[x][y];
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            // Check if we can move in this direction
            if (nx < 1 || nx > R || ny < 1 || ny > C || grid[nx][ny] == '#') {
                continue;
            }
            
            // Slide until we hit a wall or edge
            while (nx + dx[dir] >= 1 && nx + dx[dir] <= R && 
                   ny + dy[dir] >= 1 && ny + dy[dir] <= C && 
                   grid[nx + dx[dir]][ny + dy[dir]] != '#') {
                nx += dx[dir];
                ny += dy[dir];
            }
            
            if (dist[nx][ny] == -1) {
                dist[nx][ny] = d + 1;
                if (nx == r2 && ny == c2) return d + 1;
                q.push_back({nx, ny});
            }
        }
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
        }
    }
    cin >> r1 >> c1 >> r2 >> c2;
    
    cout << bfs() << "\n";
    return 0;
}
