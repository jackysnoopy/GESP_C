#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<string> grid(n, string(m, ' '));
    
    // Greedy: for each cell, try to use the smallest possible color
    // that doesn't conflict with left neighbor only (horizontal adjacency)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                bool ok = true;
                // Check left only (horizontal adjacency)
                if (j > 0 && grid[i][j - 1] == c) ok = false;
                
                if (ok) {
                    grid[i][j] = c;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << grid[i] << "\n";
    }
    
    return 0;
}
