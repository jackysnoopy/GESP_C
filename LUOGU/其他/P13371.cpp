#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int R, C;
        cin >> R >> C;
        vector<string> grid(R);
        for (int i = 0; i < R; i++) cin >> grid[i];
        bool possible = true;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == '#') {
                    // Check if we can place a 2x2 tile covering (i,j)
                    if (i + 1 < R && j + 1 < C &&
                        grid[i][j+1] == '#' && grid[i+1][j] == '#' && grid[i+1][j+1] == '#') {
                        grid[i][j] = '/'; grid[i][j+1] = '\\';
                        grid[i+1][j] = '\\'; grid[i+1][j+1] = '/';
                    } else {
                        possible = false;
                    }
                }
            }
        }
        cout << "Case #" << tc << ":\n";
        if (!possible) {
            cout << "Impossible\n";
        } else {
            for (int i = 0; i < R; i++) cout << grid[i] << "\n";
        }
    }
    return 0;
}
