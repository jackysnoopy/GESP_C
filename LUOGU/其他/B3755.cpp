#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, k;
int grid[55][55];
int id;

void solve() {
    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < k; i++) grid[i][i] = -1;
    id = 1;
    
    // Fill from bottom-right, greedily place horizontal then vertical
    for (int r = n - 1; r >= 0; r--) {
        for (int c = n - 1; c >= 0; c--) {
            if (grid[r][c] != 0) continue;
            // Try horizontal (right)
            if (c + 1 < n && grid[r][c + 1] == 0) {
                grid[r][c] = id;
                grid[r][c + 1] = id;
                id++;
            }
            // Try vertical (down)
            else if (r + 1 < n && grid[r + 1][c] == 0) {
                grid[r][c] = id;
                grid[r + 1][c] = id;
                id++;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    solve();
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (c > 0) cout << ' ';
            cout << grid[r][c];
        }
        cout << '\n';
    }
    return 0;
}
