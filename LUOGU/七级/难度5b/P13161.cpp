#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<char>> grid(n, vector<char>(n, '.'));
        
        for (int i = 0; i < m; i++) {
            char type;
            int r, c;
            cin >> type >> r >> c;
            grid[r-1][c-1] = type;
        }
        
        // We want to maximize style points
        // '+' and 'x' add 1 point, 'o' adds 2 points
        // Constraints:
        // - Any two models in same row/col: at least one must be '+'
        // - Any two models on same diagonal: at least one must be 'x'
        
        // 'o' counts as both '+' and 'x'
        // So 'o' can coexist with any model
        
        // Let's use a greedy approach:
        // For each empty cell, try to place 'o' if possible
        // Otherwise, try '+' or 'x'
        
        int points = 0;
        int changes = 0;
        vector<string> output;
        
        // Count existing points
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '+' || grid[i][j] == 'x') points++;
                else if (grid[i][j] == 'o') points += 2;
            }
        }
        
        // Try to place new models
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != '.') continue;
                
                // Check if we can place 'o'
                bool can_o = true;
                
                // Check row and column for non-'+'
                for (int k = 0; k < n; k++) {
                    if (grid[i][k] != '.' && grid[i][k] != '+') can_o = false;
                    if (grid[k][j] != '.' && grid[k][j] != '+') can_o = false;
                }
                
                // Check diagonals for non-'x'
                for (int k = -n; k <= n; k++) {
                    int r1 = i + k, c1 = j + k;
                    int r2 = i + k, c2 = j - k;
                    if (r1 >= 0 && r1 < n && c1 >= 0 && c1 < n) {
                        if (grid[r1][c1] != '.' && grid[r1][c1] != 'x') can_o = false;
                    }
                    if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < n) {
                        if (grid[r2][c2] != '.' && grid[r2][c2] != 'x') can_o = false;
                    }
                }
                
                if (can_o) {
                    grid[i][j] = 'o';
                    points += 2;
                    changes++;
                    output.push_back("o " + to_string(i+1) + " " + to_string(j+1));
                    continue;
                }
                
                // Check if we can place '+'
                bool can_plus = true;
                for (int k = 0; k < n; k++) {
                    if (grid[i][k] != '.' && grid[i][k] != '+') can_plus = false;
                    if (grid[k][j] != '.' && grid[k][j] != '+') can_plus = false;
                }
                
                if (can_plus) {
                    grid[i][j] = '+';
                    points++;
                    changes++;
                    output.push_back("+ " + to_string(i+1) + " " + to_string(j+1));
                    continue;
                }
                
                // Check if we can place 'x'
                bool can_x = true;
                for (int k = -n; k <= n; k++) {
                    int r1 = i + k, c1 = j + k;
                    int r2 = i + k, c2 = j - k;
                    if (r1 >= 0 && r1 < n && c1 >= 0 && c1 < n) {
                        if (grid[r1][c1] != '.' && grid[r1][c1] != 'x') can_x = false;
                    }
                    if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < n) {
                        if (grid[r2][c2] != '.' && grid[r2][c2] != 'x') can_x = false;
                    }
                }
                
                if (can_x) {
                    grid[i][j] = 'x';
                    points++;
                    changes++;
                    output.push_back("x " + to_string(i+1) + " " + to_string(j+1));
                }
            }
        }
        
        cout << "Case #" << t << ": " << points << " " << changes << endl;
        for (const string& s : output) {
            cout << s << endl;
        }
    }
    
    return 0;
}
