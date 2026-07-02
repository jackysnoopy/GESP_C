#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        double x0, y0;
        string dir;
        cin >> x0 >> y0 >> dir;

        int grid[55][55];
        memset(grid, 0, sizeof(grid));

        int sx = (int)x0;
        int sy = (int)y0;

        for (char c : dir) {
            int nx = sx, ny = sy;
            if (c == 'N') ny++;
            else if (c == 'S') ny--;
            else if (c == 'E') nx++;
            else if (c == 'W') nx--;

            grid[sx][sy] = 1;
            grid[nx][ny] = 1;

            sx = nx;
            sy = ny;
        }

        grid[sx][sy] = 1;

        cout << "Bitmap #" << t << endl;
        for (int y = 49; y >= 0; y--) {
            for (int x = 0; x < 50; x++) {
                cout << (grid[x][y] ? 'X' : '.');
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
