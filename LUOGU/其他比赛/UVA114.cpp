#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXR = 55, MAXC = 55;
int R, C, grid[MAXR][MAXC];

int main() {
    int r0, c0;
    int dir = 0;
    double total = 0;
    
    cin >> R >> C;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];
    
    cin >> r0 >> c0;
    
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    int r = r0, c = c0;
    while (true) {
        total += grid[r][c];
        grid[r][c] = 0;
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) break;
        if (grid[nr][nc] == 0) {
            dir = (dir + 1) % 4;
            nr = r + dr[dir];
            nc = c + dc[dir];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) break;
        }
        r = nr;
        c = nc;
    }
    
    cout << fixed << setprecision(0) << total << "\n";
    return 0;
}
