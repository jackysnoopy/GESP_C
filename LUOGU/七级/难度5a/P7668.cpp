#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 2; j++) {
            if (grid[i][j] == 'R' && grid[i][j+1] == 'G' && grid[i][j+2] == 'W') {
                ans++;
                grid[i][j] = grid[i][j+1] = grid[i][j+2] = 'X';
            }
        }
    }
    
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n - 2; i++) {
            if (grid[i][j] == 'R' && grid[i+1][j] == 'G' && grid[i+2][j] == 'W') {
                ans++;
                grid[i][j] = grid[i+1][j] = grid[i+2][j] = 'X';
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}